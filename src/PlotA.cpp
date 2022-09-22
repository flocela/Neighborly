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
        int maxY,
        int xSpacePx,
        int ySpacePx
): // TODO does PlotA really need _colors or _moods
    _a_format_x{sizer.axisFormatX()},
    _a_format_y{sizer.axisFormatY()},
    _min_unit__px{sizer.minUnitSize()},
    _start_offset_m{sizer.startOffsetM()},
    _end_offset_m{sizer.endOffsetM()},
    _colors{colors},
    _moods{moods},
    _top_left_x__px{topLeftXPx},
    _top_left_y__px{topLeftYPx},
    _min_x{minX},
    _max_x{maxX},
    _min_y{minY},
    _max_y{maxY},
    _x_space__px{xSpacePx},
    _y_space__px{ySpacePx},
    _x_diff{maxX - minX},
    _y_diff{maxY - minY},
    _unit_x__px{calcUnitSizeXPx()},
    _unit_y__px{calcUnitSizeYPx()},
    _dot__px{calcDotSizePx()},
    // center graph in column
    _cross_x__px{ calcCrossXPx(topLeftXPx) }, 
    _cross_y__px{ calcCrossYPx(topLeftYPx) },
    _tick_spacing_min_x{(_unit_x__px >= 10)? 1 : 5},
    _tick_spacing_min_y{(_unit_y__px >= 10)? 1 : 5},
    _tick_spacing_maj_x{(_unit_x__px > 10)? 5 : 10},
    _tick_spacing_maj_y{(_unit_y__px > 10)? 5 : 10},
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
        _unit_x__px * sizer.startOffsetM(),
        _unit_x__px * sizer.endOffsetM(),
        _unit_x__px
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
        _unit_y__px * sizer.startOffsetM(),
        _unit_y__px * sizer.endOffsetM(),
        _unit_y__px
    }
{
    int tickThickness = (_dot__px%2==0)? 2 : 1;
    _a_format_x.setTickThicknessPx(tickThickness); // TODO move tick thickness to axes.
    _a_format_y.setTickThicknessPx(tickThickness);
}

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
            _unit_x__px *_start_offset_m +      
            ( _unit_x__px * (point.x() - _min_x) ) - 
            _dot__px/2;                               
            
        std::cout << _cross_y__px << ", " << _unit_y__px << ", " << _start_offset_m << ", " << point.y() << ", " << _min_y << ", " << _dot__px << std::endl;
        int y = 
            _cross_y__px -
            _unit_y__px * _start_offset_m -
            ( _unit_y__px * (point.y() - _min_y)) +
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

int PlotA::calcUnitSizeXPx ()
{
    if (_x_space__px <= 0 || _y_space__px <= 0)
    {
        return _min_unit__px;
    }

    int allowableXAxisLengthPx = _x_space__px - _a_format_y.getAxisHeightPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX; // TODO dividing by zero is dangerous

    return std::max(xUnitSize, _min_unit__px);
}

int PlotA::calcUnitSizeYPx ()
{
    if (_x_space__px <= 0 || _y_space__px <= 0)
    {
        return _min_unit__px;
    }

    int allowableYAxisLengthPx = _y_space__px - _a_format_x.getAxisHeightPx();

    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;

    
    // TODO dividing by zero is dangerous
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;

    yUnitSize = std::max(yUnitSize, _min_unit__px);

    yUnitSize = ((_unit_x__px % 2 + _unit_y__px % 2) == 1)? yUnitSize + 1 : yUnitSize;

    return yUnitSize;
}

int PlotA::calcDotSizePx ()
{
    int unitSizePx = std::min(_unit_x__px, _unit_y__px);
    int dotSize = unitSizePx/2;
    dotSize =  ((unitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

int PlotA::calcCrossXPx (int topLeftXPx)
{
    int xAxisLength = 
        (_unit_x__px * ( _x_diff + _start_offset_m + _end_offset_m)) + _a_format_y.getAxisHeightPx();

    return topLeftXPx + (int)(0.5 * ( _x_space__px - xAxisLength ));
}

int PlotA::calcCrossYPx (int topLeftYPx) // TODO, I think I should be calling this more often, instead of repeating this calculation
{
    return 
        topLeftYPx + _unit_y__px * (_start_offset_m + _end_offset_m + _y_diff);
}

void PlotA::moveTopLeft (int topLeftXPx, int topLeftYPx)
{
    _top_left_x__px = topLeftXPx;
    _top_left_y__px = topLeftYPx;

    _cross_x__px = calcCrossXPx(topLeftXPx);
    _cross_y__px = calcCrossYPx(topLeftYPx);
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);

}

void PlotA::setXYSpacePx (int xSpacePx, int ySpacePx) { 
    _x_space__px = xSpacePx;
    _y_space__px = ySpacePx;
    
    _unit_x__px = calcUnitSizeXPx();
    _unit_y__px = calcUnitSizeYPx();
    _dot__px = calcDotSizePx();
    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);
    int tickThickness = (_dot__px%2==0)? 2 : 1;
    _a_format_x.setTickThicknessPx(tickThickness);  // TODO move tick thickness to axes.
    _a_format_y.setTickThicknessPx(tickThickness);
    _tick_spacing_min_x = (_unit_x__px >= 10)? 1 : 5;
    _tick_spacing_min_y = (_unit_y__px >= 10)? 1 : 5;
    _tick_spacing_maj_x = (_unit_x__px > 10)? 5 : 10;
    _tick_spacing_maj_y = (_unit_y__px > 10)? 5 : 10;
    _x_axis.setMinTickSpacing(_tick_spacing_min_x);
    _x_axis.setMajTickSpacing(_tick_spacing_maj_x);
    _y_axis.setMinTickSpacing(_tick_spacing_min_y);
    _y_axis.setMajTickSpacing(_tick_spacing_maj_y);
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit_y__px);
    _y_axis.setOffsetsPx(_unit_y__px * _start_offset_m, _unit_y__px * _end_offset_m);
}


