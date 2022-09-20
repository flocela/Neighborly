#include "PlotA.h"

PlotA::PlotA ( 
        PlotASizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX,
        int maxX,
        int minY, 
        int maxY
): // TODO does PlotA really need _colors or _moods
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
    _unit__px{calcUnitSizePx()},
    _dot__px{calcDotSizePx(_unit__px)},
    // center graph in column
    _cross_x__px{ calcCrossXPx(topLeftXPx) }, 
    _cross_y__px{ calcCrossYPx(topLeftYPx)},
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

void PlotA::print (
    std::vector<Point> points,
    bool clear,
    Renderer* renderer
)
{ 
    (void) clear;
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

int PlotA::calcUnitSizePx ()
{
    int allowableXAxisLengthPx = _sizer.xSpacePx() - _a_format_y.getAxisHeightPx();
    int numOfCellsX = _x_diff + _sizer.startOffsetM() + _sizer.endOffsetM();
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx =
        _sizer.ySpacePx() -
        _sizer.axisFormatYHeight();

    int numOfCellsY = _y_diff + _sizer.startOffsetM() + _sizer.endOffsetM();

    int yCellSize =  allowableYAxisLengthPx/numOfCellsY;

    int min = std::min(xUnitSize, yCellSize);

    return (min < _sizer.minUnitSize())? 4 : min;
}

int PlotA::calcDotSizePx (int unitSizePx)
{
    int dotSize = unitSizePx/2;
    dotSize =  ((unitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

int PlotA::calcCrossXPx (int topLeftXPx)
{
    return topLeftXPx + (int)(0.5 * ( _sizer.xSpacePx() - calcXAxisLength() ));
}

int PlotA::calcCrossYPx (int topLeftYPx)
{
    std::cout << "PlotA calcCrossYPx: y: " << topLeftYPx << std::endl;
    return 
        topLeftYPx + 
        _unit__px * _sizer.startOffsetM() +
        _unit__px * _sizer.endOffsetM() +
        _unit__px * _y_diff;
}

void PlotA::moveTopLeft (int topLeftXPx, int topLeftYPx)
{
    std::cout << "PlotA moveToPleft: y: " << topLeftYPx << std::endl; 
    _top_left_x__px = topLeftXPx;
    _top_left_y__px = topLeftYPx;

    _cross_x__px = calcCrossXPx(topLeftXPx);
    _cross_y__px = calcCrossYPx(topLeftYPx);
    std::cout << "PLot AmoveTopLeft cross_y__px: " << _cross_y__px << std::endl;
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);

}



