#include "GrChartA.h"

GrChartA::GrChartA ( 
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
): // TODO does GrChartA really need _colors or _moods
    _sizer{sizer},
    _a_format_x{sizer.axisFormatX()},
    _a_format_y{sizer.axisFormatY()},
    _colors{colors},
    _moods{moods},
    _top_left_x__px{topLeftXPx},
    _top_left_y__px{topLeftYPx},
    _min_x{minX},
    _max_x{maxX},
    _min_y{minY},
    _max_y{maxY},
    _x_diff{maxX - minX},
    _y_diff{maxY - minY},
    _title{title},
    _unit__px{calcUnitSizePx()},
    _dot__px{calcDotSizePx(_unit__px)},
    _title_x__px{_top_left_x__px + (_x_diff * _unit__px / 2)}, // TODO not used.
    _title_y__px{_top_left_y__px}, // TODO not used
    // center graph in column
    _cross_x__px{ _top_left_x__px + (int)(0.5 * ( _sizer.xSpacePx() - calcXAxisLength() ))}, 
    _cross_y__px{
        _top_left_y__px + 
        _sizer.titleHeight() +
        _sizer.keyLetterHeightInclSpace() +
        _unit__px * _sizer.startOffsetM() +
        _unit__px * _sizer.endOffsetM() +
        _unit__px * _y_diff
    },
    _tick_spacing_min_x{(_unit__px >= 10)? 1 : 5},
    _tick_spacing_min_y{(_unit__px >= 10)? 1 : 5},
    _tick_spacing_maj_x{(_unit__px > 10)? 5 : 10},
    _tick_spacing_maj_y{(_unit__px > 10)? 5 : 10},
    _x_axis{
        "",
        _a_format_x,
        _cross_x__px,
        _cross_y__px,
        minX,
        maxX,
        _tick_spacing_maj_x,
        _tick_spacing_min_x,
        _tick_spacing_maj_x,
        _unit__px * sizer.startOffsetM(),
        _unit__px * sizer.endOffsetM(),
        _unit__px
    },
    _y_axis{
        "",
        _a_format_y,
        _cross_x__px,
        _cross_y__px,
        minY,
        maxY,
        _tick_spacing_maj_y,
        _tick_spacing_min_y,
        _tick_spacing_maj_y,
        _unit__px * sizer.startOffsetM(),
        _unit__px * sizer.endOffsetM(),
        _unit__px
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
        _sizer.keyLetterHeight()); // TODO law of Demeter
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
            _cross_x__px +                                      
            _unit__px * _sizer.startOffsetM() +      
            ( _unit__px * (point.x() - _min_x) ) - 
            _dot__px/2;                               
            
        int y = 
            _cross_y__px -
            _unit__px * _sizer.startOffsetM() -
            ( _unit__px * (point.y() - _min_y)) +
            _dot__px/2;

        std::vector<Coordinate> coordinates;
        coordinates.push_back(Coordinate(x, y));
        renderer->addBlocksByColor(
            _dot__px,
            _dot__px,
            coordinates,
            point.rgba()
        );
    }
}

int GrChartA::calcUnitSizePx ()
{
    int allowableXAxisLengthPx = _sizer.xSpacePx() - _a_format_y.getAxisHeightPx();
    int numOfCellsX = _x_diff + _sizer.startOffsetM() + _sizer.endOffsetM();
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx =
        _sizer.ySpacePx() -
        _sizer.titleHeight() -
        _sizer.keyLetterHeightInclSpace() -
        _sizer.axisFormatYHeight();

    int numOfCellsY = _y_diff + _sizer.startOffsetM() + _sizer.endOffsetM();

    int yCellSize =  allowableYAxisLengthPx/numOfCellsY;

    int min = std::min(xUnitSize, yCellSize);

    return (min < _sizer.minUnitSize())? 4 : min;
}

int GrChartA::calcDotSizePx (int unitSizePx)
{
    int dotSize = unitSizePx/2;
    dotSize =  ((unitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}
