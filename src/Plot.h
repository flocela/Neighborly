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

    // Returns the x-axis' most central-value's pixel.
    virtual int getCenterValueOfXAxisPx () const = 0;

    virtual int getDotSizePx () const = 0;

    // Get x-coordinate of top left corner of plot. This is not the same as x-y cross hairs.
    virtual int getTopLeftXPx () const = 0;

    // Get y-coordinate of top left corner of plot. This is not the same as x-y cross hairs.
    virtual int getTopLeftYPx () const = 0;
    
    // Returns the allowed space (in the x-direction). This value was given when the plot was
    // constructed or updated when setXYSpacePx was last called.
    virtual int getXSpacePx () const = 0;

    // Returns the allowed space (in the y-direction). This value was given when the plot was
    // constructed or updated when setXYSpacePx was last called.
    virtual int getYSpacePx () const = 0;

    // Returns unit size in x direction.
    virtual int getXUnitSizePx () const = 0;

    // Return unit size in y direction.
    virtual int getYUnitSizePx () const = 0;

    // The size of the plot in the x direction. This is smaller than or equal to the allowed space.
    virtual int sizeXPx () const = 0;

    // The size of the plot in the y direction. This is smaller than or equal to the allowed space.
    virtual int sizeYPx () const = 0;

    virtual void print (
        std::vector<Point> points,
        bool printAxes,
        Renderer* renderer
    ) const = 0;

    // Sets the top left corner of the plot and sets the available space in the x and y directions.
    virtual void setPlot (
        int topLeftCornerXPx,
        int topLeftCornerYPx,
        int xSpacePx,
        int ySpacePx) = 0;

};

#endif