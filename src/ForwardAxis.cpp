#include "ForwardAxis.h"
#include <cmath>
using namespace std;

ForwardAxis::ForwardAxis (
    int crossPixel,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
):
    _cross_pixel__px{crossPixel},
    _min_val{minVal},
    _max_val{maxVal},
    _diff{_max_val - _min_val},
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{tickThickness},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

int ForwardAxis::getCenterValPx () const
{
    return getPixel(_min_val + (_max_val - _min_val)/2, 1).first;
}

int ForwardAxis::getAxisLengthPx () const
{
    return getEndPixel() - getFrontPixel() + 1;
}

// Add testing for this for even sized dotSize.
std::pair<int, int> ForwardAxis::getPixel (double val, int dotSize) const
{
    // The standard line equation is y2 = y1 + m * (x2 - x1), m is in px per unit.

    // Change the variable names to denote pixels and axis-values.
    // Line equation: px2 = px1 + m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value val (v2 is set to val).
    // px1 is the pixel value corresponding to the smallest xvalue, (v1 is the smallest value).
    
    double v1 = _min_val - _start_offset_m;

    // Cross axis is centered on a pixel, so px1 is at _cross_pixel__px + 0.5.
    // Cross axis is at the center of pixel.
    double px1 = _cross_pixel__px + .5;
    double v2 = val;
    double diff = v2 - v1;
    double px2 = px1 + (_px_per_unit * diff);

    if (dotSize%2 == 0)
    {
        int latterPixel = floor(px2 + .5) - (dotSize/2);
        return {latterPixel, latterPixel + dotSize-1};
    }
    else
    {
        int latterPixel = floor(px2) - dotSize/2;
        return {latterPixel, latterPixel + dotSize - 1};
    }
}

int ForwardAxis::getCrossPx__px () const
{
    return _cross_pixel__px;
}

int ForwardAxis::getMinVal () const
{
    return _min_val;
}

int ForwardAxis::getMaxVal () const
{
    return _max_val;
}

int ForwardAxis::getDiff () const
{
    return _diff;
}

int ForwardAxis::getPixelsPerUnit () const
{
    return _px_per_unit;
}

int ForwardAxis::getTickThichness__px () const
{
    return _tick_thickness__px;
}

int ForwardAxis::getStartOffsetMultiplier () const
{
    return _start_offset_m;
}

int ForwardAxis::getEndOffsetMultiplier () const
{
    return _end_offset_m;
}

int ForwardAxis::getFrontPixel () const
{
    return getPixel(_min_val - _start_offset_m, _tick_thickness__px).first;
}

int ForwardAxis::getEndPixel () const
{
    return getPixel(_max_val + _end_offset_m, _tick_thickness__px).second;
}

void ForwardAxis::moveCrossPixel (int pixel)
{
    _cross_pixel__px = pixel;
}

void ForwardAxis::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
}

void ForwardAxis::setTickThickness (int tickThicknessPx)
{
    _tick_thickness__px = tickThicknessPx;
}