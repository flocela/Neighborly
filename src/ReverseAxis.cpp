#include "ReverseAxis.h"
#include <cmath>

#include <iostream>
using namespace std;

ReverseAxis::ReverseAxis (
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

int ReverseAxis::getAxisLengthPx () const
{
    return abs(getEndPixel() - getFrontPixel()) + 1;
}

// TODO Add testing for this for even sized dotSize.
std::pair<int, int> ReverseAxis::getPixel (double val, int dotSize) const
{
    // The standard line equation is for downsloping line is
    // y2 = y1 - m * (x2 - x1), m is in px per unit.

    // Change the variable names to denote pixels and axis-values.
    // Line equation: px2 = px1 - m * (v2 - v1), m is in px per unit.
    // px2 is the pixel value we're looking for, given the real value val (v2 is set to val).
    // px1 is the pixel value corresponding to the smallest xvalue, (v1 is the smallest value).
    
    double v1 = _min_val - _start_offset_m;

    // Cross axis is centered on a pixel, so px1 is at _cross_pixel__px + 0.5.
    // Cross axis is at the center of pixel.
    double px1 = _cross_pixel__px + .5;
    double v2 = val;
    double diff = v2 - v1;
    double px2 = px1 - (_px_per_unit * diff);

    if (dotSize%2 == 0)
    {
        int formerPixel = floor(px2 + .5) - (dotSize/2);
        return {formerPixel, formerPixel + dotSize - 1};
    }
    else
    {
        int formerPixel = floor(px2) - dotSize/2;
        return {formerPixel, formerPixel + dotSize - 1};
    }
}

int ReverseAxis::getCrossPx__px () const
{
    return _cross_pixel__px;
}

int ReverseAxis::getMinVal () const
{
    return _min_val;
}

int ReverseAxis::getMaxVal () const
{
    return _max_val;
}

int ReverseAxis::getDiff () const
{
    return _diff;
}

int ReverseAxis::getPixelsPerUnit () const
{
    return _px_per_unit;
}

int ReverseAxis::getTickThichness__px () const
{
    return _tick_thickness__px;
}

int ReverseAxis::getStartOffsetMultiplier () const
{
    return _start_offset_m;
}

int ReverseAxis::getEndOffsetMultiplier () const
{
    return _end_offset_m;
}

int ReverseAxis::getFrontPixel () const
{
    // front pixel is the bottom most pixel of the set of pixels representing the first value.
    // the bottom most pixel is the second pixel, so return .second.
    return getPixel(_min_val - _start_offset_m, _tick_thickness__px).second;
}

int ReverseAxis::getEndPixel () const
{
    // end pixel is the top most pixel of the set of pixels representing the last value.
    // the top most pixel is the first pixel, so return .first.
    return getPixel(_max_val + _end_offset_m, _tick_thickness__px).first;
}

void ReverseAxis::moveCrossPixel (int pixel)
{
    _cross_pixel__px = pixel;
}

void ReverseAxis::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
}

void ReverseAxis::setTickThickness (int tickThicknessPx)
{
    _tick_thickness__px = tickThicknessPx;
}