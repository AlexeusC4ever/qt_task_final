#include <QFile>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTextStream>
#include <QDialogButtonBox>
#include <QString>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <mutex>
#include "sessionmodel.h"

static constexpr int sendPlayerIdOperation = 1;
static constexpr int sendPointOperation = 2;
static constexpr int giveMoveOperation = 3;
static constexpr size_t defaultFieldDimension {14};

SessionModel::SessionModel(QObject *parent)
    : QAbstractListModel(parent),
      m_pModel(/*nullptr*/new FieldModel),
      m_pSocket(nullptr),
      m_abilityToMakeMoveInOnline(false),
      m_onlineGame(false)
{
    m_players.emplace_back(Player{"Player1", "red", 0});
    m_players.emplace_back(Player{"Player2", "blue", 0});
//    m_players.emplace_back(Player{"Player2", "green", 0});

    connect(m_pModel, SIGNAL(addPoints(int,int)), this, SLOT(addPoints(int,int)));
    connect(m_pModel, SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(m_pModel, SIGNAL(changePlayer()), this, SLOT(nextPlayer()));



    m_settingsDialog = new QDialog;
    m_okButton = new QDialogButtonBox(QDialogButtonBox::Ok);
    QHBoxLayout *widthLayout = new QHBoxLayout;
    QHBoxLayout *heightLayout = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(m_settingsDialog);

    m_pLineEditWidth = new QLineEdit;
    m_pLabelWidth = new QLabel(tr("Columns:"));
    m_pLineEditWidth->setText(QString::number(defaultFieldDimension));
    m_pLabelWidth->setBuddy(m_pLineEditWidth);
    widthLayout->addWidget(m_pLabelWidth);
    widthLayout->addWidget(m_pLineEditWidth);

    m_pLineEditHeight = new QLineEdit;
    m_pLabelHeight = new QLabel(tr("Rows:"));
    m_pLineEditHeight->setText(QString::number(defaultFieldDimension));
    m_pLabelHeight->setBuddy(m_pLineEditHeight);
    heightLayout->addWidget(m_pLabelHeight);
    heightLayout->addWidget(m_pLineEditHeight);

    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(heightLayout);
    mainLayout->addWidget(m_okButton);

    m_settingsDialog->setLayout(mainLayout);

    connect(m_okButton, SIGNAL(accepted()), this, SLOT(changeFieldModel()));
    connect(m_okButton, SIGNAL(accepted()), m_settingsDialog, SLOT(hide()));
}

SessionModel::~SessionModel()
{
//    delete m_pModel;
}

int SessionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_players.size();
}

QVariant SessionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
        return QVariant(m_players[index.row()].name);
    else if(role == Qt::EditRole)
        return QVariant(m_players[index.row()].points);
    else if(role == Qt::DecorationRole)
        return QVariant(m_players[index.row()].color);

    return QVariant();
}

FieldModel *SessionModel::pModel() const
{
    return m_pModel;
}

int SessionModel::player()
{
    if(m_onlineGame)
        return m_currentOnlinePlayer;

    return m_pModel->currentPlayer();
}

QColor SessionModel::playerColor(int player)
{
    QColor playerColor;
    if(player == -1)
    {
        playerColor = qRgba(255, 255, 255, 0);
    }
    else{
        playerColor = m_players[player].color;
    }
    return playerColor;
}

QColor SessionModel::playerColorForArea(int player)
{
    QColor color = playerColor(player);
    color.setAlpha(50);
    return color;
}

void SessionModel::nextPlayer()
{

    int curPlayer = m_pModel->currentPlayer();
    if(curPlayer == m_players.size() - 1)
        m_pModel->setCurrentPlayer(0);
    else
        m_pModel->setCurrentPlayer(curPlayer + 1);

//    qDebug() << curPlayer;
    //    return curPlayer;
}

void SessionModel::showSettingsDialog()
{
    m_settingsDialog->show();
}

void SessionModel::connectRequest()
{
    if(m_pSocket)
        delete m_pSocket;

    m_pSocket = new QTcpSocket;
std::unique_ptr<FieldModel> model(new FieldModel(defaultFieldDimension, defaultFieldDimension));

    m_in.setDevice(m_pSocket);
    m_out.setDevice(m_pSocket);
    m_pSocket->connectToHost(QHostAddress::LocalHost, 45569);
    while (!m_pSocket->waitForConnected(5000))
        if (m_pSocket->error() != QAbstractSocket::UnknownSocketError)
        {
        //          err << "Error: " << socket.errorString() << Qt::endl;
            QMessageBox::warning(m_settingsDialog, tr("Error"), tr("Network Error"));
            return;
        }

    setPModel(model.release());

    m_pModel->setOnlineGame(true);

    connect(m_pModel, SIGNAL(sendPointToServer(int)), this, SLOT(sendPointToServer(int)));
    connect(m_pSocket, &QIODevice::readyRead,
        this, &SessionModel::onReadyRead);

    QMessageBox::information(m_settingsDialog, tr("OnlineGame"), tr("Server was found"));

}

