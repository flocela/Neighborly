#include "GrAxis_Horizontal.h"

#include <cmath>
#include <iostream>

using namespace std;

GrAxis_Horizontal::GrAxis_Horizontal (
    std::unique_ptr<Axis> axis,
    AxisFormat axisFormat,
    int yCoordPx
): GrAxis{move(axis), axisFormat},
    _y_coord__px{yCoordPx},
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int GrAxis_Horizontal::getAxisLengthPx () const
{
    return _axis->getAxisLengthPx();
}

int GrAxis_Horizontal::getCentralValuePx () const
{
    return _axis->getCenterValPx();
}

int GrAxis_Horizontal::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

pair<int, int> GrAxis_Horizontal::getPixels (double xVal, int dotSize) const
{   
    return _axis->getPixels(xVal, dotSize);
}
   
int GrAxis_Horizontal::getMinVal () const
{
    return _axis->getMinVal();
}

int GrAxis_Horizontal::getMaxVal () const
{
    return _axis->getMaxVal();
}

int GrAxis_Horizontal::sizeXPx () const
{
    return _axis->getAxisLengthPx();
}

int GrAxis_Horizontal::sizeYPx () const
{   
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

void GrAxis_Horizontal::moveCrossHairs (int xPx, int yPx)
{
    _axis->moveCrossPixel(xPx);
    _y_coord__px = yPx;
}

void GrAxis_Horizontal::setHorizLength (int horizLengthPx)
{
    (void) horizLengthPx;
    //TODO write something for this.
}

void GrAxis_Horizontal::setPxPerUnit (int pixels)
{
    _axis->setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();
}

void GrAxis_Horizontal::setTickThickness (int tickThicknessPx)
{
    _axis->setTickThickness(tickThicknessPx);
}

void GrAxis_Horizontal::implimentAddAxisLine (std::vector<Rect>& rects) const
{
    // Calculate top most pixel.
    int leftPixel = _axis->getStartPixel();

    // Rectangle represents vertical line.
    Rect rect{
        leftPixel,      // top left corner of line, x-coordinate
        _y_coord__px,   // top left corner of line, y-coordinate
        _axis->getAxisLengthPx(),
        _axis_format.axisThicknessPx()
    };

    rects.push_back(rect);
}

void GrAxis_Horizontal::implimentAddTicksAndLabels (
    std::vector<Rect>& backgroundLinesMaj,
    std::vector<Rect>& backgroundLinesMin,
    std::vector<Rect>& ticks, 
    std::vector<TextRect>& texts
) const
{   
    (void)backgroundLinesMaj;
    (void)backgroundLinesMin;
    // First tick will represent the min val.
    int curVal = _axis->getMinVal();

    // topOfLabelYPx is the top of the number shown.
    int topOfNumberYPx =
        _y_coord__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

    // curPixels the first and last pixels covered by one tick.
    pair<int, int> curPixels = getPixels(curVal, _axis->getTickThichness__px());

    int centerOfTick = curPixels.first + (curPixels.second - curPixels.first)/2;

    // text corresponding to the curVal
    TextRect curText{
        centerOfTick, // Text is centered at tick center.
        topOfNumberYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        1 // text is centered
    };

    // Top of tick is inside the chart.
    int tickYPx = _y_coord__px - _axis_format.tickLengthInsideChartPx();

    Rect majTick{
        curPixels.first,
        tickYPx,
        _axis->getTickThichness__px(),
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curPixels.first,
        tickYPx,
        _axis->getTickThichness__px(),
        _axis_format.minTickLengthPx()
    };
    
    // Push ticks onto ticks vector, from the left most tick until the right most tick.
    while (curVal <= _axis->getMaxVal() + _axis->getEndOffsetMultiplier())
    {  
        curPixels = getPixels(curVal, _axis->getTickThichness__px());

        // If curVal is divisible by _maj_tick_spacing then tick is a major tick
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick._x__px = curPixels.first;

            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            ticks.push_back(majTick);
        }
        // Else if curVal is divisible by _min_tick_spacing then tick is a minor tick
        else if (curVal % _min_tick_spacing == 0)
        {   
            minTick._x__px = curPixels.first;
            ticks.push_back(minTick);
        }
        
        ++curVal;
    }
}

int GrAxis_Horizontal::calcMinTickSpacing () const
{
    if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }

    return (_axis->getPixelsPerUnit() >= 10)? 1 : 5;
}

int GrAxis_Horizontal::calcMajTickSpacing () const
{        
    if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }
    
    return (_axis->getPixelsPerUnit() > 10)? 5 : 10; 
}