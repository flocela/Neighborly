#include "AxisLeftToRightT.h"

#include <cmath>
#include <iostream>

using namespace std;

AxisLeftToRightT::AxisLeftToRightT (
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

int AxisLeftToRightT::getAxisLengthPx () const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisLeftToRightT::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

int AxisLeftToRightT::getCenterValXPx () const
{
    return _forward_axis.getCenterValPx();
}

pair<int, int> AxisLeftToRightT::getPixels (double xVal, int dotSize) const
{   
    return _forward_axis.getPixels(xVal, dotSize);
}

void AxisLeftToRightT::print (Renderer* renderer) const
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

int AxisLeftToRightT::sizeXPx () const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisLeftToRightT::sizeYPx () const
{
    return getLabelLengthPx();
}

void AxisLeftToRightT::moveCrossHairs (int xPx, int yPx)
{
    _forward_axis.moveCrossPixel(xPx);
    _y_cross__px = yPx;
}

void AxisLeftToRightT::setPxPerUnit (int pixels)
{
    _forward_axis.setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();
}

void AxisLeftToRightT::setTickThickness (int tickThicknessPx)
{
    _forward_axis.setTickThickness(tickThicknessPx);
}

void AxisLeftToRightT::addHorizontalLine (std::vector<Rect>& rects) const
{
    int leftPixel = _forward_axis.getStartPixel();
    Rect rect{
        leftPixel,
        _y_cross__px,
        _forward_axis.getAxisLengthPx(),
        _axis_format.axisThicknessPx()
    };

    rects.push_back(rect);
}

void AxisLeftToRightT::addTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    // First tick will represent the min val.
    int curVal = _forward_axis.getMinVal();

    // curPixels describes one tick, it is the first and last pixels covered by the tick.
    pair<int, int> curPixels = getPixels(curVal, _forward_axis.getTickThichness__px());

    // Bottom of number is at botOfLabelYPx.
    int botOfLabelYPx =
        _y_cross__px -
        _axis_format.majTickLengthOutsideChartPx() -
        _axis_format.labelLineSpacePx();

    TextRect curText{
        curPixels.first,
        botOfLabelYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        5 // Renderer places text centered horizontally and bottom of text is at botOfLabelYPx
    };

    // top of tick px for major tick
    int majTickYPx = _y_cross__px - _axis_format.majTickLengthOutsideChartPx();

    // top of tick px for minor tick
    int minTickYPx = _y_cross__px - _axis_format.minTickLengthOutsideChartPx();
    
    Rect majTick{
        curPixels.first,
        majTickYPx,
        _forward_axis.getTickThichness__px(),
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curPixels.first,
        minTickYPx,
        _forward_axis.getTickThichness__px(),
        _axis_format.minTickLengthPx()
    };
    
    // Right most pixel on axis is farthest away from cross hairs.
    int rightMostPixel = _forward_axis.getEndPixel();
    
    // Push ticks onto rects vector, from the left most tick until the right most tick.
    while (curPixels.first <= rightMostPixel)
    {  
        // If curVal is divisible by _maj_tick_spacing then tick is a major tick
        if (curVal % _maj_tick_spacing == 0) // major tick with label
        { 
            majTick._x__px = curPixels.first;
                
            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        // Else if curVal is divisible by _min_tick_spacing then tick is a minor tick
        else if (curVal % _min_tick_spacing == 0) // minor tick
        {   
            minTick._x__px = curPixels.first;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curPixels = _forward_axis.getPixels(curVal, _forward_axis.getTickThichness__px());
    }
}

int AxisLeftToRightT::calcMinTickSpacing () const
{ 
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }

    return (_forward_axis.getPixelsPerUnit() >= 10)? 1 : 5;
}
        
int AxisLeftToRightT::calcMajTickSpacing () const
{ 
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }
    
    return (_forward_axis.getPixelsPerUnit() > 10)? 5 : 10; 
}