#ifndef POINT_H
#define POINT_H

#include "Color.h"

class Point
{
public:
    Point(
        double x,
        double y,
        Color color,
        std::string mood
    ):
    _x{x},
    _y{y},
    _color{color},
    _mood{mood}
    {}

    double x () {return _x;}
    double y () {return _y;}
    Color color () { return _color;}
    std::string mood () { return _mood;}

private:
    double _x;
    double _y;
    Color _color;
    std::string _mood;

};

#endif