void SessionModel::saveModel(QString &fileName)
{
    fileName = "savedgames/" + fileName + ".txt";

    QFile fileForSave(fileName);

    if (!fileForSave.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(m_settingsDialog, tr("Error"), tr("Save Error"));
        qDebug() << "ERROR" << "Save Error";
        return;
    }

    try{
        QDataStream data(&fileForSave);
        data << *m_pModel;
        data << m_players.size();
        for(int i = 0; i < m_players.size(); ++i)
        {
            data << m_players[i].color;
            data << m_players[i].name;
            data << m_players[i].points;
        }

    } catch(...)
    {
        QMessageBox::warning(m_settingsDialog, tr("Error"), tr("Save Error"));
        fileForSave.remove();
    }

    fileForSave.close();
}

void SessionModel::loadModel(QString &fileName)
{
    fileName = "savedgames/" + fileName + ".txt";

    QFile fileForLoad(fileName);

    if (!fileForLoad.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(m_settingsDialog, tr("Error"), tr("Load Error"));
        qDebug() << "LOADERROR";
        return;
    }

    try{
        QDataStream data(&fileForLoad);

        size_t rows = 0;
        size_t columns = 0;
        size_t fieldSize = 0;

        data >> rows >> columns >> fieldSize;

        std::unique_ptr<FieldModel> newModel(new FieldModel(rows, columns));
        std::vector<Player> newPlayers;

        data >> *newModel;

        size_t playersSize = 0;
        data >> playersSize;
        qDebug() << "PLAYERS:" << playersSize;

        newPlayers.resize(playersSize);

        for(size_t i = 0; i < playersSize; ++i)
        {
            data >> newPlayers[i].color;
            data >> newPlayers[i].name;
            data >> newPlayers[i].points;
            qDebug() << newPlayers[i].color << m_players[i].name << m_players[i].points;
        }
        setPModel(newModel.release());
        m_players = newPlayers;

    } catch(...)
    {
        QMessageBox::warning(m_settingsDialog, tr("Error"), tr("Load Error"));
    }

    fileForLoad.close();

    emit dataChanged(createIndex(0, 0), createIndex(m_players.size() - 1, 0), QVector<int> {
                         Qt::DisplayRole,
                         Qt::EditRole,
                         Qt::DecorationRole});

    emit modelChanged();
}

void SessionModel::setPModel(FieldModel *newPModel)
{
    FieldModel *oldModel = m_pModel;

    m_pModel = newPModel;

    if(oldModel){
        delete oldModel;
    }

    qDebug() << "SETTINGMODEL";

    connect(m_pModel, SIGNAL(addPoints(int,int)), this, SLOT(addPoints(int,int)));
    connect(m_pModel, SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(m_pModel, SIGNAL(changePlayer()), this, SLOT(nextPlayer()));

    for(auto& player: m_players)
    {
        player.points = 0;
    }

    emit dataChanged(createIndex(0, 0), createIndex(m_players.size() - 1, 0), QVector<int> {
                                                                         Qt::DisplayRole,
                                                                         Qt::EditRole,
                                                                         Qt::DecorationRole});

    emit modelChanged();
}

int SessionModel::winner()
{
    return m_winner;
}

void SessionModel::addPoints(int player, int points)
{
        m_players[player].points += points;
        emit dataChanged(createIndex(player, 0),
                         createIndex(player, 0),
                         QVector<int>{Qt::EditRole});
}

void SessionModel::endGame()
{
   int winner = std::distance(m_players.begin(),
                      std::max_element(m_players.begin(), m_players.end(), [](Player &a, Player &b){
                          return a.points < b.points;
                      }));

   emit sendWinner(winner, m_players[winner].name);
}

void SessionModel::sendPointToServer(int index)
{
    m_in << index;
    m_pSocket->flush();
    m_abilityToMakeMoveInOnline = false;
}

void SessionModel::onReadyRead()
{
    int operation = 0;
    int player = 0;
    int pointIndex = 0;

    m_out.startTransaction();
    while(!m_out.atEnd())
    {
        m_out >> operation;

        switch(operation)
        {
            case(sendPlayerIdOperation):
                m_out >> player;
                m_pModel->setCurrentPlayer(player);
//                qDebug() << "sendPlayerIdOperation" << player;
            break;
            case(sendPointOperation):
                m_out >> pointIndex;
                m_out >> player;
                m_currentOnlinePlayer = player;
                if(!m_abilityToMakeMoveInOnline)
                    m_pModel->dfsStart(pointIndex, player);
//                qDebug() << "sendPointOperation" << player << pointIndex;
            break;
            case(giveMoveOperation):
                m_abilityToMakeMoveInOnline = true;
                m_currentOnlinePlayer = m_pModel->currentPlayer();
//                qDebug() << "giveMoveOperation";
                emit readyToMove();
            break;
        }
    }
    if (!m_out.commitTransaction()){
//        qDebug() << "!commitTransaction" << operation;
        return;
    }

}

void SessionModel::changeFieldModel()
{
    setPModel(new FieldModel(m_pLineEditHeight->text().toInt(),
                             m_pLineEditWidth->text().toInt()));
}

bool SessionModel::abilityToMakeMoveInOnline() const
{
    return m_abilityToMakeMoveInOnline;
}
