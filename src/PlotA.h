#ifndef PLOT_A_H
#define PLOT_A_H

#include <utility>
#include "AxisBottomToTopL.h"
#include "AxisFormat.h"
#include "AxisLeftToRightB.h"
#include "Color.h"
#include "Coordinate.h"
#include "Plot.h"
#include "PlotFormat.h"
#include "Point.h"
#include "unordered_map"

// Plot contains the x and y axis, their labels, and the data points inside the graph.
// x-axis runs horizontally on the bottom of the plot (left to right)
// y-axis runs vertically on the left (bottom to top) 
class PlotA: public Plot
{
public:

    PlotA ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX, // minimum value on x-axis
        int maxX, // maximum value on x-axis
        int minY, // minimum value on y-axis
        int maxY, // maximum value on y-axis
        int xSpacePx, // allowable space to put the axes (including labels)
        int ySpacePx  // allowable space to put the axes (including labels)
    );

    // Creates a plot with top left corner at (0,0) pixels.
    // Size of plot is zero in x and y directions.
    // This is a temporary plot. Use setTopLeft() and setXYSpacePx() to finish it.
    PlotA (
        PlotFormat plotFormat,
        int minX,
        int maxX,
        int minY, 
        int maxY
    );

    PlotA () = delete;
    PlotA (const PlotA& o) = default;
    PlotA (PlotA&& o) noexcept = default;
    PlotA& operator= (const PlotA& o) = default;
    PlotA& operator=(PlotA&& o) noexcept = default;
    ~PlotA () = default;
    
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
        bool printAxis,
        Renderer* renderer) const override;

    void setTopLeft (int xPx, int yPx) override; 

    void setXYSpacePx (int xSpacePx, int ySpacePx) override;

private:

    AxisFormat _a_format_x;
    AxisFormat _a_format_y;

    // requested minimum unit size.
    int _min_unit__px = 4;

    // _start_offset_m is used to determine space before the first values (_min_x or _min_y).
    // length of space is _start_offset_m * _unit_space__px. 
    int _start_offset_m;

    // _end_offset_m is used to determine space after the last value (_max_x or _max_y).
    // length of space is _end_offset_m * _unit_space__px.
    int _end_offset_m;

    // top left corner of plot. This is not at the x-y axes cross hairs. it takes into
    // account the width of the y-axis labels.
    int _top_left_x__px = 0;
    int _top_left_y__px = 0;

    // smallest values on the axes with data.
    int _min_x;
    int _min_y;
    
    // largest values on the axes with data.
    // Note: the axes stretch past the largest value with data.
    // the largest value on the axes will be _max_y + _end_offset_m.
    int _max_x;
    int _max_y;
    
    // given allowable space in the x and y directions
    int _x_space__px;
    int _y_space__px;

    int _x_diff; // max minus min axis values
    int _y_diff; // max minus min axis values
    int _unit_x__px = 0; // unit size in pixels in x direction
    int _unit_y__px = 0; // unit size in pixels in y direction

    // dot represents a value. the dot is a colored square, same size in x and y directions.
    // _dot__px is the length of the square
    int _dot__px;

    // where x and y axes cross.
    int _cross_x__px;
    int _cross_y__px; 

    AxisLeftToRightB _x_axis;
    AxisBottomToTopL _y_axis;

    // only print axes once, they don't change.
    mutable bool _printed_axes = false;

    // Use the given allowable spaces in the x and y directions and the number of units in the axes
    // to determine the unit sizes in the x and y directions.
    // The unit sizes in the x and y axes have to be both odd or both even.
    // if the unit_size in a direction is odd, then the dot length in that direction must be odd.
    // if the unit_size in a direction is even, then the dot length in that direction must be even.
    // In order for the dot to be square, the two unit sizes must both be odd or both be even.
    std::pair<int, int> calcUnitSizeXAndYPx () const;

    // returns length of square dot. the length is 1/2 the smaller of _unit_x__px and _unit_y__px.
    int calcDotSizePx () const;

    // retuns x value of cross hairs.
    int calcCrossXPx (int topLeftX) const;

    // returns y values of cross hairs.
    int calcCrossYPx (int topLeftY) const;
};

#endif