#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "Point.h"
#include "Renderer.h"

// A Plot has an x and y axis. It prints data points (dots) in its area.
class Plot
{
protected:
    Plot () = default;
    Plot (const Plot& o) = default;
    Plot (Plot&& o) noexcept = default;
    Plot& operator= (const Plot& o) = default;
    Plot& operator= (Plot&& o) noexcept = default;

public:
    virtual ~Plot() noexcept = default;
    // the x axis has values. returns the most centarl value's pixel.
    virtual int getCenterValueOfXAxisPx () const = 0;

    virtual int getDotSizePx () const = 0;

    // get X value of top left corner of plot. This is not the same as x-y cross hairs
    virtual int getTopLeftXPx () const = 0;

    // get Y value of top left corner of plot. This is not the same as x-y cross hairs.
    virtual int getTopLeftYPx () const = 0;
    
    // returns the given space (x-direction) from when the plot was constructed,
    // or when setXYSpacePx was called.
    virtual int getXSpacePx () const = 0;

    virtual int getYSpacePx () const = 0;

    // returns unit size in x direction
    virtual int getXUnitSizePx () const = 0;

    // return unit size in y direction
    virtual int getYUnitSizePx () const = 0;

    // the size of the plot in the x direction. This is smaller than or equal to the given x space.
    virtual int sizeXPx () const = 0;

    // the size of the plot in the x direction. This is smaller than or equal to the given y space.
    virtual int sizeYPx () const = 0;

    // set the top left corner of the plot
    // does not change the unitSize of the axes, or the total length of the axes.
    // does not change the dot size
    virtual void setTopLeft (int xPx, int yPx) = 0;

    virtual void print (
        std::vector<Point> points,
        bool printAxes,
        Renderer* renderer
    ) const = 0;

    // set the space available from the top left corner in the x and y directions
    // top left x and y pixel values do not change.
    virtual void setXYSpacePx (int xSpacePx, int ySpacePx) = 0;

};

#endif