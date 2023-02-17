#include "AxisBottomToTopL.h"
#include <iostream>

using namespace std;

AxisBottomToTopL::AxisBottomToTopL (
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

void AxisBottomToTopL::print (Renderer* renderer) const
{
    std::vector<SDL_Rect> rects = {};
    std::vector<TextRect> texts = {};

    printVerticalLine(rects);
    printTicksAndLabels (rects, texts);

    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
}

void AxisBottomToTopL::printVerticalLine (std::vector<SDL_Rect>& rects) const
{
    int unit_px_odd = (_px_per_unit%2==0)? 0 : 1;

    SDL_Rect rect{
        _x_cross__px,
        calcTopMostPixelWithValue_Y() + unit_px_odd - (_tick_thickness__px/2),
        _axis_format.axisThicknessPx(),
        axisLengthPx()
    };
    rects.push_back(rect);
}
        
void AxisBottomToTopL::printTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
) const
{
    int unit_px_even = (_px_per_unit%2==0)? 1 : 0;

    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    int curVal = _min_val;
    int curVal__px = getPixel(_min_val) + unit_px_even - ( _tick_thickness__px/2 );

    TextRect curText{
        majTickXPx - _text_spacer,
        curVal__px,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3
    };

    SDL_Rect majRect{
        majTickXPx,
        curVal__px,
        //_axis_format.majTickLengthPx(),
        1000,
        _tick_thickness__px
    };

    SDL_Rect minRect{
        minTickXPx,
        curVal__px,
        //_axis_format.minTickLengthPx(),
        1900,
        _tick_thickness__px
    };

    int topMostPixelY = calcTopMostPixelWithValue_Y();
    while ( curVal__px >= topMostPixelY )
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect.y = curVal__px;

            curText._text = std::to_string(curVal);
            curText._y_pixel = curVal__px;

            rects.push_back(majRect);
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect.y = curVal__px;
            rects.push_back(minRect);
        }
        ++curVal;
        curVal__px = getPixel(curVal) + unit_px_even - ( _tick_thickness__px/2 );
    }
    std::cout << std::endl;
}

int AxisBottomToTopL::calcTopMostPixelWithValue_Y () const
{
    return  _y_cross__px - (_px_per_unit * (_diff + _start_offset_m + _end_offset_m));
}

void AxisBottomToTopL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisBottomToTopL::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);

}

void AxisBottomToTopL::setTickThickness (int tickThicknessPx) 
{
    _tick_thickness__px = tickThicknessPx;
}

int AxisBottomToTopL::sizeXPx () const
{  
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

int AxisBottomToTopL::sizeYPx () const
{
    return axisLengthPx();
}

int AxisBottomToTopL::axisLengthPx () const
{
    int unit_px_even = (_px_per_unit%2==0)? 1 : 0;
    // tick may be at edge of horizontal axis, so 1/2 of tick will hang off the end.
    return _y_cross__px - calcTopMostPixelWithValue_Y() - unit_px_even + (_tick_thickness__px/2);
}

int AxisBottomToTopL::calcMinTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit > 10)? 5 : 10;
}

int AxisBottomToTopL::getPixel (double yVal) const
{
    int minYPx = _y_cross__px - (_start_offset_m * _px_per_unit);

    return minYPx - (_px_per_unit * (yVal - _min_val));
}
