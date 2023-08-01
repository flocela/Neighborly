#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include "AxisFormat.h"
#include "Renderer.h"
#include "ReverseAxis.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class AxisBottomToTopL
{
    public:
        AxisBottomToTopL (
            AxisFormat axisFormat,
            // length of horizontal background lines. They line up with ticks and go
            // across the chart.
            int horizLengthPx,
            int x_coordinate__px,
            int y_coordinate__px,
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
        ~AxisBottomToTopL () noexcept = default;

        int getAxisLengthPx () const;

        // The labels are the numbers to the left of the axis, but their length is more
        // than just the number.
        // The label length is the length of the digits in the label plus
        // the space between the label and the tick plus
        // the length of the tick outside the chart plus
        // the axis thickness.
        // The length is in the x direction.
        int getLabelLengthPx () const;


        std::pair<int, int> getPixel (double yVal, int dotSize) const;
        
        void print (Renderer* renderer) const;
        
        // Same as getLabelLengthPx()
        int sizeXPx() const;
        
        // Same as getAxisLengthPx()
        int sizeYPx() const;
        
        void moveCrossHairs (int xPx, int yPx);

        // There are background horizontal lines that run across the chart. They
        // line up with the major and minor tick marks.
        void setHorizLength (int horizLengthPx);
        
        // Sets the pixels per unit. May change the major and minor tick spacing.
        void setPxPerUnit (int pixels);
        
        void setTickThickness (int tickThicknessPx);

    private:
        AxisFormat _axis_format;
        
        // width of horizontal background lines that are a continuation of tick marks.
        // They extend into the chart and are usually a greyed out color.
        int _horiz_line_length__px;
        ReverseAxis _reverse_axis;
        int _x_cross__px; // where x and y axis meet
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels

        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks

        // This is the axis vertical line.
        void addVerticalLine (std::vector<Rect>& rects) const;

        void addTicksAndLabels (
            std::vector<Rect>& horizLinesMaj,
            std::vector<Rect>& horizLinesMin,
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing () const;

        int calcMajTickSpacing () const;
        
};

#endif