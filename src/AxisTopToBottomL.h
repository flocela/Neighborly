#ifndef AXIS_BOTTOM_TO_TOP_R_H
#define AXIS_BOTTOM_TO_TOP_R_H

#include "AxisFormat.h"
#include "ForwardAxis.h"
#include "Renderer.h"
#include "TextRect.h"

// Vertical axis, number run from top to bottom. Labels are on left.
class AxisTopToBottomL
{
    public:
        AxisTopToBottomL (
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
        AxisTopToBottomL () = delete;
        AxisTopToBottomL (const AxisTopToBottomL& o) = default;
        AxisTopToBottomL (AxisTopToBottomL&& o) noexcept = default;
        AxisTopToBottomL& operator= (const AxisTopToBottomL& o) = default;
        AxisTopToBottomL& operator=(AxisTopToBottomL&& o) noexcept = default;
        ~AxisTopToBottomL () noexcept = default;

        int getAxisLengthPx () const;

        // The labels are the numbers to the left of the axis, but their length is more
        // than just the number.
        // The label length is the length of the digits in the label plus
        // the space between the label and the tick plus
        // the length of the tick outside the chart.
        // The length is in the x direction.
        int getLabelLengthPx () const;

        // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
        // would be {1, 5}.
        std::pair<int, int> getPixels (double xVal, int dotSize) const;
        
        void print (Renderer* renderer) const;

        // Returns labelLength plus axis thickness.
        int sizeXPx() const;

        // Same as getAxisLengthPx()
        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        // Sets the pixels per unit. Updates the major and minor tick spacing.
        void setPxPerUnit (int pixels);

        void setTickThickness (int tickThicknessPx);

    private:
        AxisFormat _axis_format;
        ForwardAxis _forward_axis;

        int _x_cross__px;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks.

        void addVerticalLine (std::vector<Rect>& rects) const;

        void addTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing () const;

        int calcMajTickSpacing ()  const;
};

#endif