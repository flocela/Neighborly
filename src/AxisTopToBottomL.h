#ifndef AXIS_BOTTOM_TO_TOP_R_H
#define AXIS_BOTTOM_TO_TOP_R_H

#include "Renderer.h"
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
        AxisTopToBottomL () = delete;
        AxisTopToBottomL (const AxisTopToBottomL& o) = default;
        AxisTopToBottomL (AxisTopToBottomL&& o) noexcept = default;
        AxisTopToBottomL& operator= (const AxisTopToBottomL& o) = default;
        AxisTopToBottomL& operator=(AxisTopToBottomL&& o) noexcept = default;
        ~AxisTopToBottomL () = default;

        int getAxisLengthPx () const;

        // the label are the numbers to the right of the axis plus
        // the length of the tick outside the chart plus
        // the space between the label and the tick plus
        // the axis thickness.
        // the length is in the x direction.
        int getLabelLengthPx () const;

        // returns the y-pixel for yVal. If tick thickness is odd, then result is one pixel.
        // If tick thickness is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from the y's zero.)
        int getPixel (double yVal) const;
        
        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void print (Renderer* renderer) const;

        int sizeXPx() const;

        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        void setPxPerUnit (int pixels);

        void setTickThickness (int tickThicknessPx);

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
        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks.

        void printVerticalLine (std::vector<Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcBotMostPixel_Y () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;

        int calcMajTickSpacing (int pixelsPerUnit)  const;
};

#endif