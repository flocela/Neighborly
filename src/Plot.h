#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include "Point.h"
#include "Renderer.h"

// A Plot has an x and y axis. It prints data points (dots) in its plot area.
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

    // Returns the most central-value's pixel.
    virtual int getCenterValueOfXAxisPx () const = 0;

    virtual int getDotSizePx () const = 0;

    // Get x-coordinate of top left corner of plot. This is not the same as x-y cross hairs.
    virtual int getTopLeftXPx () const = 0;

    // Get y-coordinate of top left corner of plot. This is not the same as x-y cross hairs.
    virtual int getTopLeftYPx () const = 0;
    
    // Returns the given allowed space (in the x-direction) from when the plot was constructed,
    // or when setXYSpacePx was last called. Returns the allowed space in the x-direction.
    virtual int getXSpacePx () const = 0;

    virtual int getYSpacePx () const = 0;

    // Returns unit size in x direction
    virtual int getXUnitSizePx () const = 0;

    // Return unit size in y direction
    virtual int getYUnitSizePx () const = 0;

    // The size of the plot in the x direction. This is smaller than or equal to the given x space.
    virtual int sizeXPx () const = 0;

    // The size of the plot in the x direction. This is smaller than or equal to the given y space.
    virtual int sizeYPx () const = 0;

    // Set the top left corner of the plot.
    // Does not change the unitSize of the axes, or the total length of the axes.
    // Does not change the dot size
    virtual void setTopLeft (int xPx, int yPx) = 0;

    virtual void print (
        std::vector<Point> points,
        bool printAxes,
        Renderer* renderer
    ) const = 0;

    // Set the space available from the top left corner of the plot in the x and y directions.
    // Coordinates of top left corner of plot do not change. Plot does not move.
    virtual void setXYSpacePx (int xSpacePx, int ySpacePx) = 0;

};

#endif