#include "dfsthread.h"
#include <algorithm>

DfsThread::DfsThread(FieldModel *model):
    m_pModel(model),
    m_currentArea(0),
    m_areasCount(1),
    m_pointsToAdd(0)
{
}

void DfsThread::run()
{
//    sleep(10);

    m_currentArea = m_pModel->areasCount() + 1;
//    qDebug() << m_currentArea;

    dfs(m_pStartCell);

    for(int i = m_maxLeftCoordinate; i <= m_maxRightCoordinate; ++i)
    {
        for(int j = m_maxTopCoordinate; j <= m_maxBottomCoordinate; ++j)
        {
//            qDebug() << "CLEAR" << i << j;
            Cell* cellForClear = m_pModel->getCellByCoords(Coord{i, j});
            cellForClear->setColor(Cell::VERTEXCOLOR::White);
//            cellForClear->isVisited = false;
        }
    }

    if(m_currentArea == m_areasCount && m_pointsToAdd)
        ++m_areasCount;

    emit dfsFinished();
}

int DfsThread::pointsToAdd() const
{
    return m_pointsToAdd;
}

void DfsThread::resetForDfs()
{
    m_vertexesInCicle.clear();
    m_finalVertexesInCicle.clear();
    m_lengthOfCicle = 0;
    m_finalLengthOfCicle = 0;
    m_maxBottomCoordinate = 0;
    m_maxTopCoordinate = m_pModel->rowCountForQml();
    m_maxRightCoordinate = 0;
    m_maxLeftCoordinate = m_pModel->columnCountForQml();
    m_finalMountOfPointsInArea = 0;
    m_vertexesForIncludeToCycle.clear();
    m_rememberArea = 0;
    m_meetAreaFlagBegin = false;
    m_meetAreaFlagEnd = false;
    m_pointsToAdd = 0;
}

int DfsThread::lengthOfCycleCount()
{
    auto lastVertexInCycle = std::prev(m_vertexesInCicle.end());
    int bufcounter = 1;

    for(auto& vertex: m_vertexesInCicle)
    {
        if(vertex.x == lastVertexInCycle->x &&
                vertex.y == lastVertexInCycle->y)
            break;
        ++bufcounter;
    }
    return m_vertexesInCicle.size() - bufcounter;
}

std::vector<Coord> DfsThread::getVertexesOfCycle()
{
    return m_finalVertexesInCicle;
}

int DfsThread::getNumberOfCurrentCycle()
{
    return m_currentArea;
}

std::vector<Coord> DfsThread::getAreaForRepaint()
{
    return m_areaToRepaint;
}

void DfsThread::searchForBoundaryVertexes(Coord vertex)
{
    int x = vertex.x;
    int y = vertex.y;

    if(x > m_maxRightCoordinate)
        m_maxRightCoordinate = x;

    if(x < m_maxLeftCoordinate)
        m_maxLeftCoordinate = x;

    if(y > m_maxBottomCoordinate)
        m_maxBottomCoordinate = y;

    if(y < m_maxTopCoordinate)
        m_maxTopCoordinate = y;
}

std::vector<Coord> DfsThread::deleteExtraVertexes(std::vector<Coord> &cycle, int realLength)
{
    int difference = cycle.size() - realLength - 1;
    std::vector<Coord> rightCycle(realLength);
    for(int i = 0; i < realLength; ++i)
    {
        rightCycle[i] = cycle[i + difference];
    }
    return rightCycle;
}



bool DfsThread::isValidCycle()
{
    if(m_lengthOfCicle <= 3){
        return false;
    }

    m_maxLocalBottomCoordinate = 0;
    m_maxLocalTopCoordinate = m_pModel->rowCountForQml();
    m_maxLocalRightCoordinate = 0;
    m_maxLocalLeftCoordinate = m_pModel->columnCountForQml();
    m_mountOfPointsInArea = 0;

    int startVertex = m_vertexesInCicle.size() - m_lengthOfCicle - 1;
    for(int i = 0; i <= m_lengthOfCicle; ++i)
    {
        int x = m_vertexesInCicle[i + startVertex].x;
        int y = m_vertexesInCicle[i + startVertex].y;

        if(x > m_maxLocalRightCoordinate)
            m_maxLocalRightCoordinate = x;

        if(x < m_maxLocalLeftCoordinate)
            m_maxLocalLeftCoordinate = x;

        if(y > m_maxLocalBottomCoordinate)
            m_maxLocalBottomCoordinate = y;

        if(y < m_maxLocalTopCoordinate)
            m_maxLocalTopCoordinate = y;
    }

    if(m_maxLocalBottomCoordinate - m_maxLocalTopCoordinate < 2 ||
            m_maxLocalRightCoordinate - m_maxLocalLeftCoordinate < 2){
        return false;
    }

//        if(m_mountOfPointsInArea < m_finalMountOfPointsInArea)
//            return false;
//        else if(m_mountOfPointsInArea == m_finalMountOfPointsInArea)
            if(m_lengthOfCicle < m_finalLengthOfCicle)
                return false;

        return true;
}

