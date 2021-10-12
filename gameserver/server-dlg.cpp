// server-dlg.cpp

#include "server-dlg.h"

#include <QTcpServer>
#include <QTcpSocket>

static constexpr int sendPlayerIdOperation = 1;
static constexpr int sendPointOperation = 2;
static constexpr int giveMoveOperation = 3;

ServerDialog::ServerDialog():
    m_playersMount(2),
    m_playersCount(0),
    m_currentPLyer(0)
{
//   qDebug() << "HHHHHHHHHHHHHHEere";
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
       qDebug() << "HgiveMove";
    QDataStream inout(m_players[clientId - 1]);
//    inout.startTransaction();
    inout << giveMoveOperation;
    m_players[clientId - 1]->flush();
}

void ServerDialog::sendPlayerId(int clientId)
{
       qDebug() << "sendPlayerId";
    QDataStream inout(m_players[clientId - 1]);
//    inout.startTransaction();
    inout << sendPlayerIdOperation << clientId - 1;
    m_players[clientId - 1]->flush();
}

void ServerDialog::sendPoints()
{
    for(auto &client : m_players)
    {
        if(/*true*/client != m_players[m_currentPLyer])
        {
            qDebug() << "SERVER::CLIENT";
            QDataStream inout(client);
            inout << sendPointOperation << m_pointIndex << m_currentPLyer;
            m_players[m_currentPLyer]->flush();
        }
    }
//    QDataStream inout(m_players[player]);
//    inout << sendPointOperation << index << player;
//    m_players[player]->flush();
    if(m_currentPLyer == m_playersMount - 1)
        m_currentPLyer = 0;
    else
        ++m_currentPLyer;

    QDataStream inout(m_players[m_currentPLyer]);
    inout << giveMoveOperation;
    m_players[m_currentPLyer]->flush();
}

void ServerDialog::on_newConnection()
{
    if(m_playersCount == m_playersMount)
    {
        //ОБРАБОТАТЬ
        return;
    }

    QTcpSocket *pClientSocket = m_pServer->nextPendingConnection();
    ++m_playersCount;

    m_players.emplace_back(pClientSocket);

    sendPlayerId(m_playersCount);

    if(m_playersCount == 1)
        giveMove(m_playersCount);

    connect(pClientSocket, &QAbstractSocket::disconnected,
        pClientSocket, &QObject::deleteLater);
    connect(pClientSocket, &QIODevice::readyRead,
        this, &ServerDialog::on_readyRead);

    qDebug() << "CONNECTED";
}

void ServerDialog::on_readyRead()
{
    if(m_playersCount != m_playersMount) return;
//    if(m_playersCount != m_playersMount)
//        return;

    QTcpSocket *pClientSocket = qobject_cast <QTcpSocket *> (sender());

//    connect(pClientSocket, SIGNAL(readChannelFinished()), this, SLOT(sendPoints()));

    if (!pClientSocket)
    {
        qDebug() << "!pClientSocket";
        return;
    }

    QDataStream inout(pClientSocket);
    inout.startTransaction();

    inout >> m_pointIndex;

    if (!inout.commitTransaction()){
        qDebug() << "!inout.commitTransaction()" << m_pointIndex;
        return;
    }

//    QString strChat = QString::number(m_pointIndex);

////    inout << strChat;
//    m_pTextEditChat->setPlainText(strChat);
//    //
////    pClientSocket->disconnectFromHost();

////    inout << strChat;

//    m_pTextEditChat->setPlainText(strChat);

//    for(int i = 0; i < m_playersMount; ++i)
//        if(m_clients[i] == pClientSocket)
//            curPlayer = i;

//    for(auto &client : m_players)
//    {
//        qDebug() << "SERVER::CLIENT";
//        if(/*true*/client != pClientSocket)
//        {
//            sendPoints(m_pointIndex, m_currentPLyer);
//        }
//    }

//            qDebug() << "SERVER::CLIENTENDING";
            sendPoints();
    //
//    pClientSocket->disconnectFromHost();
}    // on_readyRead()

// End of File
