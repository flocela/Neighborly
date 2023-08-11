#include "GrAxisHorizontalSimple.h"

#include <cmath>
#include <iostream>

using namespace std;

GrAxisHorizontalSimple::GrAxisHorizontalSimple (
    std::unique_ptr<Axis> axis,
    AxisFormat axisFormat,
    int yCoordPx,
    bool labelsOnTop
): 
    _axis{move(axis)},
    _axis_format{axisFormat},
    _y_coord__px{yCoordPx},
    _labels_on_top{labelsOnTop},
    _min_tick_spacing{calcMinTickSpacing()},
    _maj_tick_spacing{calcMajTickSpacing()}
{}

int GrAxisHorizontalSimple::getAxisLengthPx () const
{
    return _axis->getAxisLengthPx();
}

int GrAxisHorizontalSimple::getCentralValuePx () const
{
    return _axis->getCenterValPx();
}

int GrAxisHorizontalSimple::getLabelLengthPx () const
{
    int retVal =  
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
    return retVal;
}

pair<int, int> GrAxisHorizontalSimple::getPixels (double xVal, int dotSize) const
{   
    return _axis->getPixels(xVal, dotSize);
}
   
int GrAxisHorizontalSimple::getLowVal () const
{
    return _axis->getLowVal();
}

int GrAxisHorizontalSimple::getHighVal () const
{
    return _axis->getHighVal();
}

int GrAxisHorizontalSimple::sizeXPx () const
{
    return _axis->getAxisLengthPx();
}

int GrAxisHorizontalSimple::sizeYPx () const
{   
    return getLabelLengthPx() + _axis_format.axisThicknessPx();
}

void GrAxisHorizontalSimple::print (Renderer* renderer) const
{
    vector<Rect> axis{};
    vector<Rect> ticks{};
    vector<TextRect> texts{};

    implimentAddAxisLine(axis);
    
    implimentAddTicksAndLabels(ticks, texts);

    renderer->fillBlocks(axis, _axis_format.axisColor());
    renderer->fillBlocks(ticks, _axis_format.tickColor());
    renderer->renderTexts(texts); 

}

void GrAxisHorizontalSimple::moveCrossHairs (int xPx, int yPx)
{
    _axis->moveCrossPixel(xPx);
    _y_coord__px = yPx;
}

void GrAxisHorizontalSimple::setPxPerUnit (int pixels)
{
    _axis->setPxPerUnit(pixels);
    _min_tick_spacing = calcMinTickSpacing();
    _maj_tick_spacing = calcMajTickSpacing();
}

void GrAxisHorizontalSimple::implimentAddAxisLine (std::vector<Rect>& rects) const
{
    int leftPixel = _axis->getStartPixel();

    // Rectangle represents horizontal axis line.
    Rect rect{
        leftPixel,      // top left corner of line, x-coordinate
        _y_coord__px,   // top left corner of line, y-coordinate
        _axis->getAxisLengthPx(),
        _axis_format.axisThicknessPx()
    };

    rects.push_back(rect);
}

void GrAxisHorizontalSimple::implimentAddTicksAndLabels (
    std::vector<Rect>& ticks, 
    std::vector<TextRect>& texts
) const
{   
    // First tick will represent the low value on the axis.
    int curVal = _axis->getLowVal();

    // topOfLabelYPx is the top of the number shown.
    int topOfNumberYPx = (_labels_on_top) ?
        _y_coord__px - 
        _axis_format.majTickLengthOutsideChartPx() -
        _axis_format.labelLineSpacePx() -
        _axis_format.labelHeightPx()
        :
        _y_coord__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

    // curPixels is the first and last pixels covered by one tick.
    pair<int, int> curPixels = getPixels(curVal, _axis->getTickThickness__px());

    // Text is at the center of the tick.
    int centerOfTick = curPixels.first + (curPixels.second - curPixels.first)/2;

    // text corresponding to the curVal
    TextRect curText{
        centerOfTick,
        topOfNumberYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        1 // text is centered
    };

    // top of tick
    int majTickYPx = (_labels_on_top) ?
        _y_coord__px - _axis_format.majTickLengthOutsideChartPx() :
        _y_coord__px + _axis_format.tickLengthInsideChartPx();

    int minTickYPx = (_labels_on_top) ?
        _y_coord__px - _axis_format.minTickLengthOutsideChartPx() :
        _y_coord__px + _axis_format.tickLengthInsideChartPx();

    Rect majTick{
        curPixels.first,
        majTickYPx,
        _axis->getTickThickness__px(),
        _axis_format.majTickLengthPx()
    };

    Rect minTick{
        curPixels.first,
        minTickYPx,
        _axis->getTickThickness__px(),
        _axis_format.minTickLengthPx()
    };
    
    // Push ticks onto ticks vector, from the left most tick until the right most tick.
    while (curVal <= _axis->getHighVal() + _axis->getEndOffset())
    {  
        curPixels = getPixels(curVal, _axis->getTickThickness__px());

        // If curVal is divisible by _maj_tick_spacing then tick is a major tick.
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick._x__px = curPixels.first;

            curText._text = std::to_string(curVal);
            curText._x_px = curPixels.first;

            texts.push_back(curText);
            ticks.push_back(majTick);
        }
        // Else if curVal is divisible by _min_tick_spacing then tick is a minor tick.
        else if (curVal % _min_tick_spacing == 0)
        {   
            minTick._x__px = curPixels.first;
            ticks.push_back(minTick);
        }
        
        ++curVal;
    }
}

int GrAxisHorizontalSimple::calcMinTickSpacing () const
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

int GrAxisHorizontalSimple::calcMajTickSpacing () const
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


void GrAxisHorizontalSimple::setDirectionOfAxis (bool forward)
{
    _axis->setDirectionOfAxis(forward);
}