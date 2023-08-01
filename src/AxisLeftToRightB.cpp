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
): _axis_format{axisFormat},
   _forward_axis{
        xCrossPx,
        minVal,
        maxVal,
        pxPerUnit,
        tickThickness,
        startOffsetMultiplier,
        endOffsetMultiplier
   },
   _y_cross__px{yCrossPx},
   _min_tick_spacing{calcMinTickSpacing()},
   _maj_tick_spacing{calcMajTickSpacing()}
{}

int AxisLeftToRightB::getAxisLengthPx () const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisLeftToRightB::getCenterValXPx () const
{
    return _forward_axis.getCenterValPx();
}

int AxisLeftToRightB::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

pair<int, int> AxisLeftToRightB::getPixel (double xVal, int dotSize) const
{   
    return _forward_axis.getPixel(xVal, dotSize);
}

void AxisLeftToRightB::print (Renderer* renderer) const
{   
    // All lines and ticks are drawn as Rects and are held in rects vector.
    std::vector<Rect> rects = {};

    // Tick labels are in texts vector.
    std::vector<TextRect> texts = {};
    
    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
}

int AxisLeftToRightB::sizeXPx () const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisLeftToRightB::sizeYPx () const
{   
    return getLabelLengthPx();
}

void AxisLeftToRightB::moveCrossHairs (int xPx, int yPx)
{
    _forward_axis.moveCrossPixel(xPx);
    _y_cross__px = yPx;
}

void AxisLeftToRightB::setPxPerUnit (int pixels)
{
    _forward_axis.setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();
}

void AxisLeftToRightB::setTickThickness (int tickThicknessPx)
{
    _forward_axis.setTickThickness(tickThicknessPx);
}

void AxisLeftToRightB::addHorizontalLine (std::vector<Rect>& rects) const
{
    int leftPixel = _forward_axis.getStartPixel();
    Rect rect{
        leftPixel, // top left corner pixel, x-coordinate of pixel
        _y_cross__px, // top left corner pixel, y-coordinate of pixel
        _forward_axis.getAxisLengthPx(),
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
    int curVal = _forward_axis.getMinVal();

    // curPixels describes one tick, it is the first and last pixels covered by the tick.
    pair<int, int> curPixels = getPixel(curVal, _forward_axis.getTickThichness__px());

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
        _forward_axis.getTickThichness__px(),
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curPixels.first,
        tickYPx,
        _forward_axis.getTickThichness__px(),
        _axis_format.minTickLengthPx()
    };

    // Right most pixel on axis is farthest away from cross hairs.
    int rightMostPixel = _forward_axis.getEndPixel();
    
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
        curPixels = _forward_axis.getPixel(curVal, _forward_axis.getTickThichness__px());
    }
}

int AxisLeftToRightB::calcMinTickSpacing () const
{
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }

    return (_forward_axis.getPixelsPerUnit() >= 10)? 1 : 5;
}

int AxisLeftToRightB::calcMajTickSpacing () const
{        
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }
    
    return (_forward_axis.getPixelsPerUnit() > 10)? 5 : 10; 
}