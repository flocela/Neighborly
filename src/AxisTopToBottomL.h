#ifndef AXIS_BOTTOM_TO_TOP_R_H
#define AXIS_BOTTOM_TO_TOP_R_H

#include "AxisFormat.h"
#include "ForwardAxis.h"
#include "Renderer.h"
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
        ~AxisTopToBottomL () noexcept = default;

        int getAxisLengthPx () const;

        // the label are the numbers to the right of the axis plus
        // the length of the tick outside the chart plus
        // the space between the label and the tick plus
        // the axis thickness.
        // the length is in the x direction.
        int getLabelLengthPx () const;

        std::pair<int,int> getPixel (double yVal, int dotSize) const;
        
        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void print (Renderer* renderer) const;

        int sizeXPx() const;

        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        void setPxPerUnit (int pixels);

        void setTickThickness (int tickThicknessPx);

    private:
        AxisFormat _axis_format;
        ForwardAxis _forward_axis;
        int _x_cross__px;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks.

        void printVerticalLine (std::vector<Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing () const;

        int calcMajTickSpacing ()  const;
};

#endif