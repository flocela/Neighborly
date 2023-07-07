#include <iostream>
#include <cmath>

#include "AxisTopToBottomL.h"

using namespace std;
AxisTopToBottomL::AxisTopToBottomL (
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal,
    int maxVal, 
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : 
    _axis_format{axisFormat},
    _forward_axis{
        y_coordinate__px,
        minVal,
        maxVal,
        pxPerUnit,
        tickThickness,
        startOffsetMultiplier,
        endOffsetMultiplier
    },
    _x_cross__px{x_coordinate__px},
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int AxisTopToBottomL::getAxisLengthPx() const
{
    return _forward_axis.getAxisLengthPx();
}

int AxisTopToBottomL::getLabelLengthPx () const
{
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

pair<int,int> AxisTopToBottomL::getPixel (double yVal, int dotSize) const
{
    return _forward_axis.getPixel(yVal, dotSize);
}

void AxisTopToBottomL::print (Renderer* renderer) const
{   
    std::vector<Rect> rects = {};
    std::vector<TextRect> texts = {};

    printVerticalLine(rects);
    printTicksAndLabels (rects, texts);

    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
}

int AxisTopToBottomL::sizeXPx () const
{
    // Three is max number of digits in the y-axis label.
    return 
        3 * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer + 
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

int AxisTopToBottomL::sizeYPx() const
{
    return getAxisLengthPx();
}

void AxisTopToBottomL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _forward_axis.moveCrossPixel(yPx);
}

void AxisTopToBottomL::setPxPerUnit (int pixels)
{
    _forward_axis.setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();

}

void AxisTopToBottomL::setTickThickness (int tickThicknessPx)
{
    _forward_axis.setTickThickness(tickThicknessPx);
}


void AxisTopToBottomL::printVerticalLine (std::vector<Rect>& rects) const
{
    int topPixel = _forward_axis.getFrontPixel();
    Rect rect{
        _x_cross__px,
        topPixel,
        _axis_format.axisThicknessPx(),
        _forward_axis.getAxisLengthPx()
    };

    rects.push_back(rect);
}

void AxisTopToBottomL::printTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{
    int curVal = _forward_axis.getMinVal();
    pair<int, int> curPixels = getPixel(curVal, _forward_axis.getTickThichness__px());

    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    TextRect curText = {
        majTickXPx - _text_spacer,
        curPixels.first,
        std::to_string(_forward_axis.getMinVal()),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3
    };

    Rect majRect{
        majTickXPx,
        curPixels.first,
        _axis_format.majTickLengthPx(),
        _forward_axis.getTickThichness__px()
    };

    Rect minRect{
        minTickXPx,
        curPixels.first,
        _axis_format.minTickLengthPx(),
        _forward_axis.getTickThichness__px()
    };
    
    // bottom most pixel on axis
    int botMostPixelY = _forward_axis.getEndPixel();

    while (curPixels.first <= botMostPixelY)
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect._y__px = curPixels.first;

            
            curText._text = std::to_string(curVal);
            curText._y_px = curPixels.first;

            rects.push_back(majRect);
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect._y__px = curPixels.first;
            
            rects.push_back(minRect);
        }
        ++curVal;
        curPixels = _forward_axis.getPixel(curVal, _forward_axis.getTickThichness__px());
    }
}

int AxisTopToBottomL::calcMinTickSpacing () const
{
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }

    return (_forward_axis.getPixelsPerUnit() >= 10)? 1 : 5;
}     

int AxisTopToBottomL::calcMajTickSpacing () const
{
    if (_forward_axis.getMaxVal() - _forward_axis.getMinVal() < 10)
    {
        return 1;
    }
    
    return (_forward_axis.getPixelsPerUnit() > 10)? 5 : 10; 
}