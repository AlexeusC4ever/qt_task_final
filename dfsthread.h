#ifndef DFSTHREAD_H
#define DFSTHREAD_H

#include "fieldmodel.h"
#include <QThread>
//#include <vector>

struct Coord;
class Cell;
class FieldModel;
class vector;

class DfsThread : public QThread
{
    Q_OBJECT

public:
    DfsThread(FieldModel *model);
    void resetForDfs();
    void dfs(Cell* vertex);
    void dfsInsideOccupiedArea(Cell *vertex);
    void makeCellNonClickable(Cell *cell);
    void includeNewVertexesToOldCycle();
    void dfsStart(int index);
    std::vector<Coord> deleteExtraVertexes(std::vector<Coord> &cycle, int realLength);
    void searchForBoundaryVertexes(Coord vertex);
    bool isValidCycle();
    int childrenInsideAreaCount(std::vector<Coord> &area);
    int lengthOfCycleCount();
    std::vector<Coord> getVertexesOfCycle();
    int getNumberOfCurrentCycle();
    std::vector<Coord> getAreaForRepaint();
    int pointsToAdd() const;
    std::mutex m_repaintMutex;

signals:
    void dfsFinished();
    void cycleIsReadyForRepaint(int area);

protected:
    void run() override;

private:
    std::vector<Coord> m_vertexesInCicle;
    std::vector<Coord> m_finalVertexesInCicle;
    std::vector<Coord> m_vertexesForIncludeToCycle;
    std::vector<Coord> m_areaToRepaint;
    FieldModel *m_pModel;
    Cell *m_pStartCell;
    Cell *m_pStartIncludeCell;
    Cell *m_pEndIncludeCell;
    int m_currentArea;
    int m_areasCount;
    int m_finalMountOfPointsInArea;
    int m_mountOfPointsInArea;
//    Cell *m_previousVertex;
    int m_lengthOfCicle;
    int m_finalLengthOfCicle;
    int m_maxTopCoordinate;             //these 4 variables will be used to clean up the area where we do dfs
    int m_maxBottomCoordinate;
    int m_maxLeftCoordinate;
    int m_maxRightCoordinate;
    int m_maxLocalRightCoordinate;
    int m_maxLocalTopCoordinate;             //these 4 variables will be used to clean up local area where we do dfs
    int m_maxLocalBottomCoordinate;
    int m_maxLocalLeftCoordinate;
    int m_rememberArea;
    int m_pointsToAdd;
    bool m_meetAreaFlagBegin;
    bool m_meetAreaFlagEnd;

};

#endif // DFSTHREAD_H
