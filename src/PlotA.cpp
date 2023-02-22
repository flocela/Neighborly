#include "PlotA.h"

using namespace std;

PlotA::PlotA ( 
        PlotSizer sizer,
        int topLeftXPx,
        int topLeftYPx,
        int minX,
        int maxX,
        int minY, 
        int maxY,
        int xSpacePx,
        int ySpacePx
):
    _a_format_x{sizer.axisFormatX()},
    _a_format_y{sizer.axisFormatY()},
    _min_unit__px{sizer.minUnitSize()},
    _start_offset_m{sizer.startOffsetM()},
    _end_offset_m{sizer.endOffsetM()},
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
    _unit_x__px{calcUnitSizeXAndYPx().first},
    _unit_y__px{calcUnitSizeXAndYPx().second},
    _dot__px{calcDotSizePx()},
    _cross_x__px{calcCrossXPx(topLeftXPx)}, 
    _cross_y__px{calcCrossYPx(topLeftYPx)},
    _x_axis{
        _a_format_x,
        _cross_x__px,
        _cross_y__px,
        _min_x,
        _max_x,
        _unit_x__px,
        (_dot__px%2==0)? 2 : 1,
        sizer.startOffsetM(),
        sizer.endOffsetM()
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
    int minX,
    int maxX,
    int minY, 
    int maxY 
):
PlotA(  sizer,
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
    vector<Point> points,
    bool printAxes,
    Renderer* renderer
) const
{
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

void PlotA::setTopLeft (int topLeftXPx, int topLeftYPx)
{
    _top_left_x__px = topLeftXPx;
    _top_left_y__px = topLeftYPx;
    std::cout << "set topleft: " << _top_left_y__px << endl;
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

    int tickThickness = (_dot__px%2==0)? 2 : 1;

    _cross_x__px = calcCrossXPx(_top_left_x__px);
    _cross_y__px = calcCrossYPx (_top_left_y__px);

    _x_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _x_axis.setPxPerUnit(_unit_x__px);
    _x_axis.setTickThickness(tickThickness);
    cout << "moveCrossHairs: " << _cross_y__px << endl;
    _y_axis.moveCrossHairs(_cross_x__px, _cross_y__px);
    _y_axis.setPxPerUnit(_unit_y__px);
    _y_axis.setTickThickness(tickThickness);
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

int PlotA::sizeYPx() const
{  
    // subraction takes care of double counting of horizontal axis' thickness.
    return _y_axis.sizeYPx() + _x_axis.sizeYPx() - (_a_format_x.axisThicknessPx()/2);
}

int PlotA::sizeXPx () const
{
    return _y_axis.sizeXPx() + _x_axis.sizeXPx() - (_a_format_y.axisThicknessPx()/2);
}

int PlotA::getCenterValueOfXAxisPx () const
{
    return _x_axis.getCenterValXPx();
}

pair<int, int> PlotA::calcUnitSizeXAndYPx () const
{
    //TODO think about if there's no space, should this be here. should there be minunits?
    // if there is no space, or if the difference in values is 0, then just use min_unit__px.
    if (_x_space__px <= 0 || _y_space__px <= 0 || _x_diff == 0 || _y_diff == 0)
    {
        return {_min_unit__px, _min_unit__px};
    }

    // x-unit size (doesn't change)
    int allowableXAxisLengthPx = _x_space__px - _y_axis.sizeXPx();
    int numOfCellsX = _x_diff + _start_offset_m + _end_offset_m;
    int xUnitSize = allowableXAxisLengthPx/numOfCellsX;
    xUnitSize = max(xUnitSize, _min_unit__px);

    // preliminary y-unit size
    int allowableYAxisLengthPx = _y_space__px - _x_axis.sizeYPx();
    std::cout <<"calcUnitSize:: y_space, allowable: " << _y_space__px << ", " << allowableYAxisLengthPx << endl;
    int numOfCellsY = _y_diff + _start_offset_m + _end_offset_m;
    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;
    
    // _unit_x__px and _unit_y__px must both be odd or both be even.
    if ( (xUnitSize%2 == 0 && yUnitSize%2 != 0) || (yUnitSize%2 != 0 && yUnitSize%2 == 0) )
    {
        --yUnitSize;
    }
    cout << "final yUnitSize: " << yUnitSize << endl;
    cout << "mult: " << yUnitSize * numOfCellsY << endl;
    return {xUnitSize, yUnitSize};
}

int PlotA::calcDotSizePx () const
{
    int minUnitSizePx = min(_unit_x__px, _unit_y__px);
    int dotSize = minUnitSizePx/2;
    dotSize =  ((minUnitSizePx - dotSize) % 2 == 0) ? dotSize : (dotSize + 1);
    return dotSize;
}

// x-axis is centered in the space available.
int PlotA::calcCrossXPx (int topLeftXPx) const
{
    int xAxisLength = 
        (_unit_x__px * ( _x_diff + _start_offset_m + _end_offset_m)) + _y_axis.sizeXPx();

    return topLeftXPx  +
           (int)( (0.5 * _x_space__px) - (0.5 * (xAxisLength + _y_axis.sizeXPx())) )+
           _y_axis.sizeXPx();
}

int PlotA::calcCrossYPx (int topLeftYPx) const
{
    int retVal =  topLeftYPx + _unit_y__px * (_y_diff + _start_offset_m + _end_offset_m);
    std::cout <<"calcCrossYPx: " << topLeftYPx << ", " << retVal << endl;
    return retVal;
       
}
