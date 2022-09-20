#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "Point.h"
#include "renderer.h"

class Plot
{

public:

    virtual void print ( std::vector<Point> points, bool clear, Renderer* renderer ) = 0;

    virtual void moveTopLeft (int xPx, int yPx) = 0;

    virtual int getTopLeftXPx () = 0;

    virtual int getTopLeftYPx () = 0;
    
};

#endif