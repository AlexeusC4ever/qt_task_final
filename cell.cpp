#include "cell.h"
#include <QDebug>

Cell::Cell(Coord coor, QObject *parent) :
    QObject(parent),
    m_occupiedByPlayer(-1),
    m_coords(coor),
    m_color(VERTEXCOLOR::White),
//    isVisited(false)
    m_clickable(true),
    m_area(0)
{
}

Coord Cell::getCoord() const
{
    return m_coords;
}

Cell::VERTEXCOLOR Cell::getColor() const
{
    return m_color;
}

int Cell::area()
{
    return m_area;
}

void Cell::setArea(int area)
{
    m_area = area;
}

void Cell::setColor(VERTEXCOLOR color_)
{
    m_color = color_;
}



void Cell::setNeighbours(const std::vector<Cell *> &&neighbours_)
{
    for(auto& neigh: m_neighbours)
    {
        qDebug() << neigh->m_coords.x << neigh->m_coords.y;
    }
    m_neighbours = std::move(neighbours_);
}

bool Cell::isClickable()
{
    return m_clickable;
}

void Cell::setClickable(bool click)
{
    m_clickable = click;
}

int Cell::player() const
{
      return m_occupiedByPlayer;
}

void Cell::setPlayer(int player)
{
    m_occupiedByPlayer = player;
}
