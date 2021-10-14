// server-dlg.cpp

#include "server-dlg.h"

#include <QTcpServer>
#include <QTcpSocket>

static constexpr int sendPlayerIdOperation = 1;
static constexpr int sendPointOperation = 2;
static constexpr int giveMoveOperation = 3;
static constexpr int sendingPointToServer = 4;
static constexpr int sendEndGameSignalToServer = 5;
static constexpr int sendPlayerDisconnectedSignalToClient = 6;

ServerDialog::ServerDialog():
    m_playersMount(2),
    m_playersCount(0),
    m_currentPLyer(0)
{
    m_players.reserve(m_playersMount);

    setupUi(this);
    //
    connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(close()));
    //
    m_pServer = new QTcpServer(this);
    connect( m_pServer, &QTcpServer::newConnection,
    this, &ServerDialog::on_newConnection);


    if (!m_pServer->listen(QHostAddress::Any, 45569))
    {
        QString strErrors = m_pTextEditErrors->toPlainText();
        strErrors += QString("Error: ") + m_pServer->errorString() + '\n';
    //
        m_pTextEditErrors->setPlainText(strErrors);
    }
}



void ServerDialog::giveMove(int clientId)
{
//    qDebug() << "giveMove";
    QDataStream inout(m_players[clientId - 1]);
    inout << giveMoveOperation;
    m_players[clientId - 1]->flush();
}

void ServerDialog::sendPlayerId(int clientId)
{
//    qDebug() << "sendPlayerId";
    QDataStream inout(m_players[clientId - 1]);
    inout << sendPlayerIdOperation << clientId - 1;
    m_players[clientId - 1]->flush();
}

void ServerDialog::sendPoints()
{
    for(auto &client : m_players)
    {
        if(/*true*/client != m_players[m_currentPLyer])
        {
//            qDebug() << "SERVER::CLIENT";
            QDataStream inout(client);
            inout << sendPointOperation << m_pointIndex << m_currentPLyer;
            m_players[m_currentPLyer]->flush();
        }
    }

    if(m_currentPLyer == m_playersMount - 1)
        m_currentPLyer = 0;
    else
        ++m_currentPLyer;

    QDataStream inout(m_players[m_currentPLyer]);
    inout << giveMoveOperation;
    m_players[m_currentPLyer]->flush();
}

void ServerDialog::playerDisconnected()
{
    QTcpSocket *pClientSocket = qobject_cast <QTcpSocket *> (sender());

    if(m_playersCount == m_playersMount)
    {
        --m_playersCount;
        for(auto &client : m_players)
        {
            if(client != pClientSocket)
            {
                QDataStream inout(client);
                inout << sendPlayerDisconnectedSignalToClient;
                client->flush();
            }
        }

        m_pTextEditChat->setPlainText(m_pTextEditChat->toPlainText()
                                      + QString("\n")
                                      + "Game Over");
        for(auto &player : m_players)
        {
            delete player;
        }
        m_players.clear();
        m_playersCount = 0;
        m_gameEndedCheck = 0;
    }
    else{
        --m_playersCount;
        for(auto client = m_players.begin(); client != m_players.end(); ++client)
        {
            if(pClientSocket == *client)
            {
                m_players.erase(client);
                delete *client;
                break;
            }
        }
    }
}

void ServerDialog::on_newConnection()
{
    if(m_playersCount == m_playersMount)
    {
        return;
    }

    QTcpSocket *pClientSocket = m_pServer->nextPendingConnection();
    ++m_playersCount;

    m_players.emplace_back(pClientSocket);

    sendPlayerId(m_playersCount);

    if(m_playersCount == m_playersMount)
        giveMove(1);

    connect(pClientSocket, &QAbstractSocket::disconnected,
        this, &ServerDialog::playerDisconnected);

    connect(pClientSocket, &QIODevice::readyRead,
        this, &ServerDialog::on_readyRead);
}

void ServerDialog::on_readyRead()
{
    if(m_playersCount != m_playersMount) return;

    QTcpSocket *pClientSocket = qobject_cast <QTcpSocket *> (sender());

    if (!pClientSocket)
    {
        m_pTextEditErrors->setPlainText("SOCKET ERROR");
        return;
    }

    QDataStream inout(pClientSocket);
    inout.startTransaction();

    int operation = 0;

    while(!inout.atEnd())
    {
        inout >> operation;

        switch(operation)
        {
            case(sendingPointToServer):
                inout >> m_pointIndex;
                m_pTextEditChat->setPlainText(m_pTextEditChat->toPlainText()
                                              + QString("\n")
                                              + QString::number(m_currentPLyer)
                                              + QString(" ")
                                              + QString::number(m_pointIndex));
                sendPoints();
            break;
            case(sendEndGameSignalToServer):
                ++m_gameEndedCheck;
                qDebug() << "DISCONNECT";
                if(m_gameEndedCheck == m_playersMount)
                {
                    m_pTextEditChat->setPlainText(m_pTextEditChat->toPlainText()
                                                  + QString("\n")
                                                  + "Game Over");
                    for(auto &player : m_players)
                    {
                        delete player;
                    }
                    m_playersCount = 0;
                    m_gameEndedCheck = 0;
                    m_players.clear();
                }
            break;
        }
    }


    if (!inout.commitTransaction()){
        m_pTextEditErrors->setPlainText("Transaction Error");
        return;
    }

}    // on_readyRead()

// End of File
