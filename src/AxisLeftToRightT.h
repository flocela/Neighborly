#ifndef AXIS_LEFT_TO_RIGHT_T__H
#define AXIS_LEFT_TO_RIGHT_T__H

#include "AxisFormat.h"
#include "ForwardAxis.h"
#include "Renderer.h"
#include "TextRect.h"

// Renders axis from left to right with title at top (used for horizontal axes).
class AxisLeftToRightT
{
    public:
        AxisLeftToRightT (
            AxisFormat axisFormat,
            int xCrossPx, // where x and y axis meet, x-coordinate
            int yCrossPx, // where x and y axis meet, y-coordinate
            int minVal,
            int maxVal,
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );
        AxisLeftToRightT () = delete;
        AxisLeftToRightT (const AxisLeftToRightT& o) = default;
        AxisLeftToRightT (AxisLeftToRightT&& o) noexcept = default;
        AxisLeftToRightT& operator= (const AxisLeftToRightT& o) = default;
        AxisLeftToRightT& operator=(AxisLeftToRightT&& o) noexcept = default;
        ~AxisLeftToRightT () noexcept = default;

        int getAxisLengthPx() const;

        // The labels are the numbers above the axis.
        // Their length includes more than just the number.
        // The label length is the height of the numbers plus
        // the space between the lable and the tick plus
        // the length of the tick outside the chart.
        // The length is in the y direction.
        int getLabelLengthPx () const;

        int getCenterValXPx () const;

        // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
        // would be {1, 5}.
        std::pair<int, int> getPixels (double xVal, int dotSize) const;
        
        void print (Renderer* renderer) const;

        int sizeXPx() const;

        // Returns label length plus axis thickness.
        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        // Sets the pixels per unit. Updates the major and minor tick spacing.
        void setPxPerUnit (int pixels);
        
        void setTickThickness (int tickThicknessPx);

    private:
        AxisFormat _axis_format;
        ForwardAxis _forward_axis;

        int _y_cross__px; // where x and y axes cross, this is the y-coordinate
        int _min_tick_spacing;
        int _maj_tick_spacing;

        void addHorizontalLine (std::vector<Rect>& rects) const;

        void addTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing () const;

        int calcMajTickSpacing () const;

};

#endif