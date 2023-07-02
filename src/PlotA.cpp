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
        int ySpacePx
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
    _x_axis{
        _a_format_x,
        0, // use zero for default x_coordinate__px
        0, // use zero for default y_coordinate__px
        _min_x,
        _max_x,
        0, // use zero for pxPerUnit
        1, // use 1 for tickThickness
        plotFormat.startOffsetM(),
        plotFormat.endOffsetM()
    },
    _y_axis{
        _a_format_y,
        _x_axis.getAxisLengthPx(),
        0, // use zero for default x_coordinate__px
        0, // use zero for default y_coordinate__px
        false,
        _min_y,
        _max_y,
        0, // use zero for pxPerUnit
        1, // use 1 for tickThickness
        plotFormat.startOffsetM(),
        plotFormat.endOffsetM(),
        
    }
{
    pair<int, int> unitSize = calcUnitSizeXAndYPx();
    _unit_x__px = unitSize.first;
    _unit_y__px = unitSize.second;
    _dot__px = calcDotSizePx();
    _y_axis.setCenteredOnPixel((_dot__px%2==0) ? false : true);
    int tickThickness = (_dot__px%2==0)? 2 : 1;
    _cross_x__px = calcCrossXPx(topLeftXPx);
    _cross_y__px = calcCrossYPx(topLeftYPx);

    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis.setPxPerUnit(_unit_x__px);
    _x_axis.setTickThickness(tickThickness);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit_y__px);
    _y_axis.setTickThickness(tickThickness);
    
    // horizontal length of extended tick marks.
    // they are inside the chart and area usually a greyed out color
    _y_axis.setHorizLength(_x_axis.getAxisLengthPx());

 }

PlotA::PlotA (
    PlotFormat plotFormat,
    int minX,
    int maxX,
    int minY, 
    int maxY 
):
PlotA(  plotFormat,
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

int PlotA::getCenterValueOfXAxisPx () const
{   
    return _x_axis.getCenterValXPx();
    
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
    return _y_axis.sizeYPx() + _x_axis.sizeYPx() - (_a_format_x.axisThicknessPx()/2);
}

int PlotA::sizeXPx () const
{
    return _y_axis.sizeXPx() + _x_axis.sizeXPx() - (_a_format_y.axisThicknessPx()/2);
}

void PlotA::print (
    vector<Point> points,
    bool printAxes,
    Renderer* renderer
) const
{   (void) points;
    // only print axes once.
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
        int y = _y_axis.getPixel(point.y(), _dot__px).first;
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
    
    pair<int, int> unit_sizes = calcUnitSizeXAndYPx();
    _unit_x__px = unit_sizes.first;
    _unit_y__px = unit_sizes.second;

    _dot__px = calcDotSizePx();
    _y_axis.setCenteredOnPixel((_dot__px%2==0) ? false : true);
    int tickThickness = (_dot__px%2==0)? 2 : 1;

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);
    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis.setPxPerUnit(_unit_x__px);
    _x_axis.setTickThickness(tickThickness);
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit_y__px);
    _y_axis.setTickThickness(tickThickness);
    _y_axis.setHorizLength(_x_axis.getAxisLengthPx());
}

pair<int, int> PlotA::calcUnitSizeXAndYPx () const
{
    int allowableXAxisLengthPx = _x_space__px - _y_axis.getLabelLengthPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;
    xUnitSize = max(xUnitSize, _min_unit__px);

    // preliminary y-unit size
    int allowableYAxisLengthPx = _y_space__px - _x_axis.getLabelLengthPx();
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;
    yUnitSize = max(yUnitSize, _min_unit__px);

    // _unit_x__px and _unit_y__px must both be odd or both be even, so that dot is square.
    if ( (xUnitSize%2) != (yUnitSize%2) )
    {
        if (yUnitSize > xUnitSize && yUnitSize > _min_unit__px)
        {
            --yUnitSize;
        }
        else if (xUnitSize > yUnitSize && xUnitSize > _min_unit__px)
        {
            --xUnitSize;
        }
        else if (yUnitSize > xUnitSize)
        {
            ++xUnitSize;
        }
        else
        {
            ++yUnitSize;
        }
    }
    return {xUnitSize, yUnitSize};
}

int PlotA::calcDotSizePx () const
{   
    int minUnitSizePx = min(_unit_x__px, _unit_y__px);
    int dotSize = minUnitSizePx/4;
    dotSize =  ((minUnitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

// x-axis is centered in the space available.
int PlotA::calcCrossXPx (int topLeftXPx) const
{
    int requiredXLength = 
        (_unit_x__px * ( _x_diff + _start_offset_m + _end_offset_m)) + _y_axis.getLabelLengthPx();

    // start at given most left point (topLeftXPx),
    // move to the center of given space, move to the left by 1/2 of the required length,
    // move crosshairs to the right making room for y-axis.
    return topLeftXPx +
           (int)( 0.5 * (_x_space__px - requiredXLength) ) +
           _y_axis.getLabelLengthPx();
}

int PlotA::calcCrossYPx (int topLeftYPx) const
{
    int retVal =  topLeftYPx + _unit_y__px * (_y_diff + _start_offset_m + _end_offset_m);
    return retVal;
       
}
