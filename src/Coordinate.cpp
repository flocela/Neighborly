#include "Coordinate.h"

using namespace std;

Coordinate::Coordinate (int x, int y): _x{x}, _y{y}
{}


bool Coordinate::operator< (const Coordinate& a) const
{
    if (_y == a._y)
        return _x < a._x;
    else
        return _y < a._y;
    
}

std::string Coordinate::toStr() const
{
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
}

std::ostream& operator<<(std::ostream& os, Coordinate const& v)
{
    os << "(" << v._x << ", " << v._y << ")";
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

