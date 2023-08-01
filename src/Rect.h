#ifndef RECT_H
#define RECT_H

#include <string>
#include <vector>

// holds information for rendering block
struct Rect
{
    int _x__px; // top left corner x-coordinate of pixel
    int _y__px; // top left corner y-coordinate of pixel
    int width;
    int height;
};

#endif