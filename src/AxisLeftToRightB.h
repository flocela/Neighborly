#ifndef AXIS_LEFT_TO_RIGHT_B__H
#define AXIS_LEFT_TO_RIGHT_B__H

#include "AxisFormat.h"
#include "ForwardAxis.h"
#include "Renderer.h"
#include "TextRect.h"

// Renders axis from left to right with title at bottom (used for horizontal axes).
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

        int getCenterValXPx () const;

        // the label length is the height of the numbers below the axis plus
        // the length of the tick outside the chart plus
        // the space between the label and the tick plus
        // the axis thickness.
        // the length is in the y direction.
        int getLabelLengthPx () const;

        std::pair<int, int> getPixel (double xVal, int dotSize) const;

        void print (Renderer* renderer) const;

        int sizeXPx() const;

        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        void setPxPerUnit (int pixels);
        
        void setTickThickness (int tickThicknessPx);

    private:
        AxisFormat _axis_format;
        ForwardAxis _forward_axis;
        int _y_cross__px; // where x and y axes cross, this is the y-coordinate
        int _min_tick_spacing;
        int _maj_tick_spacing;

        void printHorizontalLine (std::vector<Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcMinTickSpacing () const;
        
        int calcMajTickSpacing () const;

};

#endif