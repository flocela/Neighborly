#include "PlotB.h"

#include <iostream>
using namespace std;

PlotB::PlotB ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int minX,
        int maxX,
        int minY, 
        int maxY,
        int xSpacePx,
        int ySpacePx,
        unique_ptr<GrAxis_Vertical> yAxis
): 
    _axis_format_x{plotFormat.axisFormatX()},
    _axis_format_y{plotFormat.axisFormatY()},
    _min_unit_size__px{plotFormat.minUnitSize()},
    _start_offset_m{plotFormat.startOffsetM()},
    _end_offset_m{plotFormat.endOffsetM()},
    _min_x{minX},
    _min_y{minY},
    _max_x{maxX},
    _max_y{maxY},
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
    _y_axis{move(yAxis)}
{
    // Update attributes that are affected by change to the top left corner coordinate and
    // available space in the x and y directions.
    setPlot(topLeftXPx, topLeftYPx, xSpacePx, ySpacePx);
}

PlotB::PlotB (
        PlotFormat plotFormat,
        int minX,
        int maxX,
        int minY, 
        int maxY,
        unique_ptr<GrAxis_Vertical> yAxis
): PlotB(
    plotFormat,
    0,
    0,
    minX,
    maxX,
    minY,
    maxY,
    0,
    0,
    move(yAxis)
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
        _y_axis->sizeXPx() + _x_axis.sizeXPx() - (_axis_format_y.axisThicknessPx()/2);
}

int PlotB::sizeYPx() const
{  
    // subraction takes care of double counting of horizontal axis' thickness.
    return 
        _y_axis->sizeYPx() +
        _x_axis.sizeYPx() -
        (_axis_format_x.axisThicknessPx()/2);
}

void PlotB::print (
    vector<Point> points,
    bool printAxes,
    Renderer* renderer
) const
{   
    // Only print axes once.
    if (!_printed_axes || printAxes) 
    {
        _x_axis.print(renderer);
        _y_axis->print(renderer);
        _printed_axes = true;
    }
    
    // Print each point. A colored dot will represent each point.
    for (auto& point : points)
    {
        // Dot is a square. Convert point's value to the coordinate of the dot's top left corner.
        int x = _x_axis.getPixels(point.x(), _dot__px).first;                 
        int y = _y_axis->getPixels(point.y(), _dot__px).first;

        renderer->fillBlock(
            _dot__px, // width
            _dot__px, // height
            Coordinate(x, y),
            _the_color_rgba[point.color()]
        );
    }
}

void PlotB::setPlot (int topLeftCornerXPx, int topLeftCornerYPx, int xSpacePx, int ySpacePx)
{
    _top_left_x__px = topLeftCornerXPx;
    _top_left_y__px = topLeftCornerYPx;
    _x_space__px = xSpacePx;
    _y_space__px = ySpacePx;
    
    _unit__px = calcUnitSizePx();
    _dot__px = calcDotSizePx();

    int tickThickness = (_dot__px > 12)? 3 : 1;

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);

    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis.setPxPerUnit(_unit__px);
    _x_axis.setTickThickness(tickThickness);

    _y_axis->moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis->setPxPerUnit(_unit__px);
    _y_axis->setTickThickness(tickThickness);

}

int PlotB::calcUnitSizePx () const
{
    // Calculate unit size in x-direction.
    int allowableXAxisLengthPx = _x_space__px - _y_axis->sizeXPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;
    xUnitSize = max(xUnitSize, _min_unit_size__px);

    // Calculate unit size in y-direction.
    int allowableYAxisLengthPx = _y_space__px - _x_axis.sizeYPx();
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;
    yUnitSize = max(yUnitSize, _min_unit_size__px);

    return min(xUnitSize, yUnitSize);
}

// Returns dot size that is odd (not even).
int PlotB::calcDotSizePx () const
{
    // Dot size based on unit size
    int dotSize = _unit__px/2;

    // Make dotSize odd.
    dotSize = (dotSize%2==0)? dotSize+1 : dotSize;

    // Dot size must be equal or greater than _min_dot_size__px.
    dotSize = (dotSize <= _min_dot_size__px)? _min_dot_size__px : dotSize;

    return dotSize;
}

// x-axis is centered in the space available.
int PlotB::calcCrossXPx (int topLeftXPx) const
{
    int requiredXLength = 
        _unit__px * ( _x_diff + _start_offset_m + _end_offset_m) + _y_axis->sizeXPx();

    // Start at given most left point (topLeftXPx),
    // move to the center of given space, move to the left by 1/2 of the required length,
    // move crosshairs to the right making room for y-axis.
    return topLeftXPx +
           (int)( 0.5 * (_x_space__px - requiredXLength) ) +
           _y_axis->sizeXPx();
}

int PlotB::calcCrossYPx (int topLeftYPx) const
{
    return topLeftYPx + _x_axis.sizeYPx();
}