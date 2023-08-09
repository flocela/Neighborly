#include "PlotA.h"
#include <iostream>

using namespace std;

PlotA::PlotA ( 
    PlotFormat plotFormat,
    int topLeftXPx,
    int topLeftYPx,
    int minX,
    int maxX,
    int minY, 
    int maxY,
    int xSpacePx,
    int ySpacePx,
    unique_ptr<GrAxis_Horizontal> xAxis,
    unique_ptr<GrAxis_Vertical> yAxis
):
    _a_format_x{plotFormat.axisFormatX()},
    _a_format_y{plotFormat.axisFormatY()},
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
    _x_axis{move(xAxis)},
    _y_axis{move(yAxis)}
{
    // Update attributes that are affected by change to top left corner coordinate and
    // available space in the x and y directions.
    setPlot(_top_left_x__px, _top_left_y__px, _x_space__px, _y_space__px);
}

PlotA::PlotA (
    PlotFormat plotFormat,
    int minX,
    int maxX,
    int minY, 
    int maxY,
    unique_ptr<GrAxis_Horizontal> xAxis,
    unique_ptr<GrAxis_Vertical> yAxis
):
    PlotA(
        plotFormat,
        0,         
        0,         
        minX,
        maxX,
        minY,
        maxY,
        0,
        0,
        move(xAxis),
        move(yAxis)
    )
{}

int PlotA::getCenterValueOfXAxisPx () const
{   
    return _x_axis->getCentralValuePx();
}

int PlotA::getDotSizePx () const
{
    return _dot__px;
}

int PlotA::getTopLeftXPx () const
{
    return _top_left_x__px;
}

int PlotA::getTopLeftYPx () const
{
    return _top_left_y__px;
}

int PlotA::getXSpacePx () const
{
    return _x_space__px;
}

int PlotA::getYSpacePx () const
{
    return _y_space__px;
}

int PlotA::getXUnitSizePx () const
{
    return _unit_x__px;
}

int PlotA::getYUnitSizePx () const
{
    return _unit_y__px;
}

int PlotA::sizeYPx() const
{  
    // subraction takes care of double counting of horizontal axis' thickness.
    return _y_axis->sizeYPx() + _x_axis->sizeYPx() - (_a_format_x.axisThicknessPx()/2);
}

int PlotA::sizeXPx () const
{
    return _y_axis->sizeXPx() + _x_axis->sizeXPx() - (_a_format_y.axisThicknessPx()/2);
}

void PlotA::print (
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

void PlotA::setPlot (int topLeftCornerXPx, int topLeftCornerYPx, int xSpacePx, int ySpacePx)
{
    _top_left_x__px = topLeftCornerXPx;
    _top_left_y__px = topLeftCornerYPx;
    _x_space__px = xSpacePx;
    _y_space__px = ySpacePx;

    pair<int, int> unitSize = calcUnitSizeXAndYPx();
    _unit_x__px = unitSize.first;
    _unit_y__px = unitSize.second;

    _dot__px = calcDotSizePx();

    int tickThickness = (_dot__px > 12)? 3 : 1;

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx(_top_left_y__px);

    _x_axis->moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis->setPxPerUnit(_unit_x__px);
    _x_axis->setTickThickness(tickThickness);
    _y_axis->moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis->setPxPerUnit(_unit_y__px);
    _y_axis->setTickThickness(tickThickness);

    // horizontal length of background lines that extend from the tick marks across the graph.
    _y_axis->setHorizLength(_x_axis->getAxisLengthPx());
}

pair<int, int> PlotA::calcUnitSizeXAndYPx () const
{
    // Calculate unit size in x-direction.
    int allowableXAxisLengthPx = _x_space__px - _y_axis->sizeXPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;
    xUnitSize = max(xUnitSize, _min_unit__px);

    // Calculate unit size in y-direction.
    int allowableYAxisLengthPx = _y_space__px - _x_axis->sizeYPx();
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;
    yUnitSize = max(yUnitSize, _min_unit__px);
    return {xUnitSize, yUnitSize};
}

// Returns dot size that is odd (not even).
int PlotA::calcDotSizePx () const
{   
    // Dot size based on smaller unitSize of axes.
    int minUnitSizePx = min(_unit_x__px, _unit_y__px);
    int dotSize = minUnitSizePx/4;

    // Make dotSize odd.
    dotSize = (dotSize%2==0)? dotSize+1 : dotSize;

    // Dot size must be equal or greater than _min_dot__px.
    dotSize = (dotSize <= _min_dot__px)? _min_dot__px : dotSize;

    return dotSize;
}

// x-axis is centered in the available space.
int PlotA::calcCrossXPx (int topLeftXPx) const
{
    int requiredXLength = 
        (_unit_x__px * ( _x_diff + _start_offset_m + _end_offset_m)) + _y_axis->sizeXPx();

    // Start at given most left point (topLeftXPx),
    // Move to the center of given space, move to the left by 1/2 of the required length,
    // Move crosshairs to the right making room for y-axis.
    return topLeftXPx +
           (int)( 0.5 * (_x_space__px - requiredXLength) ) +
           _y_axis->sizeXPx();
}

int PlotA::calcCrossYPx (int topLeftYPx) const
{
    int retVal =  topLeftYPx + _unit_y__px * (_y_diff + _start_offset_m + _end_offset_m);
    return retVal;
       
}
