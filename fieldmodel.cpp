#include "dfsthread.h"
#include "fieldmodel.h"


FieldModel::FieldModel(const size_t rows, const size_t columns, QObject *parent)
    : QAbstractListModel(parent),
      m_rows(rows),
      m_columns(columns),
      m_fieldSize(columns * rows),
      thr(new DfsThread(this)),
      m_currentPlayer(0)
{
    m_vectorAreas.reserve(m_fieldSize);
//    for(auto &vec: m_vectorAreas)
//    {
//        vec.first.reserve(10);
//    }

    m_cells.resize(m_fieldSize);
    for(int i = 0; i < m_fieldSize; ++i)
    {
        m_cells[i] = new Cell(getCoordsFormIndex(i));
    }

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            std::vector<Cell *> neighbours;
            for(int row = i - 1; row < i + 2; ++row) {
                for(int column = j - 1; column < j + 2; ++column) {
                    if(row >= 0 && row < rows && column >= 0 && column < columns
                            && !(row == i && column == j)){
                        neighbours.push_back(getCellByCoords(Coord{row, column}));
                    }
                }
            }
            getCellByCoords(Coord{i, j})->setNeighbours(std::move(neighbours));
        }
    }

//    connect(thr, SIGNAL(dfsFinished()), this, SIGNAL(sendCoordsOfOccupiedArea()));
//    connect(thr, SIGNAL(cycleIsReadyForRepaint(int)), this, SLOT(addVertexesToCycle(int)));
    connect(thr, SIGNAL(dfsFinished()), this, SLOT(getCoordsOfOccupiedArea()));
}

FieldModel::~FieldModel()
{
    if(thr->isRunning()){
        thr->requestInterruption();
        thr->wait();
    }
    delete thr;
}

std::vector<Cell *> FieldModel::getCells()
{
    return m_cells;
}

int FieldModel::fieldSize()
{
    return m_fieldSize;
}

int FieldModel::rowCountForQml()
{
    return m_rows;
}

int FieldModel::columnCountForQml()
{
    return m_columns;
}

//void FieldModel::addVertexesToCycle(int cycle)
//{
//    QVector<QPoint> result;
//    int player =  getCellByCoords(thr->getAreaForRepaint()[0])->player();
//    for(auto& coord: thr->getAreaForRepaint())
//    {
//        getCellByCoords(coord)->setArea(cycle);
//        QPoint a(coord.x, coord.y);
//        result.emplace_back(a);
//    }

//    m_vectorAreas[cycle - 1] = std::make_pair(result, player);
////    if(thr->m_repaintMutex.try_lock())
//    thr->m_repaintMutex.unlock();

//    qDebug() << result;

//    emit repaintAllAreas();
//}

int FieldModel::currentPlayer() const
{
    return m_currentPlayer;
}

//void FieldModel::setCurrentPlayer(int newCurrentPlayer)
//{
//    m_currentPlayer = newCurrentPlayer;
//}

//QVector<QPoint> FieldModel::getCoordsOfOccupiedArea()
//{
////    m_vectorAreas.emplace_back(thr->getVertexesOfCycle());

//    if(!thr->getVertexesOfCycle().size() || !thr->pointsToAdd())
//        return QVector<QPoint>();

//    emit addPoints(thr->pointsToAdd(), m_currentPlayer);

//    int numberOfCycle = thr->getNumberOfCurrentCycle();

//    if(numberOfCycle >= m_vectorAreas.size())
//        m_vectorAreas.resize(numberOfCycle);

//    QVector<QPoint> result;
//    for(auto& coord: thr->getVertexesOfCycle())
//    {
//        getCellByCoords(coord)->setArea(numberOfCycle);
//        QPoint a;
//        a.setX(coord.x);
//        a.setY(coord.y);
////        qDebug() << a;
//        result.emplace_back(a);
//    }

//    m_vectorAreas[numberOfCycle - 1] = std::make_pair(result, m_currentPlayer);

//    if(m_movesMade == m_fieldSize)
//        emit gameOver();

//    emit repaintAllAreas();

//    return result;
//}

void FieldModel::getCoordsOfOccupiedArea()
{
//    m_vectorAreas.emplace_back(thr->getVertexesOfCycle());

    emit addPoints(m_currentPlayer, thr->pointsToAdd());
    if(thr->getVertexesOfCycle().size()/* || !thr->pointsToAdd()*/)
    {

    //    emit addPoints(thr->pointsToAdd(), m_currentPlayer);

        int numberOfCycle = thr->getNumberOfCurrentCycle();

        qDebug() << numberOfCycle;

        if(numberOfCycle >= m_vectorAreas.size())
            m_vectorAreas.resize(numberOfCycle);

        QVector<QPoint> result;
        for(auto& coord: thr->getVertexesOfCycle())
        {
            getCellByCoords(coord)->setArea(numberOfCycle);
            QPoint a;
            a.setX(coord.x);
            a.setY(coord.y);
    //        qDebug() << a;
            result.emplace_back(a);
        }
        qDebug() << "PLAYER:" << m_currentPlayer;
        m_vectorAreas[numberOfCycle - 1] = std::make_pair(result, m_currentPlayer);
        emit repaintAllAreas();
        return;
    }

    emit changePlayer();

    if(m_movesMade == m_fieldSize)
        emit gameOver();

}

Coord FieldModel::getCoordsFormIndex(int index) const
{
    Coord coords;
    coords.x = index / m_columns;
    coords.y = index % m_columns;
    return coords;
}

int FieldModel::getIndexFormCoords(Coord coords) const
{
    return coords.x * m_columns + coords.y;
}

Cell *FieldModel::getCellByCoords(Coord coords)
{
    return m_cells[coords.x * m_columns + coords.y];
}

int FieldModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_cells.size();
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || (role != Qt::EditRole && role != Qt::DisplayRole))
        return QVariant();

    if(index.row() >= this->m_fieldSize)
        return QVariant();

    const int rowIndex(static_cast<int>(index.row()));

//    qDebug() << m_cells[rowIndex]->player();

    if(role == Qt::EditRole)
        return QVariant(m_cells[rowIndex]->player());
    else if(role == Qt::DisplayRole)
        return QVariant(m_cells[rowIndex]->isClickable());

    return QVariant();
}


void FieldModel::makeCellNonClickable(Cell *cell)
{
    cell->setClickable(false);
    int index = getIndexFormCoords(cell->getCoord());
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int> { Qt::DisplayRole });
}

int FieldModel::areasCount()
{
    return m_vectorAreas.size();
}

QVector<QPoint> *FieldModel::getAreaForIncludeNewVertexes(int area)
{
    if(m_vectorAreas.empty())
        return NULL;

    return &m_vectorAreas[area].first;
}



void FieldModel::dfsStart(int index, int player)
{
//    qDebug() << getCoordsFormIndex(index).x << getCoordsFormIndex(index).y;
    if(index < 0 || index >= m_fieldSize) return;

    ++m_movesMade;

    m_cells[index]->setPlayer(player);
//    m_currentPlayer = player;
//    a.emplace_back(Qt::EditRole);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int> { Qt::EditRole });

    thr->dfsStart(index);

}

QVector<QPoint> FieldModel::getAreaForPaint(int area)
{
    if(m_vectorAreas.empty())
        return QVector<QPoint>();

    return m_vectorAreas[area].first;
}

int FieldModel::getAreaOwner(int area)
{
    if(m_vectorAreas.empty())
        return -1;

    return m_vectorAreas[area].second;
}

void FieldModel::setCurrentPlayer(int newCurrentPlayer)
{
    m_currentPlayer = newCurrentPlayer;
}

