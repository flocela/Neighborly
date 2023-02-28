#ifndef AXIS_BOTTOM_TO_TOP_R_H
#define AXIS_BOTTOM_TO_TOP_R_H

#include <string>
#include <memory>
#include "SDL.h"
#include "Renderer.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include "TextRect.h"

class AxisTopToBottomL
{
    public:
        AxisTopToBottomL (
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );

        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void print (Renderer* renderer) const;
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);
        int sizeXPx() const;
        int sizeYPx() const;

        // returns the y-pixel for yVal. If pxPerUnit is odd, then result is at center of unit.
        // If pxPerUnit is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from the y-s zero.)
        int getPixel (double yVal) const;
        int getAxisLengthPx () const;

    private:
        AxisFormat _axis_format;
        int _x_cross__px;
        int _y_cross__px;
        int _min_val;
        int _max_val;
        int _diff;
        int _px_per_unit;
        int _tick_thickness__px;
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels
        int _start_offset_m; // start offst multiplier; multiply by _px_per_unit
        int _end_offset_m; // start offst multiplier; multiply by _px_per_unit

        void printVerticalLine (std::vector<SDL_Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<SDL_Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcBotMostPixel_Y () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;

        int calcMajTickSpacing (int pixelsPerUnit)  const;
};

#endif