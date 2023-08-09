#include "GrAxis_Vertical.h"
#include <iostream>
#include <cmath>
using namespace std;

GrAxis_Vertical::GrAxis_Vertical (
    unique_ptr<Axis> axis,
    AxisFormat axisFormat,
    int x_coordinate__px
):
    GrAxis{move(axis), axisFormat},
    _x_cross__px{x_coordinate__px},
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int GrAxis_Vertical::getAxisLengthPx () const
{   
    return _axis->getAxisLengthPx();
}

int GrAxis_Vertical::getCentralValuePx () const
{
    return _axis->getCenterValPx();
}

int GrAxis_Vertical::getLabelLengthPx () const
{   
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx();
}

pair<int, int>  GrAxis_Vertical::getPixels (double yVal, int dotSize) const
{   
    return _axis->getPixels(yVal, dotSize);
}
   
int GrAxis_Vertical::getMinVal () const
{
    return _axis->getMinVal();
}

int GrAxis_Vertical::getMaxVal () const
{
    return _axis->getMaxVal();
}

int GrAxis_Vertical::sizeXPx () const
{  
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

int GrAxis_Vertical::sizeYPx () const
{
    return getAxisLengthPx();
}

void GrAxis_Vertical::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _axis->moveCrossPixel(yPx);
}

void GrAxis_Vertical::setHorizLength (int horizLengthPx)
{
    _horiz_line_length__px = horizLengthPx;
}

void GrAxis_Vertical::setPxPerUnit (int pixels)
{
    _axis->setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();

}

void GrAxis_Vertical::setTickThickness (int tickThicknessPx) 
{
    _axis->setTickThickness(tickThicknessPx);
}

void GrAxis_Vertical::implimentAddAxisLine (std::vector<Rect>& rects) const
{
    // Calculate top most pixel.
    int topPixel = _axis->getStartPixel();

    // Rectangle represents vertical line.
    Rect rect{
        _x_cross__px, // top left corner of line, x-coordinate
        topPixel, // top left corner of line, y-coordinate
        _axis_format.axisThicknessPx(),
        getAxisLengthPx()
    };

    rects.push_back(rect);
}
        
void GrAxis_Vertical::implimentAddTicksAndLabels (
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
    cout << "topMostPixelY, curPixels.first: " << topMostPixelY << ", " << curPixels.first << endl;;
    // Iterate through values from bottom of axis to top of axis.
    while ( curVal <= _axis->getMaxVal() + _axis->getEndOffsetMultiplier() )
    {   
        curPixels = _axis->getPixels(curVal, _axis->getTickThichness__px());

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
    }
}

int GrAxis_Vertical::calcMinTickSpacing () const
{ 
     if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }

    return (_axis->getPixelsPerUnit() >= 10)? 1 : 5;
}

int GrAxis_Vertical::calcMajTickSpacing () const
{ 
    if (_axis->getMaxVal() - _axis->getMinVal() < 10)
    {
        return 1;
    }
    
    return (_axis->getPixelsPerUnit() > 10)? 5 : 10; 
}