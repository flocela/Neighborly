#include "PlotB.h"

#include <iostream>
using namespace std;

PlotB::PlotB ( 
        PlotFormat plotFormat,
        int topLeftXPx, // top left corner of plot
        int topLeftYPx, // top left corner of plot
        int xSpacePx,
        int ySpacePx,
        unique_ptr<GrAxisHorizontalSimple> xAxis,
        unique_ptr<GrAxisVerticalSimple> yAxis
): 
    _min_unit_size__px{plotFormat.minUnitSize()},
    _start_offset{plotFormat.startOffsetM()},
    _end_offset{plotFormat.endOffsetM()},
    _x_diff{xAxis->getHighVal() - xAxis->getLowVal()},
    _y_diff{yAxis->getHighVal() - yAxis->getLowVal()},
    _x_axis{move(xAxis)},
    _y_axis{move(yAxis)}
{
    // Axis values will increase from left to right.
    _x_axis->setDirectionOfAxis(true);

    // Axis values will increase from top to bottom.
    _y_axis->setDirectionOfAxis(true);

    // Update attributes that are affected by change to the top-left corner and
    // available space in the x and y directions.
    setPlot(topLeftXPx, topLeftYPx, xSpacePx, ySpacePx);
}

PlotB::PlotB (
        PlotFormat plotFormat,
        unique_ptr<GrAxisHorizontalSimple> xAxis,
        unique_ptr<GrAxisVerticalSimple> yAxis
): PlotB(
    plotFormat,
    0,
    0,
    0,
    0,
    move(xAxis),
    move(yAxis)
){}

int PlotB::getCenterValueOfXAxisPx () const 
{
    return _x_axis->getCentralValuePx();
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
    return _x_axis->sizeXPx() + _y_axis->getLabelLengthPx();
}

int PlotB::sizeYPx() const
{  
    return _y_axis->sizeYPx() + _x_axis->getLabelLengthPx();
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
        _x_axis->print(renderer);
        _y_axis->print(renderer);
        _printed_axes = true;
    }
    
    // Print each point. A colored dot will represent each point.
    for (auto& point : points)
    {
        // Dot is a square. Convert point's value to the coordinate of the dot's top left corner.
        int x = _x_axis->getPixels(point.x(), _dot__px).first;                 
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

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);

    _x_axis->moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis->setPxPerUnit(_unit__px);

    _y_axis->moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis->setPxPerUnit(_unit__px);

    // horizontal length of background lines that extend from the tick marks across the graph.
    _y_axis->setHorizLength(_x_axis->getAxisLengthPx());

}

int PlotB::calcUnitSizePx () const
{
    // Calculate unit size in x-direction.
    int allowableXAxisLengthPx = _x_space__px - _y_axis->sizeXPx();
    int numOfCellsX = _x_diff + _start_offset + _end_offset;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;
    xUnitSize = max(xUnitSize, _min_unit_size__px);

    // Calculate unit size in y-direction.
    int allowableYAxisLengthPx = _y_space__px - _x_axis->sizeYPx();
    int numOfCellsY = _y_diff + _start_offset + _end_offset;
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
        _unit__px * ( _x_diff + _start_offset + _end_offset) + _y_axis->sizeXPx();

    // Start at given most left point (topLeftXPx),
    // move to the center of given space, move to the left by 1/2 of the required length,
    // move crosshairs to the right making room for y-axis.
    return topLeftXPx +
           (int)( 0.5 * (_x_space__px - requiredXLength) ) +
           _y_axis->sizeXPx();
}

int PlotB::calcCrossYPx (int topLeftYPx) const
{
    return topLeftYPx + _x_axis->sizeYPx();
}