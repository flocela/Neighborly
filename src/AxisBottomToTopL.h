#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include "Renderer.h"
#include "AxisFormat.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class AxisBottomToTopL
{
    public:
        AxisBottomToTopL (
            AxisFormat axisFormat,
            int horizLengthPx,
            int x_coordinate__px,
            int y_coordinate__px,
            bool centeredOnPixel,
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

        // the label are the numbers to the left of the axis plus
        // the space between the label and the tick plus
        // the length of the tick outside the chart plus
        // the axis thickness.
        // the length is in the x direction.
        int getLabelLengthPx () const;

        std::pair<int, int> getPixel (double yVal, int dotSize) const;
        
        void print (Renderer* renderer) const;
        
        // Does not include horizontal lines continuing from tick marks
        // Same as getLabelLengthPx()
        int sizeXPx() const;
        
        // Same as getAxisLengthPx()
        int sizeYPx() const;
        
        void moveCrossHairs (int xPx, int yPx);

        // There's background horizontal lines that run across the chart. They
        // line up with the major and minor tick marks.
        void setHorizLength (int horizLengthPx);
        
        // Sets the pixels per unit. May change the major and minor tick spacing.
        void setPxPerUnit (int pixels);
        
        void setTickThickness (int tickThicknessPx);

        void setCenteredOnPixel (bool centered);

    private:
        AxisFormat _axis_format;
        
        // width of horizontal lines that are a continuation of tick marks,
        // they extend into the chart and are usually a greyed out color.
        int _horiz_line_length__px;
        int _x_cross__px; // where x and y axis meet
        int _y_cross__px; // where x and y axis meet
        bool _centered_on_pixel = false; // x-axis is centered on a pixel, not between two pixels
        int _min_val; // the minimum data point value
        int _max_val; // the maximum data point value
        int _diff; // _max_val minus _min_val
        int _px_per_unit;
        int _tick_thickness__px;
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels

        // multiply the _start_offset_m by _px_per_unit to get length of axis
        // from cross hairs to where min_val.
        int _start_offset_m;

        // multiply _end_offset_m by _px_per_unit to get length of axis
        // after max_val 
        int _end_offset_m; // end offset multiplier; multiply by _px_per_unit

        int _text_spacer = 3; // space to the right of labels, and to the left of tick marks

        void setVerticalLine (std::vector<Rect>& rects) const;

        void setTicksAndLabels (
            std::vector<Rect>& horizLinesMaj,
            std::vector<Rect>& horizLinesMin,
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing (int pixelsPerUnit) const;

        int calcMajTickSpacing (int pixelsPerUnit) const;
        
};

#endif