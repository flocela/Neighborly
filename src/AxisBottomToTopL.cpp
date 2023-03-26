#include "AxisBottomToTopL.h"
#include <iostream>
#include <cmath>
using namespace std;

AxisBottomToTopL::AxisBottomToTopL (
    AxisFormat axisFormat,
    int horizLengthPx,
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
    _horiz_line_length__px{horizLengthPx},
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

int AxisBottomToTopL::getAxisLengthPx () const
{   // Note when tick thickness is 1, the ticks at the ends of the line, are within
    // the line - so don't add to the axis length.
    // When the tick thickness is 2, the ticks at the ends of the line, are 1/2
    // on the line, 1/2 off the line. They add 1/2 tick thickness to both ends of the axis.
    return _y_cross__px -
           calcTopMostPixelWithValue_Y() +
           _tick_thickness__px/2 +
           _tick_thickness__px/2 +
           1;
}

int AxisBottomToTopL::getPixel (double yVal) const
{   
    // line equation: y2 = y1 - m * (x2 - x1), m is in px per unit
    // line equation: z2 = z1 - m * (w2 - w1), m is in px per unit.
    // z2 is the pixel value we're looking for, given the real value yVal, w2.
    // z1 is the pixel value corresponding to the smallest yvalue, w1.

    int isEven = (_px_per_unit%2==0)? 1 : 0;
    double w2 = yVal;
    double w1 = -(((double)1)/_px_per_unit)/2;
    double z1 = _y_cross__px - _start_offset_m * _px_per_unit;
    double diff = w2 - w1;
    int retVal = ceil(z1 - (_px_per_unit * diff)) + isEven;
    return retVal;
}

void AxisBottomToTopL::print (Renderer* renderer) const
{
    std::vector<Rect> horizLinesMaj = {};
    std::vector<Rect> horizLinesMin = {};
    std::vector<Rect> rects = {};
    std::vector<TextRect> texts = {};

    setVerticalLine(rects);
    setTicksAndLabels (horizLinesMaj, horizLinesMin, rects, texts);
    if (_axis_format.showBackgroundTickLines())
    {
        renderer->fillBlocks(horizLinesMaj, _axis_format.tickBackgroundColorMaj());
        renderer->fillBlocks(horizLinesMin, _axis_format.tickBackgroundColorMin());
    }
    renderer->fillBlocks(rects, _the_color_rgba[Color::grid]);
    renderer->renderTexts(texts);
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
    return getAxisLengthPx();
}

void AxisBottomToTopL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisBottomToTopL::setHorizLength (int horizLengthPx)
{
    _horiz_line_length__px = horizLengthPx;
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

void AxisBottomToTopL::setVerticalLine (std::vector<Rect>& rects) const
{
    Rect rect{
        _x_cross__px,
        calcTopMostPixelWithValue_Y() - (_tick_thickness__px/2),
        _axis_format.axisThicknessPx(),
        getAxisLengthPx()
    };
    rects.push_back(rect);
}
        
void AxisBottomToTopL::setTicksAndLabels (
    std::vector<Rect>& horizLinesMaj,
    std::vector<Rect>& horizLinesMin,
    std::vector<Rect>& rects, 
    std::vector<TextRect>& texts
) const
{   
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    int curVal = _min_val;
    // curVal__px is the top left corner of the tick.
    int curVal__px = getPixel(_min_val) - ( _tick_thickness__px/2 );
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

    Rect horizLineRectMaj{
        minTickXPx,
        curVal__px,
        _horiz_line_length__px,
        _tick_thickness__px
    };

    Rect horizLineRectMin{
        minTickXPx,
        curVal__px,
        _horiz_line_length__px,
        _tick_thickness__px
    };

    Rect majRect{
        majTickXPx,
        curVal__px,
        _axis_format.majTickLengthPx(),
        _tick_thickness__px
    };

    Rect minRect{
        minTickXPx,
        curVal__px,
        _axis_format.minTickLengthPx(),
        _tick_thickness__px
    };
    int topMostPixelY = calcTopMostPixelWithValue_Y() - ( _tick_thickness__px/2 );

    while ( curVal__px >= topMostPixelY )
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect._y__px = curVal__px;
            curText._text = std::to_string(curVal);
            curText._y_px = curVal__px;

            rects.push_back(majRect);
            texts.push_back(curText);

            horizLineRectMaj._y__px = curVal__px;
            horizLinesMaj.push_back(horizLineRectMaj);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect._y__px = curVal__px;
            rects.push_back(minRect);

            horizLineRectMin._y__px = curVal__px;
            horizLinesMin.push_back(horizLineRectMin);
        }

        ++curVal;
        curVal__px = getPixel(curVal) - ( _tick_thickness__px/2 );
    }
}

int AxisBottomToTopL::calcTopMostPixelWithValue_Y () const
{
    return  getPixel(_max_val) - _px_per_unit * _end_offset_m;
}

int AxisBottomToTopL::calcMinTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit > 10)? 5 : 10;
}