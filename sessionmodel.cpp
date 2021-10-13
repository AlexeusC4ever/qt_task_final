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

SessionModel::SessionModel(QQmlApplicationEngine *engine, QObject *parent)
    : QAbstractListModel(parent),
      m_pModel(/*nullptr*/new FieldModel),
      m_pSocket(nullptr),
      m_abilityToMakeMoveInOnline(false),
      m_onlineGame(false)
{
    m_players.emplace_back(Player{"Player1", "red", 0});
    m_players.emplace_back(Player{"Player2", "blue", 0});
//    m_players.emplace_back(Player{"Player3", "green", 0});
//    connect(this, SIGNAL(saveGameRequest(QString&)), this, SLOT(saveModel(QString&)));
//    connect(this, SIGNAL(loadGameRequest(QString&)), this, SLOT(loadModel(QString&)));
    connect(m_pModel, SIGNAL(addPoints(int,int)), this, SLOT(addPoints(int,int)));
    connect(m_pModel, SIGNAL(gameOver()), this, SLOT(endGame()));
    connect(m_pModel, SIGNAL(changePlayer()), this, SLOT(nextPlayer()));
//    m_pContext = new QQmlContext(engine->rootContext());
//    m_pComponent = new QQmlComponent(this);

//    m_pContext->setContextProperty("fieldModel", m_pModel);

//    qDebug() << "CREATED";

//    m_pComponent->setData();
//    connectRequest();
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
    if (!index.isValid()/* || (role != Qt::EditRole && role != Qt::DisplayRole)*/)
        return QVariant();

    // FIXME: Implement me!
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
    return m_players[player].color;
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
    qDebug() << "CONNECT";

    QTextStream out(stdout), err(stderr);

    if(m_pSocket)
        delete m_pSocket;

    m_pSocket = new QTcpSocket;

    m_in.setDevice(m_pSocket);///////////////
    m_out.setDevice(m_pSocket);
    m_pSocket->connectToHost(QHostAddress::LocalHost, 45569);
    out << "Connecting to the server..." << Qt::endl;
    while (!m_pSocket->waitForConnected(5000))
        if (m_pSocket->error() != QAbstractSocket::UnknownSocketError)
        {
        //          err << "Error: " << socket.errorString() << Qt::endl;
            QMessageBox::warning(nullptr, tr("ERROR"), tr("Network Error"));
            return;
        }
      //
    out << "Connected to " << m_pSocket->peerAddress().toString() <<
        ':' << m_pSocket->peerPort() <<
        "\nLocal: " << m_pSocket->localAddress().toString() <<
        ':' << m_pSocket->localPort() << Qt::endl;


    FieldModel *model = new FieldModel(defaultFieldDimension, defaultFieldDimension);
    setPModel(model);

    m_pModel->setOnlineGame(true);

//    FieldModel *newModel = new FieldModel(15, 15);
//    setPModel(newModel);

//    m_pModel->resetModel(defaultFieldDimension, defaultFieldDimension);

//    emit modelChanged(m_pModel);

//    emit m_pModel->dataChanged(createIndex(0, 0), createIndex(m_pModel->rowCount(), 0), QVector<int> { Qt::DisplayRole,
//                     Qt::EditRole});
    connect(m_pModel, SIGNAL(sendPointToServer(int)), this, SLOT(sendPointToServer(int)));
    connect(m_pSocket, &QIODevice::readyRead,
        this, &SessionModel::onReadyRead);

//    m_inout.startTransaction();
//    connect(
//      m_pSocket, &QIODevice::readyRead,
//      this, &ClientDialog::on_readyRead);

//    m_pModel->setOnlineGame(true);


}

void SessionModel::saveModel(QString &fileName)
{
    fileName = "savedgames/" + fileName + ".txt";

    QFile fileForSave(fileName);

    if (!fileForSave.open(QIODevice::WriteOnly))
    {
//        qDebug() << "ERROR";
        return;
    }

    QDataStream data(&fileForSave);
    data << *m_pModel;
    data << m_players.size();
    for(int i = 0; i < m_players.size(); ++i)
    {
        data << m_players[i].color;
        data << m_players[i].name;
        data << m_players[i].points;
    }
    fileForSave.close();
}

