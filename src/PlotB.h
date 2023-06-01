#ifndef PLOT_B_H
#define PLOT_B_H

#include "AxisFormat.h"
#include "AxisLeftToRightT.h"
#include "AxisTopToBottomL.h"
#include "Coordinate.h"
#include "Point.h"
#include "Plot.h"
#include "PlotFormat.h"

// x-axis runs horizontally from left to right, labels are on top of axis
// y-axis runs vertically from bottom to top, labels are on the left of the axis
class PlotB: public Plot
{
public:
    PlotB ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot, not the same as where x and y axes cross
        int topLeftYPx, // top left corner of plot, not the same as where x and y axes cross
        int minX,
        int maxX,
        int minY, 
        int maxY,
        int xSpacePx,
        int ySpacePx
    );

    // Creates a plot with top left corner at (0,0) pixels.
    // Size of plot is zero in x and y directions.
    // This is a temporary plot. Use setTopLeft() and setXYSpacePx() to finish it.
    PlotB (
        PlotFormat plotFormat,
        int minX,
        int maxX,
        int minY, 
        int maxY
    );

    PlotB () = delete;
    PlotB (const PlotB& o) = default;
    PlotB (PlotB&& o) noexcept = default;
    PlotB& operator= (const PlotB& o) = default;
    PlotB& operator=(PlotB&& o) noexcept = default;
    ~PlotB () = default;

    int getCenterValueOfXAxisPx () const override;

    int getDotSizePx () const override;

    int getTopLeftXPx () const override;

    int getTopLeftYPx () const override;

    int getXSpacePx () const override;

    int getYSpacePx () const override;

    int getXUnitSizePx () const override;

    int getYUnitSizePx () const override;

    int sizeXPx () const override;

    int sizeYPx () const override;

    void print (
        std::vector<Point> points,
        bool clear,
        Renderer* renderer) const override;

    void setTopLeft (int xPx, int yPx) override; 

    void setXYSpacePx (int xSpacePx, int ySpacePx) override;

private:

    AxisFormat _axis_format_x;
    AxisFormat _axis_format_y;

    // requested minimum unit size. //TODO maybe not have this min_unit_size
    int _min_unit__px = 6;

    // _start_offset_m is used to determine space before the first values (_min_x or _min_y).
    // length of space is _start_offset_m * _unit_space__px. 
    int _start_offset_m;

    // _end_offset_m is used to determine space after the last value (_max_x or _max_y).
    // length of space is _end_offset_m * _unit_space__px.
    int _end_offset_m;

    // top left corner of plot. This is not at the x-y axes' cross hairs. it takes into
    // account the width of the y-axis labels.
    int _top_left_x__px = 0;
    int _top_left_y__px = 0;

    // smallest values on the axes with data.
    int _min_x;
    int _min_y;

    // largest values on the axes with data.
    // Note: the axes stretch past the largest value with data.
    // the largest value on the axes will be _max_y + (_end_offset_m * unit size ).
    int _max_x;
    int _max_y;
    
    // given allowable space in the x and y directions
    int _x_space__px;
    int _y_space__px;

    int _x_diff; // max minus min axis values
    int _y_diff; // max minus min axis values
    int _unit__px; // pixels per unit

    // dot represents a value. the dot is a colored square, same length in the x and y directions.
    // dot is inside the unit.
    // _dot__px is the length of the square
    int _dot__px;

    // where x and y axes cross
    int _cross_x__px; 
    int _cross_y__px; 

    AxisLeftToRightT _x_axis;
    AxisTopToBottomL _y_axis;

    // only print axes once, they don't change.
    mutable bool _printed_axes = false;

    // Use the given allowable spaces in the x and y directions and the number of units in the axes
    // to determine the unit size.
    int calcUnitSizePx () const;

    // returns length of the square dot. the length is 1/2 the _unit__px
    int calcDotSizePx () const;

    // retuns x value of cross hairs.
    int calcCrossXPx (int topLeftX) const;

    // returns y values of cross hairs.
    int calcCrossYPx (int topLeftY) const;
};

#endif