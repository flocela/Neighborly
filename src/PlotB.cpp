#include "PlotB.h"

// PlotB has the same pixels per unit in the x and y directions
// It plots the y axis from top to bottom and the x axis from left to right
PlotB::PlotB ( 
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
): // TODO does PlotB really need _colors or _moods
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
    _unit__px{calcUnitSizePx()},
    _dot__px{calcDotSizePx()},
    // center graph in column
    _cross_x__px{ calcCrossXPx(topLeftXPx) }, 
    _cross_y__px{ calcCrossYPx(topLeftYPx) },
    _x_axis{
        "",
        _a_format_x,
        _cross_x__px,
        _cross_y__px,
        _min_x,
        _max_x,
        _unit__px,
        (_dot__px%2==0)? 2 : 1,
        sizer.startOffsetM(),
        sizer.endOffsetM(),
        
    },
    _y_axis{
        "",
        _a_format_y,
        _cross_x__px,
        _cross_y__px,
        _min_y,
        _max_y,
        _unit__px,
        (_dot__px%2==0)? 2 : 1,
        sizer.startOffsetM(),
        sizer.endOffsetM(),
    }
{}

void PlotB::print (
    std::vector<Point> points,
    bool clear,
    Renderer* renderer
)
{ 
    (void) clear; // TODO
    
    _x_axis.print(renderer);
    _y_axis.print(renderer);

    std::vector<SDL_Rect> rects{};
    for (Point point : points)
    {
        int x = 
            _cross_x__px +                                      
            _unit__px *_start_offset_m +      
            ( _unit__px * (point.x() - _min_x) ) - 
            _dot__px/2;                               
            
        int y = 
            _cross_y__px +
            _unit__px * _start_offset_m +
            ( _unit__px * (point.y() - _min_y)) -
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

void PlotB::print (
    std::unordered_map<Color, std::vector<Point>> pointsPerColor,
    bool clear,
    Renderer* renderer
)
{   
    (void) clear;
    _x_axis.print(renderer);
    _y_axis.print(renderer);

    std::vector<SDL_Rect> rects{};
    for (auto& pair : pointsPerColor)
    {
        Color color = pair.first;
        std::vector<Point> points = pair.second;

        std::vector<Coordinate> coordinates;
        for (Point point : points)
        {
            int x = 
            _cross_x__px +                                      
            _unit__px *_start_offset_m +      
            ( _unit__px * (point.x() - _min_x) ) - 
            _dot__px/2;                               
            
            int y = 
            _cross_y__px +
            _unit__px * _start_offset_m +
            ( _unit__px * (point.y() - _min_y)) -
            _dot__px/2;

            coordinates.push_back(Coordinate(x, y));
        }

        renderer->addBlocksByColor(
            _dot__px,
            _dot__px,
            coordinates,
            _the_color_rgba[color]
        );
    }

}

int PlotB::calcUnitSizePx ()
{
    if (_x_space__px <= 0 || _y_space__px <= 0)
    {
        return _min_unit__px;
    }

    int allowableXAxisLengthPx = _x_space__px - _a_format_y.getAxisSizePx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX; // TODO dividing by zero is dangerous

    int allowableYAxisLengthPx = _y_space__px - _a_format_x.getAxisSizePx();
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;  // TODO dividing by zero is dangerous

    int unitSize = std::min(xUnitSize, yUnitSize);

    return std::max(unitSize, _min_unit__px);
}

int PlotB::calcDotSizePx ()
{
    int unitSizePx = std::min(_unit__px, _unit__px);
    int dotSize = unitSizePx/2;
    dotSize =  ((unitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

int PlotB::calcCrossXPx (int topLeftXPx)
{
    int xAxisLength = 
        (_unit__px * ( _x_diff + _start_offset_m + _end_offset_m)) + _a_format_y.getAxisSizePx();

    // center axis in column
    return topLeftXPx + (int)(0.5 * ( _x_space__px - xAxisLength ));
}

int PlotB::calcCrossYPx (int topLeftYPx) // TODO, I think I should be calling this more often, instead of repeating this calculation
{
    return 
        topLeftYPx + _a_format_x.getAxisSizePx();
}

void PlotB::moveTopLeft (int topLeftXPx, int topLeftYPx)
{
    _top_left_x__px = topLeftXPx;
    _top_left_y__px = topLeftYPx;

    _cross_x__px = calcCrossXPx(topLeftXPx);
    _cross_y__px = calcCrossYPx(topLeftYPx);
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);

}

void PlotB::setXYSpacePx (int xSpacePx, int ySpacePx) { 
    _x_space__px = xSpacePx;
    _y_space__px = ySpacePx;
    
    _unit__px = calcUnitSizePx();
    _dot__px = calcDotSizePx();
    int tickThickness = (_dot__px%2==0)? 2 : 1;
    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit__px);
    _y_axis.setTickThickness(tickThickness);
    _x_axis.setPxPerUnit(_unit__px);
    _x_axis.setTickThickness(tickThickness);

}
