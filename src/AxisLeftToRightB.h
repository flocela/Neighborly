#ifndef AXIS_LEFT_TO_RIGHT_B__H
#define AXIS_LEFT_TO_RIGHT_B__H

#include "Renderer.h"
#include "AxisFormat.h"
#include "TextRect.h"


class AxisLeftToRightB
{
    public:
        AxisLeftToRightB (
            AxisFormat axisFormat,
            int xCrossPx, // where x and y axis meet
            int yCrossPx, // where x and y axis meet
            int minVal,
            int maxVal,
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );
        AxisLeftToRightB () = delete;
        AxisLeftToRightB (const AxisLeftToRightB& o) = default;
        AxisLeftToRightB (AxisLeftToRightB&& o) noexcept = default;
        AxisLeftToRightB& operator= (const AxisLeftToRightB& o) = default;
        AxisLeftToRightB& operator=(AxisLeftToRightB&& o) noexcept = default;
        ~AxisLeftToRightB () noexcept = default;

        int getAxisLengthPx() const;

        // the label length is the height of the numbers below the axis plus
        // the length of the tick outside the chart plus
        // the space between the label and the tick plus
        // the axis thickness.
        // the length is in the y direction.
        int getLabelLengthPx () const;

        int getCenterValXPx () const;

        // returns the y-pixel for yVal. If tick thickness is odd, then result is one pixel.
        // If the tick thickness is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from the x's zero value.)
        int getPixel (double xVal) const;

        int sizeXPx() const;

        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        void print (Renderer* renderer) const;

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
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _start_offset_m;
        int _end_offset_m;

        void printHorizontalLine (std::vector<Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcRightMostPixelWithValue_X () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;
        
        int calcMajTickSpacing (int pixelsPerUnit) const;

};

#endif