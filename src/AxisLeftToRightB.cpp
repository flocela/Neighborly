#include "AxisLeftToRightB.h"

#include <iostream>
#include <cmath>
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
) : 
    _axis_format{axisFormat},
    _x_cross__px{xCrossPx},
    _y_cross__px{yCrossPx},
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

int AxisLeftToRightB::getAxisLengthPx () const
{
    int isOdd = (_tick_thickness__px%2 == 0? 0 : 1);
    return calcRightMostPixelWithValue_X() - _x_cross__px +
        (_tick_thickness__px/2) +
        (_tick_thickness__px/2) +
        isOdd;
}

int AxisLeftToRightB::getCenterValXPx () const
{
    return getPixel(_min_val + (_max_val-_min_val)/2);
}

int AxisLeftToRightB::getPixel (double xVal) const
{   
    // line equation: y2 = y1 + m * (x2 - x1), m is in px per unit
    // line equation: px2 = px1 + m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value xVal, v2.
    // px1 is the pixel value corresponding to _min_val, v1.
    double v2 = xVal;
    double v1 = _min_val-(((double)1)/_px_per_unit)/2;
    double px1 = _x_cross__px + _start_offset_m * _px_per_unit;
    double diff = v2 - v1;
    int retVal = floor(px1 + (_px_per_unit * diff));

    return retVal;
}

int AxisLeftToRightB::sizeXPx () const
{
    return getAxisLengthPx();
}

int AxisLeftToRightB::sizeYPx () const
{   
    int retVal =  
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

void AxisLeftToRightB::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
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
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);
}

void AxisLeftToRightB::setTickThickness (int tickThicknessPx)
{
    _tick_thickness__px = tickThicknessPx;
}

void AxisLeftToRightB::printHorizontalLine (std::vector<Rect>& rects) const
{
    Rect rect{
        _x_cross__px - (_tick_thickness__px/2),
        _y_cross__px,
        getAxisLengthPx(),
        _axis_format.axisThicknessPx(),
    };
    rects.push_back(rect);
}

void AxisLeftToRightB::printTicksAndLabels (
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    int curVal = _min_val;
    int curVal__px = getPixel(curVal) - _tick_thickness__px/2;

    int topOfLabelYPx = 
        _y_cross__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

    TextRect curText{
        curVal__px,
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
        curVal__px,
        tickYPx,
        _tick_thickness__px,
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curVal__px,
        tickYPx,
        _tick_thickness__px,
        _axis_format.minTickLengthPx()
    };

    int rightMostPixel = calcRightMostPixelWithValue_X();
    
    while (curVal__px <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick._x__px = curVal__px;

            curText._text = std::to_string(curVal);
            curText._x_px = curVal__px;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        else if (curVal % _min_tick_spacing == 0)
        {   
            minTick._x__px = curVal__px;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curVal__px = getPixel(curVal) - _tick_thickness__px/2;
    }
}

int AxisLeftToRightB::calcRightMostPixelWithValue_X () const
{   
    return getPixel(_max_val) + _px_per_unit * _end_offset_m;
}

int AxisLeftToRightB::calcMinTickSpacing (int pixelsPerUnit) const
{
    if (_max_val - _min_val < 10)
    {
        return 1;
    }

    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisLeftToRightB::calcMajTickSpacing (int pixelsPerUnit) const
{        
    if (_max_val - _min_val < 10)
    {
        return 1;
    }
    
    return (pixelsPerUnit > 10)? 5 : 10; 
}