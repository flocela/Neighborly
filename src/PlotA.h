#ifndef PLOT_A_H
#define PLOT_A_H

#include "AxisBottomToTopL.h"
#include "AxisFormat.h"
#include "AxisLeftToRightB.h"
#include "Plot.h"
#include "PlotFormat.h"
#include "Point.h"

// Plot contains the x and y axis, their labels, and the data points inside the graph.
// x-axis runs horizontally on the bottom of the plot (left to right).
// y-axis runs vertically on the left (bottom to top).
// The unit size in the x and y directions is the same.
class PlotA: public Plot
{

public:

    // The top left corner of the plot does not align with the axes. The top left corner
    // is not at the axes' crosshairs. The top left corner aligns vertically
    // with the left side of the vertical axis' labels and aligns horizontally with the top of the 
    // vertical axes. The plot encompasses the axes' labels.
    PlotA ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX, // minimum data value on x-axis
        int maxX, // maximum data value on x-axis
        int minY, // minimum data value on y-axis
        int maxY, // maximum data value on y-axis
        int xSpacePx, // allowable space to put the axes (including labels)
        int ySpacePx  // allowable space to put the axes (including labels)
    );

    // Creates a plot with top left corner at (0,0) pixels. Top left corener is not the
    // crosshairs of x and y axes.
    // Size of plot is zero in x and y directions.
    // This is a temporary plot. Use setPlot() to finish it.
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
    ~PlotA () noexcept = default;
    
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

    // Setting the top left corner and the available space affects the unit sizes in the x and
    // y axes. Updating the unit size affects the data dot's width and the tick thickness.
    // Updating the unit size also affects the cross hairs' coordinate (where x and y axes cross).
    // setPlot() updates these affected attributes.
    void setPlot (int topLeftCornerXPx, int topLeftCornerYPx, int xSpacePx, int ySpacePx) override;

private:

    AxisFormat _a_format_x;
    AxisFormat _a_format_y;

    // minimum unit size
    int _min_unit__px = 5;

    // minimum dot width
    int _min_dot__px = 3;

    // _start_offset_m is used to determine space before the first values (_min_x or _min_y).
    // Length of space is _start_offset_m * _unit_space__px. 
    int _start_offset_m;

    // _end_offset_m is used to determine space after the last value (_max_x or _max_y).
    // Length of space is _end_offset_m * _unit_space__px.
    int _end_offset_m;

    // Top left corner of plot. This is not at the x-y axes cross hairs. It takes into
    // account the width of the y-axis labels.
    int _top_left_x__px = 0;
    int _top_left_y__px = 0;

    // smallest values on the axes. These values are given in the constructor.
    int _min_x;
    int _min_y;
    
    // largest values on the axes with data. These values are given in the constructor.
    // Note: the axes stretch past the largest value with data.
    // The largest value on the axes will be _max_y + _end_offset_m.
    int _max_x;
    int _max_y;
    
    // given allowable space in the x and y directions
    int _x_space__px;
    int _y_space__px;

    int _x_diff; // difference between max and min values on the x-axis
    int _y_diff; // difference between the max and min values on the y-axis
    int _unit_x__px = 0; // unit size in pixels in x direction
    int _unit_y__px = 0; // unit size in pixels in y direction

    // Dots are colored squares that represent values on the graph. The width of a dot is _dot__px.
    int _dot__px;

    // where x and y axes cross.
    int _cross_x__px;
    int _cross_y__px; 

    AxisLeftToRightB _x_axis;
    AxisBottomToTopL _y_axis;

    // Only print axes once, they don't change.
    mutable bool _printed_axes = false;

    // For the x and y axes: Use the given allowable space and the required number of
    // units in the axis to determine the unit size. Each unit size must be equal to or larger
    // than _min_unit_size.
    // Returns a pair where the first value is the unit size in the x direction, and the second
    // value is the unit size in the y direction. 
    std::pair<int, int> calcUnitSizeXAndYPx () const;

    // Returns width of square dot. The width is 1/4 the smaller of _unit_x__px and _unit_y__px.
    // Returns an odd dot size that is at least the _min_unit__px in width.
    int calcDotSizePx () const;

    // Retuns x value of cross hairs.
    int calcCrossXPx (int topLeftX) const;

    // Returns y values of cross hairs.
    int calcCrossYPx (int topLeftY) const;
};

#endif