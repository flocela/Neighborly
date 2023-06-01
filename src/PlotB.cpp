#include "PlotB.h"

#include <iostream>
using namespace std;

// PlotB has the same pixels per unit in the x and y directions
// It plots the y axis from top to bottom and the x axis from left to right
PlotB::PlotB ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX,
        int maxX,
        int minY, 
        int maxY,
        int xSpacePx,
        int ySpacePx
): 
    _axis_format_x{plotFormat.axisFormatX()},
    _axis_format_y{plotFormat.axisFormatY()},
    _min_unit__px{plotFormat.minUnitSize()},
    _start_offset_m{plotFormat.startOffsetM()},
    _end_offset_m{plotFormat.endOffsetM()},
    _top_left_x__px{topLeftXPx},
    _top_left_y__px{topLeftYPx},
    _min_x{minX},
    _min_y{minY},
    _max_x{maxX},
    _max_y{maxY},
    _x_space__px{xSpacePx},
    _y_space__px{ySpacePx},
    _x_diff{maxX - minX},
    _y_diff{maxY - minY},
    _x_axis{
        _axis_format_x,
        0, // use zero for default x_coordinate__px
        0, // use zero for default y_coordinate__px
        _min_x,
        _max_x,
        0, // use zero for pxPerUnit
        1, // use 1 for tickThickness
        plotFormat.startOffsetM(),
        plotFormat.endOffsetM(),
        
    },
    _y_axis{
        _axis_format_y,
        0, // use zero for default x_coordinate__px
        0, // use zero for default y_coordinate__px
        _min_y,
        _max_y,
        0, // use zero for pxPerUnit
        1, // use 1 for tickThickness
        plotFormat.startOffsetM(),
        plotFormat.endOffsetM(),
    }
{
    setXYSpacePx(xSpacePx, ySpacePx);
}

PlotB::PlotB (
        PlotFormat plotFormat,
        int minX,
        int maxX,
        int minY, 
        int maxY
): PlotB(
    plotFormat,
    0,
    0,
    minX,
    maxX,
    minY,
    maxY,
    0,
    0
){}

int PlotB::getCenterValueOfXAxisPx () const 
{
    return _x_axis.getCenterValXPx();
}

int PlotB::getDotSizePx () const
{
    return _dot__px;
}

int PlotB::getTopLeftXPx () const 
{
    return _top_left_x__px;
}

int PlotB::getTopLeftYPx () const
{
    return _top_left_y__px;
}

int PlotB::getXSpacePx () const
{
    return _x_space__px;
}

int PlotB::getYSpacePx () const
{
    return _y_space__px;
}

int PlotB::getXUnitSizePx () const
{
    return _unit__px;
}

int PlotB::getYUnitSizePx () const
{
    return _unit__px;
}

int PlotB::sizeXPx () const 
{
    // subraction takes care of double counting of horizontal axis' thickness.
    return
        _y_axis.sizeXPx() + _x_axis.sizeXPx() - (_axis_format_y.axisThicknessPx()/2);
}

int PlotB::sizeYPx() const
{  
    // subraction takes care of double counting of horizontal axis' thickness.
    return 
        _y_axis.sizeYPx() +
        _x_axis.sizeYPx() -
        (_axis_format_x.axisThicknessPx()/2);
}

void PlotB::print (
    vector<Point> points,
    bool printAxes,
    Renderer* renderer
) const
{   
    if (!_printed_axes || printAxes) 
    {
        _x_axis.print(renderer);
        _y_axis.print(renderer);
        _printed_axes = true;
    }
    
    unordered_map<Color, vector<Coordinate>> coordinatesPerColor;
    for (auto& point : points)
    {
        if (coordinatesPerColor.find(point.color()) == coordinatesPerColor.end())
        {
            coordinatesPerColor.insert({point.color(), vector<Coordinate>{}});
        }

        // dot is a square.
        // x is the x-pixel of the top left pixel of dot-square
        // y is the y_pixel of the top left pixel of sot-square
        int x = _x_axis.getPixel(point.x()) - (_dot__px/2);                 
        int y = _y_axis.getPixel(point.y()) - (_dot__px/2);

        coordinatesPerColor[point.color()].push_back(Coordinate(x, y));
    }

    for (auto& pair: coordinatesPerColor)
    {   
        renderer->fillBlocks(
            _dot__px,
            _dot__px,
            pair.second,
            _the_color_rgba[pair.first]
        );
    }
}

void PlotB::setTopLeft (int topLeftXPx, int topLeftYPx)
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
    _x_axis.setPxPerUnit(_unit__px);
    _x_axis.setTickThickness(tickThickness);

    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit__px);
    _y_axis.setTickThickness(tickThickness);
}

int PlotB::calcUnitSizePx () const
{
    int allowableXAxisLengthPx = _x_space__px - _y_axis.getLabelLengthPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx = _y_space__px - _x_axis.getLabelLengthPx();
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;

    return min(xUnitSize, yUnitSize);
}

int PlotB::calcDotSizePx () const
{
    int dotSize = _unit__px/2;
    // equal space on either side of the dot, so dot is centered in unit
    return ((_unit__px - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
}

// x-axis is centered in the space available.
int PlotB::calcCrossXPx (int topLeftXPx) const
{
    int requiredXLength = 
        _unit__px * ( _x_diff + _start_offset_m + _end_offset_m) + _y_axis.getLabelLengthPx();

    // start at given most left point (topLeftXPx),
    // move to the center of given space, move to the left by 1/2 of the required length,
    // move crosshairs to the right making room for y-axis.
    return topLeftXPx +
           (int)( 0.5 * (_x_space__px - requiredXLength) ) +
           _y_axis.getLabelLengthPx();
}

int PlotB::calcCrossYPx (int topLeftYPx) const
{
    return topLeftYPx + _x_axis.sizeYPx();
}