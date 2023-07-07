#include "AxisLeftToRightB.h"

#include <iostream>
#include <cmath>
using namespace std;

AxisLeftToRightB::AxisLeftToRightB (
    AxisFormat axisFormat,
    int xCrossPx,
    int yCrossPx,
    bool centeredOnPixel,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : 
    _axis_format{axisFormat},
    _forward_axis{
        xCrossPx,
        centeredOnPixel,
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

int AxisLeftToRightB::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

int AxisLeftToRightB::getCenterValXPx () const
{
    return _forward_axis.getCenterValXPx();
}

pair<int, int> AxisLeftToRightB::getPixel (double xVal, int dotSize) const
{   
    return _forward_axis.getPixel(xVal, dotSize);
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

void AxisLeftToRightB::print (Renderer* renderer) const
{   
    std::vector<Rect> rects = {};
    std::vector<TextRect> texts = {};
    
    printHorizontalLine(rects);
    printTicksAndLabels(rects, texts);

    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
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

void AxisLeftToRightB::printHorizontalLine (std::vector<Rect>& rects) const
{
    int leftPixel = _forward_axis.getFrontPixel();
    Rect rect{
        leftPixel,
        _y_cross__px, // TODO is this right, should _centered? come into play?
        _forward_axis.getAxisLengthPx(),
        _axis_format.axisThicknessPx(), 
    };
    rects.push_back(rect);
}

void AxisLeftToRightB::printTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    int curVal = _forward_axis.getMinVal();
    pair<int, int> curPixels = getPixel(curVal, _forward_axis.getTickThichness__px());

    int topOfLabelYPx = //TODO centered properly?
        _y_cross__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

    TextRect curText{
        curPixels.first,
        topOfLabelYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        1
    };

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

    // rightMostPixel on axis
    int rightMostPixel = _forward_axis.getEndPixel();
    
    while (curPixels.first <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick._x__px = curPixels.first;

            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
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