#include "PlotA.h"

PlotA::PlotA ( 
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
    _tick_spacing_min_x{(_unit_x__px >= 10)? 1 : 5}, // TODO not used. tick spacing determined in axes Delete
    _tick_spacing_min_y{(_unit_y__px >= 10)? 1 : 5},
    _tick_spacing_maj_x{(_unit_x__px > 10)? 5 : 10},
    _tick_spacing_maj_y{(_unit_y__px > 10)? 5 : 10},
    _x_axis{
        _a_format_x,
        _cross_x__px,
        _cross_y__px,
        _min_x,
        _max_x,
        _unit_x__px,
        (_dot__px%2==0)? 2 : 1,
        sizer.startOffsetM(),
        sizer.endOffsetM(),
        
    },
    _y_axis{
        _a_format_y,
        _cross_x__px,
        _cross_y__px,
        _min_y,
        _max_y,
        _unit_y__px,
        (_dot__px%2==0)? 2 : 1,
        sizer.startOffsetM(),
        sizer.endOffsetM(),
    }
{}

PlotA::PlotA (
    PlotSizer sizer,
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods,
    int minX,
    int maxX,
    int minY, 
    int maxY 
):
PlotA(  sizer,
        colors,
        moods,
        0,
        0,
        minX,
        maxX,
        minY,
        maxY,
        0,
        0
    )
{}

void PlotA::print (
    std::unordered_map<Color, std::vector<Point>> pointsPerColor,
    bool printAxis,
    Renderer* renderer
)
{
    (void) pointsPerColor;
    if (!_printed_axes || printAxis)
    {
        _x_axis.print(renderer);
        _y_axis.print(renderer);
        _printed_axes = true;
    }

    std::vector<SDL_Rect> rects{};
    for (auto& pair : pointsPerColor)
    {
        Color color = pair.first;
        std::vector<Point> points = pair.second;

        std::vector<Coordinate> pixelCoordinates;
        for (Point point : points)
        {   
            // dot is a square.
            // x is the x-pixel of the top left pixel of dot-square
            // y is the y_pixel of the top left pixel of sot-square
            int x = 
            _cross_x__px +                                      
            _unit_x__px *_start_offset_m +      
            ( _unit_x__px * (point.x() - _min_x) ) + 
            (_unit_x__px - _dot__px)/2;                  
            int y = _y_axis.getYPixelToPrint(point.y()) + (_unit_y__px - _dot__px)/2;
            pixelCoordinates.push_back(Coordinate(x, y));
        }

        renderer->addBlocksByColor(
            _dot__px,
            _dot__px,
            pixelCoordinates,
            _the_color_rgba[color]
        );
    }

}

int PlotA::sizeYPx()
{  
    // subraction takes care of double counting of horizontal axis' thickness.
    // axis is always at least 1 px, so subtract at least one pixel.
    // otherwise, subtract half the axis thickness.
    return 
        _y_axis.sizeYPx() +
        _x_axis.sizeYPx() -
        (_a_format_x.axisThicknessPx() == 1? 1 : _a_format_x.axisThicknessPx()/2);
    
}

int PlotA::sizeXPx ()
{
    return
        _y_axis.sizeXPx() +
        _x_axis.sizeXPx() - 
        (_a_format_y.axisThicknessPx() == 1? 1 : _a_format_y.axisThicknessPx()/2);
}

int PlotA::calcUnitSizeXPx ()
{
    if (_x_space__px <= 0 || _y_space__px <= 0)
    {
        return _min_unit__px;
    }

    int allowableXAxisLengthPx = _x_space__px - _y_axis.sizeXPx();
    int numOfCellsX = _x_diff + 1 + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX; // TODO dividing by zero is dangerous

    return std::max(xUnitSize, _min_unit__px);
}

int PlotA::calcUnitSizeYPx ()
{
    if (_x_space__px <= 0 || _y_space__px <= 0)
    {
        return _min_unit__px;
    }

    int allowableYAxisLengthPx = _y_space__px - _x_axis.sizeXPx();

    int numOfCellsY = _y_diff + 1 + _start_offset_m + _end_offset_m;

    
    // TODO dividing by zero is dangerous
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;

    yUnitSize = std::max(yUnitSize, _min_unit__px);

    // both unit sizes must be odd, or both must be even
    yUnitSize = ((_unit_x__px % 2 + _unit_y__px % 2) == 1)? yUnitSize + 1 : yUnitSize;

    return yUnitSize;
}

int PlotA::calcDotSizePx ()
{
    int minUnitSizePx = std::min(_unit_x__px, _unit_y__px);
    int dotSize = minUnitSizePx/2;
    dotSize =  ((minUnitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

int PlotA::calcCrossXPx (int topLeftXPx)
{
    int xAxisLength = 
        (_unit_x__px * ( _x_diff + 1 + _start_offset_m + _end_offset_m)) + _y_axis.sizeXPx();

    return topLeftXPx + (int)(0.5 * ( _x_space__px - xAxisLength ));
}

int PlotA::calcCrossYPx (int topLeftYPx) // TODO, I think I should be calling this more often, instead of repeating this calculation
{
    return 
        topLeftYPx + _unit_y__px * (_y_diff + 1 + _start_offset_m + _end_offset_m);
}

void PlotA::setTopLeft (int topLeftXPx, int topLeftYPx)
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

    int tickThickness = (_dot__px%2==0)? 2 : 1;

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);

    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis.setPxPerUnit(_unit_x__px);
    _x_axis.setTickThickness(tickThickness);

    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit_y__px);
    _y_axis.setTickThickness(tickThickness);
}
