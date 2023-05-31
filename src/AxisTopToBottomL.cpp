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
    _x_cross__px{x_coordinate__px},
    _y_cross__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _diff{_max_val - _min_val},
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{tickThickness},
    _min_tick_spacing{calcMinTickSpacing(_px_per_unit)},
    _maj_tick_spacing{calcMajTickSpacing(_px_per_unit)},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

int AxisTopToBottomL::getAxisLengthPx() const
{
    int isOdd = (_tick_thickness__px%2 == 0? 0 : 1);
    return calcBotMostPixel_Y () - _y_cross__px +
        (_tick_thickness__px/2) +
        (_tick_thickness__px/2) +
        isOdd;
}

int AxisTopToBottomL::getLabelLengthPx () const
{
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

int AxisTopToBottomL::getPixel (double yVal) const
{
    // line equation: y2 = y1 + m * (x2 - x1), m is in px per unit
    // line equation: px2 = px1 + m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value yVal, v2.
    // px1 is the pixel value corresponding to _min_val, v1.
    double v2 = yVal;
    double v1 = _min_val-(((double)1)/_px_per_unit)/2;
    double px1 = _y_cross__px + _start_offset_m * _px_per_unit;
    double diff = v2 - v1;
    int retVal = floor(px1 + (_px_per_unit * diff));

    return retVal;
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
    _y_cross__px = yPx;
}

void AxisTopToBottomL::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);

}

void AxisTopToBottomL::setTickThickness (int tickThicknessPx)
{
    _tick_thickness__px = tickThicknessPx;
}


void AxisTopToBottomL::printVerticalLine (std::vector<Rect>& rects) const
{
    Rect rect{
        _x_cross__px,
        _y_cross__px,
        _axis_format.axisThicknessPx(),
        getAxisLengthPx()
    };

    rects.push_back(rect);
}

void AxisTopToBottomL::printTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    int curVal = _min_val;
    int curVal__px = getPixel(_min_val) - (_tick_thickness__px/2) ;
    TextRect curText = {
        majTickXPx - _text_spacer,
        curVal__px,
        std::to_string(_min_val),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3
    };

    Rect majRect{
        majTickXPx,
        curVal__px - (_tick_thickness__px/2),
        _axis_format.majTickLengthPx(),
        _tick_thickness__px
    };

    Rect minRect{
        minTickXPx,
        curVal__px,
        _axis_format.minTickLengthPx(),
        _tick_thickness__px
    };
    
    int botMostPixelY = calcBotMostPixel_Y();

    while (curVal__px <= botMostPixelY)
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect._y__px = curVal__px;

            
            curText._text = std::to_string(curVal);
            curText._y_px = curVal__px;

            rects.push_back(majRect);
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect._y__px = curVal__px;
            
            rects.push_back(minRect);
        }
        ++curVal;
        curVal__px = getPixel(curVal) - (_tick_thickness__px/ 2 ) ;
    }
}

int AxisTopToBottomL::calcBotMostPixel_Y () const
{
    int val = getPixel(_max_val) + _px_per_unit * _end_offset_m;
    return val;
}

int AxisTopToBottomL::calcMinTickSpacing (int pixelsPerUnit) const
{
    return (pixelsPerUnit >= 10)? 1 : 5;
}     

int AxisTopToBottomL::calcMajTickSpacing (int pixelsPerUnit) const
{
    return (pixelsPerUnit > 10)? 5 : 10;
}