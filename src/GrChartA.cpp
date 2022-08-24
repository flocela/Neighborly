#include "GrChartA.h"


GrChartA::GrChartA ( 
        GrChartASizer sizer,
        std::unordered_map<int, Color> colors,
        std::set<std::string> moods,
        int topLeftXPx, // top left corner of chart
        int topLeftYPx, // top left corner of chart
        std::string title
):
_sizer{sizer},
_a_format_x{sizer.axisFormatX()},
_a_format_y{sizer.axisFormatY()},
_colors{colors},
_moods{moods},
_top_left_x__px{topLeftXPx},
_top_left_y__px{topLeftYPx},
_x_diff{_sizer.maxX() - _sizer.minX()},
_y_diff{_sizer.maxY() - _sizer.minY()},
_title{title},
_title_x__px{_top_left_x__px + (_x_diff * _sizer.unitX() / 2)},
_title_y__px{_top_left_y__px},
_cross_x__px{
    _top_left_x__px +
    _a_format_y.getAxisHeightPx()
},
_cross_y__px{
    _top_left_y__px + 
    _sizer.titleLetter().getHeightIncLSpace() +
    _sizer.dotSizePx() * (_sizer.startOffset() + _sizer.endOffset()) +
    _sizer.unitY() * _y_diff
},
_tick_spacing_min_x{(_x_diff <= 100)? 1 : 5},
_tick_spacing_min_y{(_y_diff <= 100)? 1 : 5},
_tick_spacing_maj_x{(_x_diff <= 100)? 2 : 10},
_tick_spacing_maj_y{(_y_diff <= 100)? 2 : 10},
_x_axis{
    "",
    _a_format_x,
    _cross_x__px,
    _cross_y__px,
    _sizer.minX(),
    _sizer.maxX(),
    _tick_spacing_maj_x,
    _tick_spacing_min_x,
    _tick_spacing_maj_x,
    sizer.startOffset(),
    sizer.endOffset(),
    _sizer.unitX()
},
_y_axis{
    "",
    _a_format_y,
    _cross_x__px,
    _cross_y__px,
    _sizer.minY(),
    _sizer.maxY(),
    _tick_spacing_maj_y,
    _tick_spacing_min_y,
    _tick_spacing_maj_y,
    sizer.startOffset(),
    sizer.endOffset(),
    _sizer.unitY()
}
{}

void GrChartA::print (
    std::vector<Point> points,
    bool clear,
    Renderer* renderer
)
{   (void) points;
    (void) renderer;
    (void) clear;
    _x_axis.print(renderer);
    _y_axis.print(renderer);
}