#ifndef CELL_H
#define CELL_H

#include <QObject>

struct Coord{
    int x;
    int y;
    bool operator==(Coord& a)
    {
        return (a.x == x && a.y == y);
    }
};

class Cell : public QObject
{
    Q_OBJECT
public:
    Cell(Coord coor, QObject *parent = 0);

    void setCoord(Coord coor);
    Coord getCoord() const;

//    Q_PROPERTY
//    (int occupiedByPlayer
//     READ value
//     WRITE setValue
//     NOTIFY valueChanged)

//    Q_PROPERTY
//    (bool isClickable
//     READ isClickable
//     CONSTANT
//     /*WRITE setClickable
//     NOTIFY clickableChanged*/)

//    Q_PROPERTY
//     (int occupiedByPlayer
//     READ value
//     WRITE setValue
//     NOTIFY valueChanged)

    enum VERTEXCOLOR{
        White, Grey, Black
    };

    VERTEXCOLOR getColor() const;
    int area();
    void setArea(int area);
    void setColor(VERTEXCOLOR color_);
    void setNeighbours(const std::vector<Cell*>&&);
    bool isClickable();
    void setClickable(bool click);
    int player() const;
    void setPlayer(int player);
    bool isCounted();
    void setCounted(bool newCounted);
    void resetCell();

    std::vector<Cell*> m_neighbours;

signals:
//    void valueChanged(/*bool value*/);

private:
    VERTEXCOLOR m_color;
    Coord m_coords;
    int m_occupiedByPlayer;
    int m_area;
    bool m_counted;
    bool m_clickable;

};

#endif // CELL_H
