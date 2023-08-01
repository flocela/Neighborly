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

pair<int, int> AxisLeftToRightT::getPixel (double xVal, int dotSize) const
{   
    return _forward_axis.getPixel(xVal, dotSize);
}

void AxisLeftToRightT::print (Renderer* renderer) const
{   
    // All lines and ticks are drawn as Rects and are held in rects vector.
    std::vector<Rect> rects = {};

    // Tick labels are in texts vector.
    std::vector<TextRect> texts = {};
    
    printHorizontalLine(rects);
    printTicksAndLabels(rects, texts);

    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
}

int AxisLeftToRightT::sizeXPx () const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisLeftToRightT::sizeYPx () const
{
    return 
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
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

void AxisLeftToRightT::printHorizontalLine (std::vector<Rect>& rects) const
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

void AxisLeftToRightT::printTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    int curVal = _forward_axis.getMinVal();
    pair<int, int> curPixels = getPixel(curVal, _forward_axis.getTickThichness__px());

    int botOfLabelYPx =  //TODO centered properly?
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
        5
    };

    int majTickYPx = _y_cross__px - _axis_format.majTickLengthOutsideChartPx();
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
    
    // right most pixel on axis
    int rightMostPixel = _forward_axis.getEndPixel();
    
    while (curPixels.first <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0) // major tick with label
        { 
            majTick._x__px = curPixels.first;
                
            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        else if (curVal % _min_tick_spacing == 0) // minor tick
        {   
            minTick._x__px = curPixels.first;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curPixels = _forward_axis.getPixel(curVal, _forward_axis.getTickThichness__px());
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