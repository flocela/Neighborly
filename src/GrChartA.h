#ifndef GR_CHART_A_H
#define GR_CHART_A_H

#include "GrChartASizer.h"
#include "unordered_map"
#include "Color.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include "AxisLeftToRightB.h"
#include "AxisBottomToTop.h"
#include "Point.h"

class GrChartA
{
public:
    GrChartA ( 
        GrChartASizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx, // top left corner of chart
        int topLeftYPx, // top left corner of chart
        std::string title,
        int minX,
        int maxX,
        int minY, 
        int maxY
    );

    void print (
        std::vector<Point> points,
        bool clear,
        Renderer* renderer);

    void setTopLeft (int xPx, int yPx) {
        _top_left_x__px = xPx;
        _top_left_y__px = yPx;
    }

private:
    GrChartASizer _sizer;
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
    std::string _title;
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
};

#endif