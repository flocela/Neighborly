#include <cmath>
#include "BasicAxis.h"

using namespace std;

// If forward is true, then the axis values run in the direction of the window's coordinates.
// If forwards is false: then the _start_val is the maxVal, the _end_val is the minVal,
// and the _px_per_unit is negative.
BasicAxis::BasicAxis(
    bool forward,
    int crossPixel,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int startOffsetMultiplier,
    int endOffsetMultiplier
):  
    _forward{forward},
    _cross_pixel__px{crossPixel},
    _min_val{minVal},
    _max_val{maxVal},
    _start_val{forward ? minVal : maxVal},
    _end_val{ forward ? maxVal: minVal},
    _diff{_max_val - _min_val},
    _px_per_unit{forward ? pxPerUnit : -pxPerUnit},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

int BasicAxis::getAxisLengthPx () const
{   
    return abs(getEndPixel() - getStartPixel()) + 1;
}

std::pair<int, int> BasicAxis::getPixels (double val, int dotSize) const
{
    // The standard line equation
    // y2 = y1 + m * (x2 - x1), m is in px per unit.

    // Change the variable names to denote pixels and axis-values.
    // Line equation: px2 = px1 + m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value val (v2 is set to val).
    // px1 is the pixel value corresponding to the smallest xvalue, (v1 is the smallest value).

    double v1 = _min_val -_start_offset_m;

    // Cross axis is at center of pixel, so px1 is at _cross_pixel__px + 0.5.
    double px1 = _cross_pixel__px + 0.5;
    double v2 = val;
    double diff = v2 - v1;
    double px2 = px1 + (_px_per_unit * diff);

    int formerPixel = 0;
    int latterPixel = 0;
    if (dotSize%2 == 0)
    {
        formerPixel = floor(px2 + .5) - (dotSize/2);
        latterPixel = formerPixel + dotSize - 1;

        // Does not return any negative pixels, so change negative pixels to zero.
        formerPixel = formerPixel < 0 ? 0 : formerPixel;
        latterPixel = latterPixel < 0 ? 0 : latterPixel; 
    }
    else
    {
        formerPixel = floor(px2) - dotSize/2;
        latterPixel = formerPixel + dotSize - 1;

        // Does not return any negative pixels, so change negative pixels to zero.
        formerPixel = formerPixel < 0 ? 0 : formerPixel;
        latterPixel = latterPixel < 0 ? 0 : latterPixel;
    }

    return {formerPixel, latterPixel};
}

int BasicAxis::getMinVal () const
{
    return _min_val;
}

int BasicAxis::getMaxVal () const
{
    return _max_val;
}

int BasicAxis::getDiff () const
{
    return _diff;
}

int BasicAxis::getPixelsPerUnit () const
{
    return _px_per_unit;
}

int BasicAxis::getTickThickness__px () const
{
    return _tick_thickness__px;
}

int BasicAxis::getStartOffsetMultiplier () const
{
    return _start_offset_m;
}

int BasicAxis::getEndOffsetMultiplier () const
{
    return _end_offset_m;
}

int BasicAxis::getStartPixel () const
{   
    // Closest pixel to the cross hairs on the axis.
    return getPixels(
        _start_val + (_forward ? -_start_offset_m : _start_offset_m),
        _tick_thickness__px).first;
}

int BasicAxis::getEndPixel () const
{
    // Farthest pixel to the cross hairs on the axis.
    return getPixels(
        _end_val + ( _forward ? _end_offset_m : -_end_offset_m),
        _tick_thickness__px).second;
}


int BasicAxis::getCenterValPx () const
{
    return getPixels(_start_val + (_end_val - _start_val)/2, 1).first;
}

void BasicAxis::moveCrossPixel (int pixel)
{
    _cross_pixel__px = pixel;
}

void BasicAxis::setPxPerUnit (int pixels)
{
    _px_per_unit = _forward? pixels: -pixels;
}