int DfsThread::childrenInsideAreaCount(std::vector<Coord> &area)
{
    int maxLeft = m_pModel->columnCountForQml();
    int maxRight = 0;
    int maxTop = m_pModel->rowCountForQml();
    int maxBottom = 0;


    for(int i = 0; i < area.size(); ++i)
    {
        int x = area[i].x;
        int y = area[i].y;

        if(x > maxRight)
            maxRight = x;

        if(x < maxLeft)
            maxLeft = x;

        if(y > maxBottom)
            maxBottom = y;

        if(y < maxTop)
            maxTop = y;
    }

    int children = 0;
    for(int i = maxLeft + 1; i <= maxRight - 1; ++i)
    {
        bool areaOpened = false;
        for(int j = maxTop; j <= maxBottom; ++j)
        {
            Cell *insideCell = m_pModel->getCellByCoords(Coord{i, j});
            if(insideCell->getColor() != Cell::VERTEXCOLOR::White &&
                    insideCell->player() == m_pModel->getCellByCoords(area[0])->player())
            {
                if(!areaOpened)
                    areaOpened = true;
                else
                    areaOpened = false;
            }
            else if(areaOpened && !insideCell->isCounted() &&
                    insideCell->player() != m_pModel->getCellByCoords(area[0])->player() &&
                    insideCell->player() != -1){
                ++children;
                insideCell->setCounted(true);
                makeCellNonClickable(insideCell);
//                qDebug() << "COUNT";
            }
            else if(insideCell->getColor() == Cell::VERTEXCOLOR::White
                    && areaOpened)
            {
                makeCellNonClickable(insideCell);
            }
        }
        //do a traversing from different sides to count all
        areaOpened = false;

        for(int j = maxBottom; j >= maxTop; --j)
        {
            Cell *insideCell = m_pModel->getCellByCoords(Coord{i, j});
            if(insideCell->getColor() != Cell::VERTEXCOLOR::White)
            {
                if(!areaOpened)
                    areaOpened = true;
                else
                    areaOpened = false;
            }
            else if(areaOpened && !insideCell->isCounted() &&
                    insideCell->player() != m_pModel->getCellByCoords(area[0])->player() &&
                    insideCell->player() != -1){
                ++children;
                insideCell->setCounted(true);
                makeCellNonClickable(insideCell);
            }
            else if(insideCell->getColor() == Cell::VERTEXCOLOR::White
                    && areaOpened)
            {
                makeCellNonClickable(insideCell);
            }
        }
    }

    return children;

//        qDebug() << "CHILDREN:" << m_mountOfPointsInArea;
}

void DfsThread::dfs(Cell *vertex)
{
    if(isInterruptionRequested()) return;
    m_vertexesInCicle.emplace_back(vertex->getCoord());

    searchForBoundaryVertexes(vertex->getCoord());
    vertex->setColor(Cell::VERTEXCOLOR::Grey);

    auto neighbours = vertex->m_neighbours;

    for(int i = 0; i < neighbours.size(); ++i)
    {
        if(isInterruptionRequested()) return;

        if(neighbours[i]->player() != vertex->player() ||
                neighbours[i]->getCoord() == m_vertexesInCicle[m_vertexesInCicle.size() - 2])
            continue;

        if(neighbours[i]->getColor() == Cell::VERTEXCOLOR::White)
        {
            if(neighbours[i]->area() &&
                    neighbours[i]->player() == vertex->player())
                m_currentArea = neighbours[i]->area();

            dfs(neighbours[i]);

        }

        else if(neighbours[i]->getColor() == Cell::VERTEXCOLOR::Grey)
        {
            m_vertexesInCicle.emplace_back(neighbours[i]->getCoord());
            m_lengthOfCicle = lengthOfCycleCount();
            if(isValidCycle())
            {
                m_finalLengthOfCicle = m_lengthOfCicle;
                m_finalVertexesInCicle = m_vertexesInCicle;
                m_finalMountOfPointsInArea = m_mountOfPointsInArea;

                m_finalVertexesInCicle = std::move(
                            deleteExtraVertexes(m_finalVertexesInCicle, m_finalLengthOfCicle));
                m_pointsToAdd = childrenInsideAreaCount(m_finalVertexesInCicle);

                m_pModel->getCoordsOfOccupiedArea();

                m_lengthOfCicle = m_vertexesInCicle.size();
            }

            m_vertexesInCicle.pop_back();
        }
    }

    m_vertexesInCicle.pop_back();
    vertex->setColor(Cell::VERTEXCOLOR::White);

}

void DfsThread::makeCellNonClickable(Cell *cell)
{
    m_pModel->makeCellNonClickable(cell);
}



void DfsThread::dfsStart(int index)
{
    if(isRunning()) return;

    resetForDfs();
    m_pStartCell = m_pModel->getCells()[index];

    QThread::start();
}




//        vertex->setColor(Cell::VERTEXCOLOR::White/*Black*/);
