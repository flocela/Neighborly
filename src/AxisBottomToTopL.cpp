#include "AxisBottomToTopL.h"
#include <iostream>
#include <cmath>
using namespace std;

AxisBottomToTopL::AxisBottomToTopL (
    unique_ptr<Axis> axis,
    AxisFormat axisFormat,
    int horizLengthPx,
    int x_coordinate__px
): GrAxis{move(axis)},
   _axis_format{axisFormat},
   _horiz_line_length__px{horizLengthPx},
   _x_cross__px{x_coordinate__px},
   _min_tick_spacing{calcMinTickSpacing()},
   _maj_tick_spacing{calcMajTickSpacing()}
{}

int AxisBottomToTopL::getAxisLengthPx () const
{   
    return _axis->getAxisLengthPx();
}

int AxisBottomToTopL::getLabelLengthPx () const
{   
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx();
}

pair<int, int>  AxisBottomToTopL::getPixels (double yVal, int dotSize) const
{   
    return _axis->getPixels(yVal, dotSize);
}

void AxisBottomToTopL::print (Renderer* renderer) const
{
    std::vector<Rect> horizLinesMaj = {};
    std::vector<Rect> horizLinesMin = {};
    std::vector<Rect> ticks = {};
    std::vector<TextRect> texts = {};

    addVerticalLine(ticks);
    addTicksAndLabels (horizLinesMaj, horizLinesMin, ticks, texts);

    if (_axis_format.showBackgroundTickLines())
    {
        renderer->fillBlocks(horizLinesMaj, _axis_format.tickLineBackgroundColor());
        renderer->fillBlocks(horizLinesMin, _axis_format.tickLineBackgroundColor());
    }
    renderer->fillBlocks(ticks, _axis_format.tickColor());
    renderer->renderTexts(texts);
}

int AxisBottomToTopL::sizeXPx () const
{  
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

int AxisBottomToTopL::sizeYPx () const
{
    return getAxisLengthPx();
}

void AxisBottomToTopL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _axis->moveCrossPixel(yPx);
}

void AxisBottomToTopL::setHorizLength (int horizLengthPx)
{
    _horiz_line_length__px = horizLengthPx;
}

void AxisBottomToTopL::setPxPerUnit (int pixels)
{
    _axis->setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();

}

void AxisBottomToTopL::setTickThickness (int tickThicknessPx) 
{
    _axis->setTickThickness(tickThicknessPx);
}

void AxisBottomToTopL::addVerticalLine (std::vector<Rect>& rects) const
{
    // Calculate top most pixel.
    int topPixel = _axis->getEndPixel();

    // Rectangle represents vertical line.
    Rect rect{
        _x_cross__px, // top left corner of line, x-coordinate
        topPixel, // top left corner of line, y-coordinate
        _axis_format.axisThicknessPx(),
        getAxisLengthPx()
    };

    rects.push_back(rect);
}
        
void AxisBottomToTopL::addTicksAndLabels (
    std::vector<Rect>& backgroundLinesMaj,
    std::vector<Rect>& backgroundLinesMin,
    std::vector<Rect>& ticks, 
    std::vector<TextRect>& texts
) const
{   
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    // The first value will be the minimum value given in the constructor.
    int curVal = _axis->getMinVal();

    // curPixels describe one tick, it is the first and last pixels covered by the tick.
    pair<int, int> curPixels = _axis->getPixels(curVal, _axis->getTickThichness__px());

    // text corresponding to the curVal
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

    // background line corresponding to major tick. Background lines run across the chart.
    Rect horizLineRectMaj{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _axis->getTickThichness__px()
    };

    // background line corresponding to minor tick. Background lines run across the chart.
    Rect horizLineRectMin{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _axis->getTickThichness__px()
    };

    // Rect for major tick
    Rect majTick{
        majTickXPx,
        curPixels.first,
        _axis_format.majTickLengthPx(),
        _axis->getTickThichness__px()
    };

    // Rect for minor tick
    Rect minTick{
        minTickXPx,
        curPixels.first,
        _axis_format.minTickLengthPx(),
        _axis->getTickThichness__px()
    };

    // Calculate top most pixel.
    int topMostPixelY = _axis->getEndPixel();

    // Iterate through values from bottom of axis to top of axis.
    while ( curPixels.first >= topMostPixelY )
    {   
        // If _maj_tick_spacing is a multiple of curVal, then this is a major tick.
        if (curVal % _maj_tick_spacing == 0)
        {
            majTick._y__px = curPixels.first;
            curText._text = std::to_string(curVal);
            curText._y_px = curPixels.first;

            ticks.push_back(majTick);
            texts.push_back(curText);

            horizLineRectMaj._y__px = curPixels.first;
            backgroundLinesMaj.push_back(horizLineRectMaj);
        }
        // If _min_tick_spacing is a multiple of curVal, then this is a minor tick.
        else if (curVal % _min_tick_spacing == 0)
        {
            minTick._y__px = curPixels.first;
            ticks.push_back(minTick);

            horizLineRectMin._y__px = curPixels.first;
            backgroundLinesMin.push_back(horizLineRectMin);
        }

        ++curVal;
        curPixels = _axis->getPixels(curVal, _axis->getTickThichness__px());
    }
}

int AxisBottomToTopL::calcMinTickSpacing () const
{ 
     if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }

    return (_axis->getPixelsPerUnit() >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing () const
{ 
    if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }
    
    return (_axis->getPixelsPerUnit() > 10)? 5 : 10; 
}