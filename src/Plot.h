#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "Point.h"
#include "renderer.h"

class Plot
{

public:
    virtual void print (
        std::unordered_map<Color, std::vector<Point>> pointsPerColor,
        bool clear,
        Renderer* renderer) = 0;

    virtual void setTopLeft (int xPx, int yPx) = 0;

    virtual void setXYSpacePx (int xSpacePx, int ySpacePx) = 0;

    virtual int getTopLeftXPx () = 0;

    virtual int getTopLeftYPx () = 0;
    
    virtual int getXSpacePx () = 0;

    virtual int getYSpacePx () = 0;

    virtual int sizeXPx () = 0;

    virtual int sizeYPx () = 0;

    virtual int centerValueOfXAxisPx () = 0;
    
};

#endif