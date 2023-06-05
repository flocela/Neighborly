#ifndef POINT_H
#define POINT_H

#include "Color.h"
#include <vector>

class Point
{
public:
    Point (double x, double y, Color color)
    : _x{x},
      _y{y},
      _color{color},
      _rgba{_the_color_rgba[color]}
    {}

    Point () = delete;
    Point (const Point& o) = default;
    Point (Point&& o) noexcept = default;
    Point& operator= (const Point& o) = default;
    Point& operator= (Point&& o) noexcept = default;
    ~Point () = default;

    double x () {return _x;}
    double y () {return _y;}
    
    Color color () { return _color;}
    std::vector<uint8_t> rgba () { return _rgba;}

private:
    double _x;
    double _y;
    Color _color;
    std::vector<uint8_t> _rgba;

};

#endif