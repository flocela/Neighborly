#include <cmath>
#include <iostream>
#include "GrAxisVerticalSimple.h"

using namespace std;

GrAxisVerticalSimple::GrAxisVerticalSimple (
    unique_ptr<Axis> axis,
    AxisFormat axisFormat,
    int xCoordPx
):
    _axis{move(axis)},
    _axis_format{axisFormat},
    _x_coord__px{xCoordPx},
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int GrAxisVerticalSimple::getAxisLengthPx () const
{   
    return _axis->getAxisLengthPx();
}

int GrAxisVerticalSimple::getCentralValuePx () const
{
    return _axis->getCenterValPx();
}

int GrAxisVerticalSimple::getLabelLengthPx () const
{   
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx();
}

pair<int, int>  GrAxisVerticalSimple::getPixels (double yVal, int dotSize) const
{   
    return _axis->getPixels(yVal, dotSize);
}
   
int GrAxisVerticalSimple::getLowVal () const
{
    return _axis->getLowVal();
}

int GrAxisVerticalSimple::getHighVal () const
{
    return _axis->getHighVal();
}

int GrAxisVerticalSimple::sizeXPx () const
{  
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

int GrAxisVerticalSimple::sizeYPx () const
{
    return getAxisLengthPx();
}

void GrAxisVerticalSimple::print (Renderer* renderer) const
{
    vector<Rect> horizLinesMaj{};
    vector<Rect> horizLinesMin{};
    vector<Rect> axis{};
    vector<Rect> ticks{};
    vector<TextRect> texts{};

    implimentAddAxisLine(axis);
    
    implimentAddTicksAndLabels(horizLinesMaj, horizLinesMin, ticks, texts);

    if (_axis_format.showBackgroundTickLines())
    {
        renderer->fillBlocks(horizLinesMaj, _axis_format.tickLineBackgroundColor());
        renderer->fillBlocks(horizLinesMin, _axis_format.tickLineBackgroundColor());
    }

    renderer->fillBlocks(axis, _axis_format.axisColor());
    renderer->fillBlocks(ticks, _axis_format.tickColor());
    renderer->renderTexts(texts);

}

void GrAxisVerticalSimple::moveCrossHairs (int xPx, int yPx)
{
    _x_coord__px = xPx;
    _axis->moveCrossPixel(yPx);
}

void GrAxisVerticalSimple::setHorizLength (int horizLengthPx)
{
    _horiz_line_length__px = horizLengthPx;
}

void GrAxisVerticalSimple::setPxPerUnit (int pixelsPerUnit)
{
    _axis->setPxPerUnit(pixelsPerUnit);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();

}

void GrAxisVerticalSimple::implimentAddAxisLine (std::vector<Rect>& rects) const
{
    int topPixel = _axis->getStartPixel();

    // Rectangle represents vertical line.
    Rect rect{
        _x_coord__px - _axis_format.axisThicknessPx()/2, // top left corner of line, x-coord
        topPixel,                                        // top left corner of line, y-coord
        _axis_format.axisThicknessPx(),
        getAxisLengthPx()
    };

    rects.push_back(rect);
}
        
void GrAxisVerticalSimple::implimentAddTicksAndLabels (
    std::vector<Rect>& backgroundLinesMaj,
    std::vector<Rect>& backgroundLinesMin,
    std::vector<Rect>& ticks, 
    std::vector<TextRect>& texts
) const
{   
    int majTickXPx = _x_coord__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_coord__px - _axis_format.minTickLengthOutsideChartPx();

    // The first value will be the low value on the axis.
    int curVal = _axis->getLowVal();

    // curPixels describe one tick, it is the first and last pixels covered by the tick.
    pair<int, int> curPixels = _axis->getPixels(curVal, _axis->getTickThickness__px());

    // text corresponding to the curVal
    TextRect curText{
        majTickXPx - _text_spacer,
        curPixels.first,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3 // left text alignment
    };

    // background line corresponding to major tick. Background lines run across the chart.
    Rect horizLineRectMaj{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _axis->getTickThickness__px()
    };

    // background line corresponding to minor tick. Background lines run across the chart.
    Rect horizLineRectMin{
        minTickXPx,
        curPixels.first,
        _horiz_line_length__px,
        _axis->getTickThickness__px()
    };

    // Rect for major tick
    Rect majTick{
        majTickXPx,
        curPixels.first,
        _axis_format.majTickLengthPx(),
        _axis->getTickThickness__px()
    };

    // Rect for minor tick
    Rect minTick{
        minTickXPx,
        curPixels.first,
        _axis_format.minTickLengthPx(),
        _axis->getTickThickness__px()
    };
    
    // Iterate through values from start of axis to end of axis.
    while ( curVal <= _axis->getHighVal() + _axis->getEndOffset() )
    {   
        curPixels = _axis->getPixels(curVal, _axis->getTickThickness__px());

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

int GrAxisVerticalSimple::calcMinTickSpacing () const
{ 
     if (_axis->getHighVal() - _axis->getLowVal() < 10)
    {
        return 1;
    }
    else
    {
        return (_axis->getPixelsPerUnit() >= 10)? 1 : 5;
    }
}

int GrAxisVerticalSimple::calcMajTickSpacing () const
{ 
    if (_axis->getHighVal() - _axis->getLowVal() < 10)
    {
        return 1;
    }
    else
    {
        return (_axis->getPixelsPerUnit() > 10)? 5 : 10;
    }
}

void GrAxisVerticalSimple::setDirectionOfAxis (bool forward)
{
    _axis->setDirectionOfAxis(forward);
}