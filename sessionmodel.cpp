#include "sessionmodel.h"

SessionModel::SessionModel(QObject *parent)
    : QAbstractListModel(parent)
//      m_pModel(new FieldModel)
{
    m_players.emplace_back(Player{"Player1", "red", 0});
    m_players.emplace_back(Player{"Player2", "blue", 0});
//    m_players.emplace_back(Player{"Player3", "green", 0});

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

void SessionModel::setPModel(FieldModel *newPModel)
{
    m_pModel = newPModel;
    connect(m_pModel, SIGNAL(addPoints(int,int)), this, SLOT(addPoints(int,int)));
    connect(m_pModel, SIGNAL(gameOver()), this, SLOT(endGame()));
}

int SessionModel::winner()
{
    return m_winner;
}

void SessionModel::addPoints(int player, int points)
{
//    qDebug() << player << points;
    m_players[player].points += points;
    emit dataChanged(createIndex(player, 0), createIndex(player, 0), QVector<int>{Qt::EditRole});
//    emit addedPoints();
}

void SessionModel::endGame()
{
   int winner = std::distance(m_players.begin(),
                      std::max_element(m_players.begin(), m_players.end(), [](Player &a, Player &b){
                          return a.points < b.points;
                      }));

   emit sendWinner();

//   delete m_pModel;

}
