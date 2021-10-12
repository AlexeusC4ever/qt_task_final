#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include "cell.h"
#include <QAbstractListModel>
#include <vector>
#include <QPoint>

using Area = std::pair<QVector<QPoint>, int>;
using VectorArea = std::vector<Area>;

class DfsThread;

class FieldModel : public QAbstractListModel
{
    Q_OBJECT

public:
    static constexpr size_t defaultFieldDimension {10};
    explicit FieldModel(const size_t rows = defaultFieldDimension,
                        const size_t columns = defaultFieldDimension,
                        QObject *parent = 0);
    ~FieldModel();

    enum{
        clickRole = Qt::UserRole
    };

    Q_PROPERTY(
        int areasCount
        READ areasCount
        CONSTANT)

    Q_PROPERTY(
        int onlineGame
        READ onlineGame
        CONSTANT)

//    Q_PROPERTY(
//        QVector<QPoint> coords
//        READ getCoordsOfOccupiedArea
//        CONSTANT)

    Q_PROPERTY(
        int columns
        READ columnCountForQml
        CONSTANT)

    Q_PROPERTY(
        int rows
        READ rowCountForQml
        CONSTANT)

    std::vector<Cell *> getCells();
    int fieldSize();
    int columnCountForQml();
    int rowCountForQml();
//    QVector<QPoint> getCoordsOfOccupiedArea();
    Coord getCoordsFormIndex(int index) const;
    int getIndexFormCoords(Coord index) const;
    Cell *getCellByCoords(Coord coords);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void makeCellNonClickable(Cell *cell);
    int areasCount();
    void setCurrentPlayer(int newCurrentPlayer);
    int currentPlayer() const;
//    QVector<QPoint> *getAreaForIncludeNewVertexes(int area);
    void resetModel(int newRowSize, int newColumnSize);
    Q_INVOKABLE void dfsStart(int index, int player);
    Q_INVOKABLE QVector<QPoint> getAreaForPaint(int area);
    Q_INVOKABLE int getAreaOwner(int area);
//    Q_INVOKABLE void saveModel(QString &fileName);
    void setNeighbours(std::vector<Cell *>& cells, int rows, int columns);
    friend QDataStream& operator>>( QDataStream& d, FieldModel& model);
    friend QDataStream& operator<<( QDataStream& d, const FieldModel& model);

    void setOnlineGame(bool newOnlineGame);

    bool onlineGame() const;

signals:
    Q_INVOKABLE void changePlayer();
    Q_INVOKABLE void sendCoordsOfOccupiedArea();
    Q_INVOKABLE void repaintAllAreas();
    Q_INVOKABLE void repaintAll();
    void sendPointToServer(int index);
    void addPoints(int player, int points);
    void gameOver();

public slots:
    void getCoordsOfOccupiedArea();
    void onDfsFinished();
//    void addVertexesToCycle(int cycle);    

private:
    std::vector<Cell *> m_cells;
    VectorArea m_vectorAreas;
    DfsThread *thr;
    size_t m_rows;
    size_t m_columns;
    size_t m_fieldSize;
    int m_currentPlayer;
    int m_movesMade;
    int m_currentOnlinePlayer;
    bool m_onlineGame;

};


#endif // FIELDMODEL_H
