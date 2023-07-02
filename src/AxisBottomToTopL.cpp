#include "AxisBottomToTopL.h"
#include <iostream>
#include <cmath>
using namespace std;

AxisBottomToTopL::AxisBottomToTopL (
    AxisFormat axisFormat,
    int horizLengthPx,
    int x_coordinate__px, 
    int y_coordinate__px,
    bool centeredOnPixel,
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
    _centered_on_pixel{centeredOnPixel},
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
{   
    pair<int, int> topPair = getPixel(_max_val + _end_offset_m, _tick_thickness__px);
    int topPixel = topPair.first < 0 ? 0 : topPair.first;

    int bottomPixel = getPixel(_min_val - _start_offset_m, _tick_thickness__px).second;

    return bottomPixel - topPixel + 1;
}

int AxisBottomToTopL::getLabelLengthPx () const
{   
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

pair<int, int>  AxisBottomToTopL::getPixel (double yVal, int dotSize) const
{   
    // The standard line equation is y2 = y1 - m * (x2 - x1), m is in px per unit.

    // Change the variable names to denote pixels and y-values.
    // Line equation: px2 = px1 - m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value yVal (v2 is set to yVal).
    // px1 is the pixel value corresponding to the smallest yvalue, (v1 is the smallest y-value).

    double v1 = _min_val - _start_offset_m;

    // If _y_cross__px is centered on a pixel, then px1 is _y_cross__px + 0.5.
    // If _y_cross is between two pixels (spanning over 2 pixels). Then px1 is at_y_cross__px.
    double px1 = _centered_on_pixel? _y_cross__px + .5 : _y_cross__px;
    double v2 = yVal;
    double diff = v2 - v1;
    double px2 = px1 - ((int)_px_per_unit * diff);
    if (dotSize%2 == 0)
    {
        int topPixel = floor(px2 + .5) - (dotSize/2);
        return {topPixel, topPixel + dotSize - 1};
    }
    else
    {
        int px2Int = floor(px2) - dotSize/2;
        return {px2Int, px2Int + dotSize - 1};
    }
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
    return getLabelLengthPx();
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
    // Calculate top most pixel.
    pair<int, int> topPair = getPixel(_max_val + _end_offset_m, _tick_thickness__px);
    int topPixel = topPair.first < 0 ? 0 : topPair.first;

    // Rectangle represents vertical line.
    Rect rect{
        _x_cross__px,
        topPixel,
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
    pair<int, int> curPixels = getPixel(_min_val, _tick_thickness__px);
    TextRect curText{
        majTickXPx - _text_spacer,
        curPixels.first,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3
    };

    Rect horizLineRectMaj{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _tick_thickness__px
    };

    Rect horizLineRectMin{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _tick_thickness__px
    };

    Rect majRect{
        majTickXPx,
        curPixels.first,
        _axis_format.majTickLengthPx(),
        _tick_thickness__px
    };

    Rect minRect{
        minTickXPx,
        curPixels.first,
        _axis_format.minTickLengthPx(),
        _tick_thickness__px
    };

    // Calculate top most pixel.
    pair<int, int> topPair = getPixel(_max_val + _end_offset_m, _tick_thickness__px);
    int topMostPixelY = topPair.first < 0 ? 0 : topPair.first;

    while ( curPixels.first >= topMostPixelY )
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect._y__px = curPixels.first;
            curText._text = std::to_string(curVal);
            curText._y_px = curPixels.first;

            rects.push_back(majRect);
            texts.push_back(curText);

            horizLineRectMaj._y__px = curPixels.first;
            horizLinesMaj.push_back(horizLineRectMaj);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect._y__px = curPixels.first;
            rects.push_back(minRect);

            horizLineRectMin._y__px = curPixels.first;
            horizLinesMin.push_back(horizLineRectMin);
        }

        ++curVal;
        curPixels = getPixel(curVal, _tick_thickness__px);
    }
}

void AxisBottomToTopL::setCenteredOnPixel (bool centered)
{
    _centered_on_pixel = centered;
}

int AxisBottomToTopL::calcMinTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing (int pixelsPerUnit) const
{ 
    return (pixelsPerUnit > 10)? 5 : 10;
}