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
        void print (Renderer* renderer) const;
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);
        int sizeXPx() const;
        int sizeYPx() const;

        // returns the y-pixel for yVal. If pxPerUnit is odd, then result is at center of unit.
        // If pxPerUnit is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from the x's zero value.)
        int getPixel (double xVal) const;
        int getCenterValXPx () const;
        int getAxisLengthPx() const;
    
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

        void printHorizontalLine (std::vector<SDL_Rect>& rects) const;

        void printTicksAndLabels (
            std::vector<SDL_Rect>& rects,
            std::vector<TextRect>& texts) const;

        int calcRightMostPixel_X () const;

        int calcMinTickSpacing (int pixelsPerUnit) const;
        
        int calcMajTickSpacing (int pixelsPerUnit) const;

};

#endif