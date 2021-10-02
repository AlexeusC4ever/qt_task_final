#include "dfsthread.h"
#include <algorithm>

DfsThread::DfsThread(FieldModel *model):
    m_pModel(model),
    m_currentArea(0),
    m_areasCount(1)
{
}

void DfsThread::run()
{
//    sleep(10);

    m_currentArea = m_areasCount;

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

    if(m_meetAreaFlagBegin && m_meetAreaFlagEnd)
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
}

int DfsThread::lengthOfCycleCount()
{
    auto lastVertexInCycle = std::prev(m_vertexesInCicle.end());
//    m_lengthOfCicle = 0;
    int bufcounter = 1;

    for(auto& vertex: m_vertexesInCicle)
    {
        if(vertex.x == lastVertexInCycle->x &&
                vertex.y == lastVertexInCycle->y)
            break;
        ++bufcounter;
    }

//    m_lengthOfCicle = m_vertexesInCicle.size() - bufcounter - 1;
//    qDebug() << bufcounter;
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

//    if(m_lengthOfCicle < m_finalLengthOfCicle ||
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
//        qDebug() << "m_maxBottomCoordinate - m_maxTopCoordinate < 2 ||";
        return false;
    }

//    m_mountOfPointsInArea = childrenInsideAreaCount(m_vertexesInCicle);

//        for(int i = m_maxLocalLeftCoordinate + 1; i <= m_maxLocalRightCoordinate - 1; ++i)
//        {
//            bool areaOpened = false;
//            for(int j = m_maxLocalTopCoordinate; j <= m_maxLocalBottomCoordinate; ++j)
//            {
//                Cell *insideCell = m_pModel->getCellByCoords(Coord{i, j});
//                if(insideCell->getColor() != Cell::VERTEXCOLOR::White)
//                {
//                    if(!areaOpened)
//                        areaOpened = true;
//                    else
//                        areaOpened = false;
//                }
//                else if(areaOpened){
//                    ++m_mountOfPointsInArea;
//    //                if(insideCell->player() && insideCell->player() != )   ДОБАВЛЕНИЕ ОЧКОВ
//                    makeCellNonClickable(insideCell);
//                }
//            }
//            //do a traversing from different sides to count all
//            areaOpened = false;
//            for(int j = m_maxLocalBottomCoordinate; j <= m_maxLocalTopCoordinate; --j)
//            {
//                Cell *insideCell = m_pModel->getCellByCoords(Coord{i, j});
//                if(insideCell->getColor() != Cell::VERTEXCOLOR::White)
//                {
//                    if(!areaOpened)
//                        areaOpened = true;
//                    else
//                        areaOpened = false;
//                }
//                else if(areaOpened){
//                    if(insideCell->isClickable())
//                    {
//                        ++m_mountOfPointsInArea;
//    //                if(insideCell->player() && insideCell->player() != )   ДОБАВЛЕНИЕ ОЧКОВ
//                        makeCellNonClickable(insideCell);
//                    }
//                }
//            }
//        }



//        qDebug() << "CHILDREN:" << m_mountOfPointsInArea;

        if(m_mountOfPointsInArea < m_finalMountOfPointsInArea)
            return false;
        else if(m_mountOfPointsInArea == m_finalMountOfPointsInArea)
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
            if(insideCell->getColor() != Cell::VERTEXCOLOR::White)
            {
                if(!areaOpened)
                    areaOpened = true;
                else
                    areaOpened = false;
            }
            else if(areaOpened && insideCell->isClickable()){
                ++children;
//                if(insideCell->player() && insideCell->player() != )   ДОБАВЛЕНИЕ ОЧКОВ
                makeCellNonClickable(insideCell);
            }
            if(insideCell->player() != m_pModel->getCellByCoords(area[0])->player())
                ++children;
        }
        //do a traversing from different sides to count all
        areaOpened = false;
        for(int j = maxBottom; j <= maxTop; --j)
        {
            Cell *insideCell = m_pModel->getCellByCoords(Coord{i, j});
            if(insideCell->getColor() != Cell::VERTEXCOLOR::White)
            {
                if(!areaOpened)
                    areaOpened = true;
                else
                    areaOpened = false;
            }
            else if(areaOpened && insideCell->isClickable()){
                ++children;
//                if(insideCell->player() && insideCell->player() != )   ДОБАВЛЕНИЕ ОЧКОВ
                makeCellNonClickable(insideCell);
            }
        }
    }

    return children;

//        qDebug() << "CHILDREN:" << m_mountOfPointsInArea;
}

