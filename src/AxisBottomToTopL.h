#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include "Axis.h"
#include "AxisFormat.h"
#include "GrAxis.h"
#include "Renderer.h"
#include "ReverseAxis.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class AxisBottomToTopL : public GrAxis
{
    public:
        AxisBottomToTopL (
            std::unique_ptr<Axis> axis, // TODO change to unique pointer
            AxisFormat axisFormat,
            // length of horizontal background lines. They line up with ticks and go
            // across the chart.
            int horizLengthPx,
            int x_coordinate__px
        );
        AxisBottomToTopL () = delete;
        AxisBottomToTopL (const AxisBottomToTopL& o) = default;
        AxisBottomToTopL (AxisBottomToTopL&& o) noexcept = default;
        AxisBottomToTopL& operator= (const AxisBottomToTopL& o) = default;
        AxisBottomToTopL& operator=(AxisBottomToTopL&& o) noexcept = default;
        ~AxisBottomToTopL () noexcept = default;

        int getAxisLengthPx () const override;

        // The labels are the numbers to the left of the axis, but their length is more
        // than just the number.
        // The label length is the length of the digits in the label plus
        // the space between the label and the tick plus
        // the length of the tick outside the chart.
        // The length is in the x direction.
        int getLabelLengthPx () const override;

        // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
        // would be {1, 5}.
        std::pair<int, int> getPixels (double yVal, int dotSize) const override;
        
        void print (Renderer* renderer) const override;
        
        // The label length plus the axis thickness.
        int sizeXPx() const override;
        
        // Same as getAxisLengthPx()
        int sizeYPx() const override;
        
        void moveCrossHairs (int xPx, int yPx) override;

        // There are background horizontal lines that run across the chart. They
        // line up with the major and minor tick marks.
        void setHorizLength (int horizLengthPx) override;
        
        // Sets the pixels per unit. Updates the major and minor tick spacing.
        void setPxPerUnit (int pixels) override;
        
        void setTickThickness (int tickThicknessPx) override;

    private:
        AxisFormat _axis_format;
        
        // width of horizontal background lines that are a continuation of tick marks.
        // They extend into the chart and are usually a greyed out color.
        int _horiz_line_length__px;

        int _x_cross__px; // where x and y axis meet
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels

        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks

        // This is the axis vertical line.
        void addVerticalLine (std::vector<Rect>& rects) const;

        void addTicksAndLabels (
            std::vector<Rect>& backgroundLinesMaj, // horizontal lines that cross the chart
            std::vector<Rect>& backgroundLinesMin, // horizontal lines that cross the chart
            std::vector<Rect>& ticks,
            std::vector<TextRect>& texts) const; // number next to tick

        int calcMinTickSpacing () const;

        int calcMajTickSpacing () const;
        
};

#endif