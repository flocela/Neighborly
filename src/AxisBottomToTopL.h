#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include "Renderer.h"
#include "SDL.h"
#include "AxisFormat.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class AxisBottomToTopL
{
    public:
        AxisBottomToTopL (
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal,
            int maxVal,
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );
        AxisBottomToTopL () = delete;
        AxisBottomToTopL (const AxisBottomToTopL& o) = default;
        AxisBottomToTopL (AxisBottomToTopL&& o) noexcept = default;
        AxisBottomToTopL& operator= (const AxisBottomToTopL& o) = default;
        AxisBottomToTopL& operator=(AxisBottomToTopL&& o) noexcept = default;
        ~AxisBottomToTopL () = default;

        int getAxisLengthPx () const;

        // returns the y-pixel for yVal. If pxPerUnit is odd, then result is at center of unit.
        // If pxPerUnit is even, then center is denoted by two pixels,
        // and the result is the first pixel. (The first pixel is from the cross hairs or _y_cross__px.)
        int getPixel (double yVal) const;
        
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
        // start offset multiplier; multiply by _px_per_unit to get length of axis
        // from cross hairs to where min_val's unit starts.
        int _start_offset_m; 
        // end offset multiplier; multiply by _px_per_unit to get length of axis
        // after max_val's unit ends 
        int _end_offset_m; // end offset multiplier; multiply by _px_per_unit
        int _text_spacer = 3; // space to the right of labels, and the the left of tick marks

        void printVerticalLine (std::vector<Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcTopMostPixelWithValue_Y () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;

        int calcMajTickSpacing (int pixelsPerUnit) const;

     
};

#endif