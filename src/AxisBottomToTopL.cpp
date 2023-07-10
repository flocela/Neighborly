#include "AxisBottomToTopL.h"
#include <iostream>
#include <cmath>
using namespace std;

AxisBottomToTopL::AxisBottomToTopL (
    AxisFormat axisFormat,
    int horizLengthPx,
    int x_coordinate__px, 
    int y_coordinate__px,
    int minVal,
    int maxVal, 
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : 
    _axis_format{axisFormat},
    _horiz_line_length__px{horizLengthPx},
    _reverse_axis{
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

int AxisBottomToTopL::getAxisLengthPx () const
{   
    return _reverse_axis.getAxisLengthPx();
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
    return _reverse_axis.getPixel(yVal, dotSize);
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
    _reverse_axis.moveCrossPixel(yPx);
}

void AxisBottomToTopL::setHorizLength (int horizLengthPx)
{
    _horiz_line_length__px = horizLengthPx;
}

void AxisBottomToTopL::setPxPerUnit (int pixels)
{
    _reverse_axis.setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();

}

void AxisBottomToTopL::setTickThickness (int tickThicknessPx) 
{
    _reverse_axis.setTickThickness(tickThicknessPx);
}

void AxisBottomToTopL::setVerticalLine (std::vector<Rect>& rects) const
{
    // Calculate top most pixel.
    int topPixel = _reverse_axis.getEndPixel();
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

    int curVal = _reverse_axis.getMinVal();
    pair<int, int> curPixels = _reverse_axis.getPixel(curVal, _reverse_axis.getTickThichness__px());
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
        _reverse_axis.getTickThichness__px()
    };

    Rect horizLineRectMin{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _reverse_axis.getTickThichness__px()
    };

    Rect majRect{
        majTickXPx,
        curPixels.first,
        _axis_format.majTickLengthPx(),
        _reverse_axis.getTickThichness__px()
    };

    Rect minRect{
        minTickXPx,
        curPixels.first,
        _axis_format.minTickLengthPx(),
        _reverse_axis.getTickThichness__px()
    };

    // Calculate top most pixel.
    int topMostPixelY = _reverse_axis.getEndPixel();

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
        curPixels = _reverse_axis.getPixel(curVal, _reverse_axis.getTickThichness__px());
    }
}

int AxisBottomToTopL::calcMinTickSpacing () const
{ 
     if (_reverse_axis.getMaxVal() - _reverse_axis.getMinVal() < 10)
    {
        return 1;
    }

    return (_reverse_axis.getPixelsPerUnit() >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing () const
{ 
    if (_reverse_axis.getMaxVal() - _reverse_axis.getMinVal() < 10)
    {
        return 1;
    }
    
    return (_reverse_axis.getPixelsPerUnit() > 10)? 5 : 10; 
}