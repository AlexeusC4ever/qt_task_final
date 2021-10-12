#include "dfsthread.h"
#include "fieldmodel.h"
#include <QColor>


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

    setNeighbours(m_cells, m_rows, m_columns);

//    connect(thr, SIGNAL(dfsFinished()), this, SLOT(getCoordsOfOccupiedArea()));
    connect(thr, SIGNAL(dfsFinished()), this, SLOT(onDfsFinished()));
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

int FieldModel::currentPlayer() const
{
    return m_currentPlayer;
}

void FieldModel::getCoordsOfOccupiedArea()
{
    if(m_onlineGame)
        emit addPoints(m_currentOnlinePlayer, thr->pointsToAdd());
    else
        emit addPoints(m_currentPlayer, thr->pointsToAdd());

    if(thr->getVertexesOfCycle().size()/* || !thr->pointsToAdd()*/)
    {

    //    emit addPoints(thr->pointsToAdd(), m_currentPlayer);

        int numberOfCycle = thr->getNumberOfCurrentCycle();

//        qDebug() << numberOfCycle;

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
//        qDebug() << "PLAYER:" << m_currentPlayer;
        if(m_onlineGame)
            m_vectorAreas[numberOfCycle - 1] = std::make_pair(result, m_currentOnlinePlayer);
        else
            m_vectorAreas[numberOfCycle - 1] = std::make_pair(result, m_currentPlayer);

        emit repaintAllAreas();
        return;
    }

//    emit changePlayer();

    if(m_movesMade == m_fieldSize)
        emit gameOver();

}

void FieldModel::onDfsFinished()
{
    if(!m_onlineGame)
        emit changePlayer();

    else
        emit repaintAll();
}

bool FieldModel::onlineGame() const
{
    return m_onlineGame;
}

void FieldModel::setOnlineGame(bool newOnlineGame)
{
    m_onlineGame = newOnlineGame;
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

//QVector<QPoint> *FieldModel::getAreaForIncludeNewVertexes(int area)
//{
//    if(m_vectorAreas.empty())
//        return NULL;

//    return &m_vectorAreas[area].first;
//}

//void FieldModel::resetModel(int newRowSize, int newColumnSize)
//{
//    int newSize = newRowSize * newColumnSize;
//    std::vector<Cell *> newCells;
//    qDebug() << "NEWSIZE" << newSize;
//    newCells.reserve(newSize);

//    for(int i = 0; i < newSize; ++i)
//    {
////        qDebug() << getCoordsFormIndex(i).x << getCoordsFormIndex(i).y;
//        newCells.emplace_back(new Cell(getCoordsFormIndex(i)));
//    }

//    setNeighbours(newCells, newRowSize, newColumnSize);

//    for(int i = 0; i < m_fieldSize; ++i)
//    {
//        delete m_cells[i];
//    }

//    m_cells = std::move(newCells);
//    m_rows = newRowSize;
//    m_columns = newColumnSize;
//    m_fieldSize = newRowSize * newColumnSize;

//    m_vectorAreas.clear();
//    m_currentPlayer = 0;
//    m_movesMade = 0;
////    m_onlineGame = false;
//}



void FieldModel::dfsStart(int index, int player)
{
//    qDebug() << getCoordsFormIndex(index).x << getCoordsFormIndex(index).y;
    if(index < 0 || index >= m_fieldSize) return;

    ++m_movesMade;

    m_cells[index]->setPlayer(player);
    m_currentOnlinePlayer = player;
//    m_currentPlayer = player;
//    a.emplace_back(Qt::EditRole);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int> { Qt::EditRole });

    if(m_onlineGame && player == m_currentPlayer)
        emit sendPointToServer(index);

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

void FieldModel::setNeighbours(std::vector<Cell *>& cells, int rows, int columns)
{
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
            cells[getIndexFormCoords(Coord{i, j})]->setNeighbours(std::move(neighbours));
//            getCellByCoords(Coord{i, j})->setNeighbours(std::move(neighbours));
        }
    }
}

void FieldModel::setCurrentPlayer(int newCurrentPlayer)
{
    m_currentPlayer = newCurrentPlayer;
}

QDataStream& operator<<(QDataStream& d, const FieldModel& model)
{
    d << model.m_rows << model.m_columns << model.m_fieldSize;
    for(int i = 0; i < model.m_fieldSize; ++i)
    {
        Cell *cell = model.m_cells[i];
        d << cell->getColor();
        d << cell->getCoord().x << cell->getCoord().y;
        d << cell->player();
        d << cell->area();
        d << cell->isCounted();
        d << cell->isClickable();
    }
    d << model.m_vectorAreas.size();

    for(int i = 0; i < model.m_vectorAreas.size(); i++)
    {
        int size = model.m_vectorAreas[i].first.count();
        int player = model.m_vectorAreas[i].second;
        d << size;
        for(int j = 0; j < size; ++j)
        {
            d << model.m_vectorAreas[i].first[j];
        }
        d << player;
    }

    d <<  model.m_currentPlayer;
    return d;
}

QDataStream& operator>>( QDataStream& d, FieldModel& model)
{
    d >> model.m_rows >> model.m_columns >> model.m_fieldSize;

    model.m_cells.resize(model.m_fieldSize);

    for(int i = 0; i < model.m_fieldSize; i++)
    {
        Cell::VERTEXCOLOR cellColor;
        Coord cellCoord;
        int player;
        int area;
        bool isCounted;
        bool isClickable;

        d >> cellColor;
        d >> cellCoord.x;
        d >> cellCoord.y;
        d >> player;
        d >> area;
        d >> isCounted;
        d >> isClickable;

        Cell *cell = new Cell(cellCoord);
        cell->setColor(cellColor);
        cell->setPlayer(player);
        cell->setArea(area);
        cell->setCounted(isCounted);
        cell->setClickable(isClickable);
        model.m_cells[i] = cell;
//        qDebug() << i << "LOAD-----" << model.m_cells[i]->getColor() << model.m_cells[i]->getCoord().x <<
//                    model.m_cells[i]->getCoord().y << model.m_cells[i]->player() << model.m_cells[i]->area() << model.m_cells[i]->isClickable();
    }

    size_t vectorAreasSize = 0;

    model.setNeighbours(model.m_cells, model.m_rows, model.m_columns);

    d >> vectorAreasSize;
//    qDebug() << "AREASLOADED:" << vectorAreasSize;

    model.m_vectorAreas.resize(vectorAreasSize);

    for(size_t i = 0; i < vectorAreasSize; ++i)
    {
        int size = 0;
        int player = 0;
        d >> size;
        model.m_vectorAreas[i].first.resize(size);
        for(int j = 0; j < size; ++j)
        {
            d >> model.m_vectorAreas[i].first[j];
        }
        d >> model.m_vectorAreas[i].second;
    }

    emit model.repaintAllAreas();

    d >> model.m_currentPlayer;

//    int tryda = 0;
//    QColor color;
//    d >> tryda;
//    d >> color;

    return d;
}