void DfsThread::includeNewVertexesToOldCycle()
{
    QVector<QPoint> *points = m_pModel->getAreaForIncludeNewVertexes(m_rememberArea - 1);

    std::vector<Coord> firstLoop;
    std::vector<Coord> secondLoop;
//    firstLoop.reserve(m_vertexesForIncludeToCycle.size());
//    secondLoop.reserve(m_vertexesForIncludeToCycle.size());
    Cell *startCell = m_pStartIncludeCell;
    Cell *endCell = m_pEndIncludeCell;

    int error = 0;
    int start = -1;
    int end = -1;

    for(int i = 0; i <= points->count(); ++i)
    {
        if(i == points->count()) i = 0;

        if((*points)[i].x() == startCell->getCoord().x &&
                (*points)[i].y() == startCell->getCoord().y)
        {
            start = i;
            if(end != -1)
                break;
        }

        else if((*points)[i].x() == endCell->getCoord().x &&
                (*points)[i].y() == endCell->getCoord().y)
        {
            end = i;
            if(start != -1)
                break;
        }

    }

//    bool backFlag = (end < start);

//    std::copy(m_vertexesForIncludeToCycle.begin(),
//              m_vertexesForIncludeToCycle.end(), firstLoop.begin());
//    std::copy(m_vertexesForIncludeToCycle.begin(),
//              m_vertexesForIncludeToCycle.end(), secondLoop.begin());

    auto startIter = m_vertexesForIncludeToCycle.begin();
    auto endIter = m_vertexesForIncludeToCycle.end();
    int counter = 0;
    while(startIter != endIter)
    {
        firstLoop.emplace_back(Coord{startIter->x, startIter->y});
        secondLoop.emplace_back(Coord{startIter->x, startIter->y});
//        qDebug() << startIter->x << startIter->y;
        ++startIter;
    }

    for(int i = end; i <= points->size(); ++i)
    {
        if(i == points->size()) {
            if(error){
                qDebug() << "can't find1 start";
            }
            i = 0;
            error = 1;
        }

        firstLoop.emplace_back(Coord{(*points)[i].x(), (*points)[i].y()});

        if(i == start) break;

    }

    error = 0;

    for(int i = end; i >= -1; --i)
    {
        if(i == -1) {
            if(error){
                qDebug() << "can't find1 start";
            }
            i = points->size() - 1;
            error = 1;
        }

        secondLoop.emplace_back(Coord{(*points)[i].x(), (*points)[i].y()});

        if(i == start) break;

    }

    int childrenFirstLoop = childrenInsideAreaCount(firstLoop);

    int childrenSecondLoop = childrenInsideAreaCount(firstLoop);

//    std::lock_guard<std::mutex> mute(m_repaintMutex);
    m_repaintMutex.lock();

    if(childrenSecondLoop > childrenFirstLoop)
    {
        m_areaToRepaint = secondLoop;
        m_pointsToAdd = childrenFirstLoop;
    }
    else
    {
        m_areaToRepaint = firstLoop;
        m_pointsToAdd = childrenSecondLoop;
    }


//    for()
    emit cycleIsReadyForRepaint(m_rememberArea);
//    mute.~lock_guard();

//    emit dfsFinished();
//    sleep(5);

//    qDebug() << "FINISH";
}

void DfsThread::dfs(Cell *vertex)
{
//    vertex->isVisited = true;
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
        {
            continue;
        }

        if(neighbours[i]->getColor() == Cell::VERTEXCOLOR::White)
        {
//            if(neighbour->area())
//            {
////                m_vertexesForIncludeToCycle.emplace_back(vertex->getCoord());
//                if(!m_meetAreaFlagBegin) {
//                    m_vertexesForIncludeToCycle.emplace_back(vertex->getCoord());
//                    m_rememberArea = neighbour->area();
//                    qDebug() <<  neighbour->area();
//                    m_pStartIncludeCell = neighbour;
//                    m_meetAreaFlagBegin = true;
//                    qDebug() << "MakeTRUE";
//                }
//                else{
//                    if(!(vertex->getCoord() == m_vertexesForIncludeToCycle[0])){
//                        m_meetAreaFlagEnd = true;
//                        m_vertexesForIncludeToCycle.emplace_back(vertex->getCoord());
//                        qDebug() << "END";
//                     }
//                    m_pEndIncludeCell = neighbour;
//                    includeNewVertexesToOldCycle();
////                    m_meetAreaFlagBegin = false;
//                }
//                continue;
//            }

//            else if(m_meetAreaFlagBegin && !m_meetAreaFlagEnd)
//            {
//                qDebug() << "ADDDD";
//                 m_vertexesForIncludeToCycle.emplace_back(vertex->getCoord());
//            }

            if(neighbours[i]->area())
                m_currentArea = neighbours[i]->area();

            dfs(neighbours[i]);

//            if(!m_meetAreaFlagEnd)
//                m_vertexesForIncludeToCycle.pop_back();
        }

        /**/else if(neighbours[i]->getColor() == Cell::VERTEXCOLOR::Grey)
        {

            m_vertexesInCicle.emplace_back(neighbours[i]->getCoord());
            m_lengthOfCicle = lengthOfCycleCount();
            if(isValidCycle())
            {
                m_finalLengthOfCicle = m_lengthOfCicle;
                m_finalVertexesInCicle = m_vertexesInCicle;
                m_finalMountOfPointsInArea = m_mountOfPointsInArea;

//                if(m_vertexesInCicle.size() - 1 - m_lengthOfCicle > 0)
                m_finalVertexesInCicle = std::move(
                            deleteExtraVertexes(m_finalVertexesInCicle, m_finalLengthOfCicle));
                m_pointsToAdd = childrenInsideAreaCount(m_finalVertexesInCicle);

//                childrenInsideAreaCount();

                m_lengthOfCicle = m_vertexesInCicle.size();
            }

            m_vertexesInCicle.pop_back();
        }
    }
    m_vertexesInCicle.pop_back();

//    if(m_meetAreaFlagBegin && !m_meetAreaFlagEnd)
//        vertex->setColor(Cell::VERTEXCOLOR::Black);
//    else
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


