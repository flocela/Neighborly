#include <cmath>
#include "Axis_Basic.h"

using namespace std;

Axis_Basic::Axis_Basic(
    bool forward,
    int crossPixel,
    int lowVal,
    int highVal,
    int pxPerUnit,
    int startOffsetMultiplier,
    int endOffsetMultiplier
):  
    _forward{forward},
    _cross_pixel__px{crossPixel},
    _low_val{lowVal},
    _high_val{highVal},
    _start_val{forward ? lowVal : highVal},
    _end_val{forward ? highVal : lowVal},
    _px_per_unit{forward ? pxPerUnit : -pxPerUnit},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

int Axis_Basic::getAxisLengthPx () const
{   
    return abs(getEndPixel() - getStartPixel()) + 1;
}

std::pair<int, int> Axis_Basic::getPixels (double val, int dotSize) const
{
    // The standard non-vertical line equation is
    // y2 = y1 + m * (x2 - x1), m is in px per unit.

    // Change the variable names to denote pixels and axis-values.
    // Line equation: px2 = px1 + m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value val (v2 is set to val).
    // px1 is the pixel value corresponding to the smallest xvalue, (v1 is the smallest value).

    double v1 = _low_val -_start_offset_m;

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

int Axis_Basic::getLowVal () const
{
    return _low_val;
}

int Axis_Basic::getHighVal () const
{
    return _high_val;
}

int Axis_Basic::getPixelsPerUnit () const
{
    return _px_per_unit;
}

int Axis_Basic::getTickThickness__px () const
{
    return _tick_thickness__px;
}

int Axis_Basic::getStartOffset () const
{
    return _start_offset_m;
}

int Axis_Basic::getEndOffset () const
{
    return _end_offset_m;
}

int Axis_Basic::getStartPixel () const
{   
    return getPixels(
        _start_val + (_forward ? -_start_offset_m : _start_offset_m),
        _tick_thickness__px).first;
}

int Axis_Basic::getEndPixel () const
{
    return getPixels(
        _end_val + ( _forward ? _end_offset_m : -_end_offset_m),
        _tick_thickness__px).second;
}


int Axis_Basic::getCenterValPx () const
{
    return getPixels(_start_val + (_end_val - _start_val)/2, 1).first;
}

void Axis_Basic::moveCrossPixel (int pixel)
{
    _cross_pixel__px = pixel;
}

void Axis_Basic::setPxPerUnit (int pixels)
{
    _px_per_unit = _forward? pixels: -pixels;
}

void Axis_Basic::setDirectionOfAxis (bool forward)
{
    _forward = forward;
    _start_val = forward ? _low_val : _high_val;
    _end_val = forward ? _high_val : _low_val;
    if ( (_px_per_unit < 0 && forward) ||
         (_px_per_unit > 0 && !forward) )
    {
        _px_per_unit = -_px_per_unit;
    }
}