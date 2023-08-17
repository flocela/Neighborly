#ifndef PLOT_B_H
#define PLOT_B_H

#include "AxisFormat.h"
#include "Coordinate.h"
#include "GrAxisHorizontalSimple.h"
#include "GrAxisVerticalSimple.h"
#include "Point.h"
#include "Plot.h"
#include "PlotFormat.h"

// Plot contains the x and y axis, their labels, and the data points inside the graph.
// x-axis runs horizontally from left to right. Labels are on top of axis.
// y-axis runs vertically from top to bottom. Labels are on the left of the axis.
// The unit size in the x and y directions is the same.
class PlotB: public Plot
{

public:

    // The top-left corner aligns vertically with the left side of the vertical axis' labels
    // and aligns horizontally with the top of the horizontal axis' labels.
    // The top-left corner of the plot does not align with the axes' cross hairs.
    PlotB ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot, not the same as where x and y axes cross
        int topLeftYPx, // top left corner of plot, not the same as where x and y axes cross
        int xSpacePx,
        int ySpacePx,
        std::unique_ptr<GrAxisHorizontalSimple> xAxis,
        std::unique_ptr<GrAxisVerticalSimple> yAxis
    );

    // Creates a plot with top left corner at (0,0) pixels.
    // Size of plot is zero in x and y directions.
    // This is a temporary plot. Use setPlot() method to finish it.
    PlotB (
        PlotFormat plotFormat,
        std::unique_ptr<GrAxisHorizontalSimple> xAxis,
        std::unique_ptr<GrAxisVerticalSimple> yAxis
    );

    PlotB () = delete;
    PlotB (const PlotB& o) = default;
    PlotB (PlotB&& o) noexcept = default;
    PlotB& operator= (const PlotB& o) = default;
    PlotB& operator=(PlotB&& o) noexcept = default;
    ~PlotB () noexcept = default;

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

    // Setting the top left corner and the available space affects the unit sizes in the x and
    // y axes. Updating the unit size affects the data dot's width.
    // Updating the unit size also affects the cross hairs' coordinate (where x and y axes cross).
    // setPlot() updates these affected attributes.
    void setPlot (int topLeftCornerXPx, int topLeftCornerYPx, int xSpacePx, int ySpacePx) override;

private:

    // minimum unit size
    int _min_unit_size__px = 5;

    // minimum dot width
    int _min_dot_size__px = 3;

    // _start_offset is used to determine space before the low values (_low_x or _low_y).
    // Length of space is _start_offset_m * _unit_space__px.
    // _end_offset is used to determine space after the high values (_high_x or _high_y).
    // Length of space is _end_offset * _unit_space__px. 
    int _x_start_offset = 1;
    int _x_end_offset = 1;
    int _y_start_offset = 1;
    int _y_end_offset = 1;

    // Top left corner of plot. This is not at the x-y axes' cross hairs. It takes into
    // account the width of the y-axis labels and the height of the x-axis labels.
    int _top_left_x__px = 0;
    int _top_left_y__px = 0;
    
    // given allowable space in the x and y directions
    int _x_space__px;
    int _y_space__px;

    int _x_diff; // difference between high and low values on the x-axis
    int _y_diff; // difference between the high and low values on the y-axis
    int _unit__px; // pixels per unit

    // Dots are colored squares that represent values on the graph. The width of a dot is _dot__px.
    int _dot__px;

    // where x and y axes cross
    int _cross_x__px; 
    int _cross_y__px; 

    std::unique_ptr<GrAxisHorizontalSimple> _x_axis;
    std::unique_ptr<GrAxisVerticalSimple> _y_axis;

    // Only print axes once, they don't change.
    mutable bool _printed_axes = false;

    // For the x and y axes: Use the given allowable space and the required number of
    // units in the axis to determine the unit size. Choose the smaller unit size.
    // The unit size must be equal or greater to _min_unit_size__px.
    int calcUnitSizePx () const;

    // Returns width of square dot. The width is 1/2 the smaller of _unit__px.
    // Returns an odd dot size that is at least the _min_dot__px in width.
    int calcDotSizePx () const;

    // Retuns x value of cross hairs.
    int calcCrossXPx (int topLeftX) const;

    // Returns y values of cross hairs.
    int calcCrossYPx (int topLeftY) const;
};

#endif