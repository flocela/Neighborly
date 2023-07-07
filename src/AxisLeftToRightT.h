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
        std::pair<int, int> getPixel (double xVal, int dotSize) const;
        
        void print (Renderer* renderer) const;

        int sizeXPx() const;

        int sizeYPx() const;

        void moveCrossHairs (int xPx, int yPx);

        void setPxPerUnit (int pixels);
        
        void setTickThickness (int tickThicknessPx);

    private:
        std::string _title; //TODO should probably get rid of this.
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