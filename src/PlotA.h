#ifndef PLOT_A_H
#define PLOT_A_H

#include "PlotASizer.h"
#include "unordered_map"
#include "Color.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include "AxisLeftToRightB.h"
#include "AxisBottomToTop.h"
#include "Point.h"
#include "Plot.h"

class PlotA: public Plot
{
public:
    PlotA ( 
        PlotASizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX,
        int maxX,
        int minY, 
        int maxY
    );

    void print (
        std::vector<Point> points,
        bool clear,
        Renderer* renderer) override;

    void moveTopLeft (int xPx, int yPx) override;

    int getTopLeftXPx () override
    {

        return _top_left_x__px;
    }

    int getTopLeftYPx () override
    {
        return _top_left_y__px;
    }

private:
    PlotASizer _sizer;
    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    int _top_left_x__px;
    int _top_left_y__px;
    int _min_x;
    int _max_x;
    int _min_y;
    int _max_y;
    int _x_diff; // max minus min axis values
    int _y_diff; // max minus min axis values
    int _unit__px; // unit size, same in x and y direction.
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
    AxisBottomToTop _y_axis;

    int calcUnitSizePx ();
    int calcDotSizePx (int unitSizePx);
    int calcXAxisLength () {
        return (
            _unit__px * _x_diff +
            _unit__px * _sizer.startOffsetM() +
            _unit__px * _sizer.endOffsetM() +
            _a_format_y.getAxisHeightPx()
        );
    }

    int calcCrossXPx (int topLeftX);
    int calcCrossYPx (int topLeftY);
};

#endif