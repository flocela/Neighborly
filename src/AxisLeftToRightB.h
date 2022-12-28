#ifndef AXIS_LEFT_TO_RIGHT_B__H
#define AXIS_LEFT_TO_RIGHT_B__H

#include "renderer.h"
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
        void print (Renderer* renderer);
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);
        int sizeYPx();
        int sizeXPx();

        // returns the x-pixel for xVal. If pxPerUnit is odd, then result is at center of unit.
        // If pxPerUnit is even, then center is denoted by two pixels,
        // and the result is the second pixel. (The second pixel is from zero.)
        int getPixel (double xVal);
    
    private:
        AxisFormat _axis_format;
        int _x_cross__px;
        int _y_cross__px;
        int _min_val;
        int _max_val;
        int _px_per_unit;
        int _tick_thickness__px;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _start_offset_m;
        int _end_offset_m;

        void addHorizontalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        int calcRightMostPixelX ();

        int calcMinTickSpacing (int pixelsPerUnit);
        int calcMajTickSpacing (int pixelsPerUnit);

        int axisLengthPx();
        
};

#endif