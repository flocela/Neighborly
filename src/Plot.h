#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "Point.h"
#include "renderer.h"

// A Plot has an x and y axis. It prints data points (dots) in its area.
class Plot
{

public:
    virtual void print (
        std::vector<Point> points,
        bool printAxes,
        Renderer* renderer
    ) const = 0;

    // set the top left corner of the plot
    virtual void setTopLeft (int xPx, int yPx) = 0;

    // set the space available from the top left corner in the x and y directions
    virtual void setXYSpacePx (int xSpacePx, int ySpacePx) = 0;

    virtual int getTopLeftXPx () const = 0;

    virtual int getTopLeftYPx () const = 0;
    
    virtual int getXSpacePx () const = 0;

    virtual int getYSpacePx () const = 0;

    // returns the size of the plot in the x direction.
    virtual int sizeXPx () const = 0;

    // returns the size of the plot in the y directions.
    virtual int sizeYPx () const = 0;

    // the x axis has values. returns the most centarl value's pixel.
    virtual int getCenterValueOfXAxisPx () const = 0;
    
};

#endif