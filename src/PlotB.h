#ifndef PLOT_B_H
#define PLOT_B_H

#include "PlotSizer.h"
#include "unordered_map"
#include "Color.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include "AxisLeftToRightT.h"
#include "AxisTopToBottomL.h"
#include "Point.h"
#include "Plot.h"

class PlotB: public Plot
{
public:
    PlotB ( 
        PlotSizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX,
        int maxX,
        int minY, 
        int maxY,
        int xSpacePx,
        int ySpacePx
    );

    void print (
        std::vector<Point> points,
        bool clear,
        Renderer* renderer) override;

    void moveTopLeft (int xPx, int yPx) override; // TODO combine move TopLeft and setXYSpacePx into one method, so not doing some work twice.

    void setXYSpacePx (int xSpacePx, int ySpacePx) override;

    int getTopLeftXPx () override { return _top_left_x__px;}

    int getTopLeftYPx () override { return _top_left_y__px;}

    int getXSpacePx () override { return _x_space__px; }

    int getYSpacePx () override { return _y_space__px; }


private:

    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    int _min_unit__px = 6;
    // Start offset multiplier is used to determine space from cross haris to first value.
    // Space to first value is _start_offset_m * _unit_space__px.
    int _start_offset_m;
    // End offset multiplier is used to determine how much space follows the last value.
    // Space after last value is _end_offset_m * _unit_space__px.
    int _end_offset_m;

    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    int _top_left_x__px = 0;
    int _top_left_y__px = 0;
    int _min_x;
    int _max_x;
    int _min_y;
    int _max_y;
    

    // given allowable space in the x and y directions
    int _x_space__px;
    int _y_space__px;

    int _x_diff; // max minus min axis values
    int _y_diff; // max minus min axis values
    int _unit__px; // pixels per unit
    int _dot__px; // dot size, same in x and y directions. Dot is inside of the unit.
    int _title_x__px; // center placement of _title
    int _title_y__px;

    int _cross_x__px; // where x and y axes cross
    int _cross_y__px; 

    AxisLeftToRightT _x_axis;
    AxisTopToBottomL _y_axis;

    int calcUnitSizeXPx ();

    // Y unit size is dependent on X unit size. They both have to be odd or even.
    int calcUnitSizePx ();
    int calcDotSizePx ();
    int calcCrossXPx (int topLeftX);
    int calcCrossYPx (int topLeftY);
};

#endif