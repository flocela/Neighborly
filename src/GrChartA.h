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
        std::unordered_map<int, Color> colors,
        std::set<std::string> moods,
        int topLeftXPx, // top left corner of chart
        int topLeftYPx, // top left corner of chart
        std::string title
    );

    void print (
        std::vector<Point> points,
        bool clear,
        Renderer* renderer);

private:
    GrChartASizer _sizer;
    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    std::unordered_map<int, Color> _colors;
    std::set<std::string> _moods;
    int _top_left_x__px;
    int _top_left_y__px;
    int _x_diff; // max minus min axis values
    int _y_diff; // max minus min axis values
    std::string _title;

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
};

#endif