#include "AxisLeftToRightB.h"

#include <cmath>
#include <iostream>

using namespace std;

AxisLeftToRightB::AxisLeftToRightB (
    AxisFormat axisFormat,
    int xCrossPx,
    int yCrossPx,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
): 
    GrAxis{move(axis), axisFormat},
    _y_cross__px{yCrossPx},
    _axis_format{axisFormat},
    _axis{
        true,
        xCrossPx,
        minVal,
        maxVal,
        pxPerUnit,
        tickThickness,
        startOffsetMultiplier,
        endOffsetMultiplier
    },
    
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int AxisLeftToRightB::getAxisLengthPx () const
{
    return _axis.getAxisLengthPx();
}

int AxisLeftToRightB::getCenterValXPx () const
{
    return _axis.getCenterValPx();
}

int AxisLeftToRightB::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

pair<int, int> AxisLeftToRightB::getPixels (double xVal, int dotSize) const
{   
    return _axis.getPixels(xVal, dotSize);
}

void AxisLeftToRightB::print (Renderer* renderer) const
{   
    // All lines and ticks are drawn as Rects and are held in rects vector.
    std::vector<Rect> rects = {};

    // Tick labels are in texts vector.
    std::vector<TextRect> texts = {};
    
    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->fillBlocks(rects, _axis_format.axisColor());
    renderer->renderTexts(texts);
}

int AxisLeftToRightB::sizeXPx () const
{
    return _axis.getAxisLengthPx();
}

int AxisLeftToRightB::sizeYPx () const
{   
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

void AxisLeftToRightB::moveCrossHairs (int xPx, int yPx)
{
    _axis.moveCrossPixel(xPx);
    _y_cross__px = yPx;
}

void AxisLeftToRightB::setPxPerUnit (int pixels)
{
    _axis.setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();
}

void AxisLeftToRightB::setTickThickness (int tickThicknessPx)
{
    _axis.setTickThickness(tickThicknessPx);
}

void AxisLeftToRightB::addHorizontalLine (std::vector<Rect>& rects) const
{
    int leftPixel = _axis.getStartPixel();
    Rect rect{
        leftPixel, // top left corner pixel, x-coordinate of pixel
        _y_cross__px, // top left corner pixel, y-coordinate of pixel
        _axis.getAxisLengthPx(),
        _axis_format.axisThicknessPx(), 
    };
    rects.push_back(rect);
}

void AxisLeftToRightB::addTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    // First tick will represent the min val.
    int curVal = _axis.getMinVal();

    // curPixels describes one tick, it is the first and last pixels covered by the tick.
    pair<int, int> curPixels = getPixels(curVal, _axis.getTickThichness__px());

    // topOfLabelYPx is the top of the number shown.
    int topOfNumberYPx =
        _y_cross__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

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
    int tickYPx = _y_cross__px - _axis_format.tickLengthInsideChartPx();

    Rect majTick{
        curPixels.first,
        tickYPx,
        _axis.getTickThichness__px(),
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curPixels.first,
        tickYPx,
        _axis.getTickThichness__px(),
        _axis_format.minTickLengthPx()
    };

    // Right most pixel on axis is farthest away from cross hairs.
    int rightMostPixel = _axis.getEndPixel();
    
    // Push ticks onto rects vector, from the left most tick until the right most tick.
    while (curPixels.first <= rightMostPixel)
    {  
        // If curVal is divisible by _maj_tick_spacing then tick is a major tick
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick._x__px = curPixels.first;

            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        // Else if curVal is divisible by _min_tick_spacing then tick is a minor tick
        else if (curVal % _min_tick_spacing == 0)
        {   
            minTick._x__px = curPixels.first;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curPixels = _axis.getPixels(curVal, _axis.getTickThichness__px());
    }
}

int AxisLeftToRightB::calcMinTickSpacing () const
{
    if (_axis.getMaxVal() - _axis.getMinVal() < 10)
    {
        return 1;
    }

    return (_axis.getPixelsPerUnit() >= 10)? 1 : 5;
}

int AxisLeftToRightB::calcMajTickSpacing () const
{        
    if (_axis.getMaxVal() - _axis.getMinVal() < 10)
    {
        return 1;
    }
    
    return (_axis.getPixelsPerUnit() > 10)? 5 : 10; 
}