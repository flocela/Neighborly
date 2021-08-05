#include "Coordinate.h"

Coordinate::Coordinate (int x, int y): _x{x}, _y{y}
{}

int Coordinate::getX () const
{
    return _x;
}

int Coordinate::getY () const
{
    return _y;
}

std::string Coordinate::toStr() const
{
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
}

bool Coordinate::operator< (const Coordinate& a) const
{
    if (_y == a._y)
        return _x < a._x;
    else
        return _y < a._y;
    
}

std::ostream& operator<<(std::ostream& os, Coordinate const& v)
{
    os << "(" << v._x << ", " << v._y << ")"; // This needs to be tested
    return os;
}

bool Coordinate::operator==(const Coordinate& c) const
{
    return _x == c.getX() && _y == c.getY();
}

bool Coordinate::operator!=(const Coordinate& c) const
{
    return _x != c.getX() || _y != c.getY();
}

