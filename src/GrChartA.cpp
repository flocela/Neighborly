#include "GrChartA.h"


GrChartA::GrChartA ( 
        GrChartASizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx, // top left corner of chart
        int topLeftYPx, // top left corner of chart
        std::string title
): // TODO does GrChartA really need _colors or _moods
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
_title_x__px{_top_left_x__px + (_x_diff * _sizer.unitX() / 2)}, // TODO not used.
_title_y__px{_top_left_y__px}, // TODO not used
_cross_x__px{ _top_left_x__px + (int)(0.5 * ( _sizer.xSpacePx() - _sizer.xAxisLength() ))}, // center graph in column
_cross_y__px{
    _top_left_y__px + 
    _sizer.titleLetter().getHeightIncLSpace() +
    _sizer.dotSizePx() * (_sizer.startOffset() + _sizer.endOffset()) +
    _sizer.unitY() * _y_diff
},
_tick_spacing_min_x{(sizer.unitX() > 10)? 1 : 5},
_tick_spacing_min_y{(sizer.unitY() > 10)? 1 : 5},
_tick_spacing_maj_x{(sizer.unitX() > 10)? 5 : 10},
_tick_spacing_maj_y{(sizer.unitY() > 10)? 5 : 10},
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
{   
    (void) clear;
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _sizer.titleLetter().letterHeight()); // TODO law of Demeter
    renderer->renderText(
        _top_left_x__px + (_sizer.xSpacePx()/2),
        _top_left_y__px,
        _title,
        1
    );
    _x_axis.print(renderer);
    _y_axis.print(renderer);


    std::vector<SDL_Rect> rects{};
    for (Point point : points)
    {
        int x = 
            _cross_x__px +                                      // cross hairs
            _sizer.startOffset() +                              // space between crosshairs and min_value
            ( _sizer.unitX() * (point.x() - _sizer.minX()) ) -  // px_per_unit * ( x - min value)
            _sizer.dotSizePx()/2;                               // x is left edge of dot
            
        int y = _cross_y__px -
                _sizer.startOffset() -
                (_sizer.unitY() * (point.y() - _sizer.minY())) +
                _sizer.dotSizePx()/2;

        std::vector<Coordinate> coordinates;
        coordinates.push_back(Coordinate(x, y));
        renderer->addBlocksByColor(
            _sizer.dotSizePx(),
            _sizer.dotSizePx(),
            coordinates,
            point.rgba()
        );
    }
}