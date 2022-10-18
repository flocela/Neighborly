#ifndef PLOT_A_H
#define PLOT_A_H

#include "PlotSizer.h"
#include "unordered_map"
#include "Color.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include "AxisLeftToRightB.h"
#include "AxisBottomToTopL.h"
#include "Point.h"
#include "Plot.h"

class PlotA: public Plot
{
public:
    PlotA ( 
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
        std::unordered_map<Color, std::vector<Point>> pointsPerColor,
        bool clear,
        Renderer* renderer) override;

    void setTopLeft (int xPx, int yPx) override; 

    void setXYSpacePx (int xSpacePx, int ySpacePx) override;

    int getTopLeftXPx () override { return _top_left_x__px;}

    int getTopLeftYPx () override { return _top_left_y__px;}

    // This is the amount of space given to the Plot. It may be bigger than this because 
    // of the minimumUnitSize from the sizer
    int getXSpacePx () override { return _x_space__px; }

    // This is the amount of space given to the Plot. It may be bigger than this because 
    // of the minimumUnitSize from the sizer
    int getYSpacePx () override { return _y_space__px; }

    // returns the size of the Plot in x and y directions
    int sizeYPx() override;
    int sizeXPx() override;

private:

    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    int _min_unit__px = 6; // TODO should this be set here, it's set int the constructor
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
    int _unit_x__px; // unit size
    int _unit_y__px;
    int _dot__px; // dot size, same in x and y directions. Dot is inside of the unit.
    int _title_x__px; // center placement of _title
    int _title_y__px;

    int _cross_x__px; // where x and y axes cross
    int _cross_y__px; 

    int _tick_spacing_min_x; // spacing for minor ticks
    int _tick_spacing_min_y;
    int _tick_spacing_maj_x; // spacing for major ticks, major ticks have label
    int _tick_spacing_maj_y;

    AxisLeftToRightB _x_axis;
    AxisBottomToTopL _y_axis;

    int calcUnitSizeXPx ();

    // Y unit size is dependent on X unit size. They both have to be odd or even.
    int calcUnitSizeYPx ();
    int calcDotSizePx ();
    int calcCrossXPx (int topLeftX);
    int calcCrossYPx (int topLeftY);
};

#endif