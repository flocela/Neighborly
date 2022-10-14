#ifndef POINT_H
#define POINT_H

#include "Color.h"
#include <vector>

// TODO point doesn't need mood
class Point
{
public:
    Point(
        double x, // TODO why do these have to doubles?
        double y,
        Color color // TODO, color isn't used.
    ):
    _x{x},
    _y{y},
    _color{color},
    _rgba{_the_color_rgba[color]} // TODO make rgba a reference
    {}

    double x () {return _x;}
    double y () {return _y;}
    Color color () { return _color;}
    std::vector<int> rgba () { return _rgba;}

private:
    double _x;
    double _y;
    Color _color; // maybe just hold rgba, don't hold color since not asked for ever.
    std::vector<int> _rgba;

};

#endif