void SessionModel::loadModel(QString &fileName)
{   /*"qrc:/window.qml"*/
    fileName = "savedgames/" + fileName + ".txt";

    QFile fileForLoad(fileName);

    if (!fileForLoad.open(QIODevice::ReadOnly))
    {
        qDebug() << "ERROR";
        return;
    }

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

    setPModel(newModel.release());

    for(size_t i = 0; i < playersSize; ++i)
    {
        data >> newPlayers[i].color;
        data >> newPlayers[i].name;
        data >> newPlayers[i].points;
        qDebug() << newPlayers[i].color << m_players[i].name << m_players[i].points;
    }
    fileForLoad.close();

    m_players = newPlayers;

    emit dataChanged(createIndex(0, 0), createIndex(m_players.size() - 1, 0), QVector<int> { Qt::DisplayRole,
                     Qt::EditRole, Qt::DecorationRole});
//    int cellsMount = m_pModel->rowCount();
//    emit m_pModel->dataChanged(createIndex(0, 0), createIndex(cellsMount, 0), QVector<int> { Qt::DisplayRole,
//                     Qt::EditRole});

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

//    m_pContext->setContextProperty("FieldModel", m_pModel);

    connect(m_pModel, SIGNAL(changePlayer()), this, SLOT(nextPlayer()));
//    m_pModel->resetModel(defaultFieldDimension, defaultFieldDimension);

    for(auto& player: m_players)
    {
        player.points = 0;
    }

    emit dataChanged(createIndex(0, 0), createIndex(m_players.size() - 1, 0), QVector<int> { Qt::DisplayRole,
                     Qt::EditRole, Qt::DecorationRole});
    emit modelChanged();

//    emit m_pModel->dataChanged(createIndex(0, 0), createIndex(m_pModel->rowCount(), 0), QVector<int> { Qt::DisplayRole,
//                     Qt::EditRole});
}

int SessionModel::winner()
{
    return m_winner;
}

void SessionModel::addPoints(int player, int points)
{
//    qDebug() << player << points;
//    if(m_pModel->onlineGame()){
//        m_players[m_currentOnlinePlayer].points += points;
//        emit dataChanged(createIndex(m_currentOnlinePlayer, 0),
//                         createIndex(m_currentOnlinePlayer, 0),
//                         QVector<int>{Qt::EditRole});
//    }

//    else{
        m_players[player].points += points;
        emit dataChanged(createIndex(player, 0),
                         createIndex(player, 0),
                         QVector<int>{Qt::EditRole});
//    }
}

void SessionModel::endGame()
{
   int winner = std::distance(m_players.begin(),
                      std::max_element(m_players.begin(), m_players.end(), [](Player &a, Player &b){
                          return a.points < b.points;
                      }));

   emit sendWinner(winner, m_players[winner].name);

//   delete m_pModel;

}

void SessionModel::sendPointToServer(int index)
{
    qDebug() << "CATCH";

    m_in << index;
    m_pSocket->flush();
    m_abilityToMakeMoveInOnline = false;
}

void SessionModel::onReadyRead()
{
    qDebug() << "CLIENTREADYREAD";

//    std::mutex a;
//    std::lock_guard<std::mutex> mute(a);

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
                qDebug() << "sendPlayerIdOperation" << player;
            break;
            case(sendPointOperation):
                m_out >> pointIndex;
                m_out >> player;
                m_currentOnlinePlayer = player;
                if(!m_abilityToMakeMoveInOnline)
                    m_pModel->dfsStart(pointIndex, player);
                qDebug() << "sendPointOperation" << player << pointIndex;
            break;
            case(giveMoveOperation):
                m_abilityToMakeMoveInOnline = true;
                m_currentOnlinePlayer = m_pModel->currentPlayer();
                qDebug() << "giveMoveOperation";
                emit readyToMove();
            break;
        }
    }


    if (!m_out.commitTransaction()){
        qDebug() << "!commitTransaction" << operation;
        return;
    }
//    emit m_pSocket->readyRead();

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
