#ifndef AXIS_LEFT_TO_RIGHT_T__H
#define AXIS_LEFT_TO_RIGHT_T__H

#include <string>
#include "SDL.h"
#include "Renderer.h"
#include "Coordinate.h"
#include "AxisFormat.h"
#include <memory>
#include "TextRect.h"

// Renders axis from left to right with title at top (used for horizontal axes).
class AxisLeftToRightT
{
    public:
        AxisLeftToRightT (
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
        
        void print (Renderer* renderer) const;
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);

        int sizeYPx() const;
        int sizeXPx() const;

        // returns the y-pixel for yVal. If pxPerUnit is odd, then result is at center of unit.
        // If pxPerUnit is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from x's zero.)
        int getPixel (double xVal) const;
        int axisLengthPx() const;
        int getCenterValXPx() const;
    
    private:
        std::string _title;
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

        void printHorizontalLine (std::vector<SDL_Rect>& rects) const;
        void printTicksAndLabels (
            std::vector<SDL_Rect>& rects,
            std::vector<TextRect>& texts) const;

        // right most pixel on horizontal line.
        int calcRightMostPixelWithValue_X () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;
        int calcMajTickSpacing (int pixelsPerUnit) const;
        int calcLabelSpacing (int pixelsPerUnit) const;

};

#endif