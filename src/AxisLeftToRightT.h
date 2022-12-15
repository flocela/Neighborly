#ifndef AXIS_LEFT_TO_RIGHT_T__H
#define AXIS_LEFT_TO_RIGHT_T__H

#include <string>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
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
        
        void print (Renderer* renderer);
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);

        int sizeYPx();
        int sizeXPx();

        // returns the x-pixel for the top left corner of this xVal's unit
        int getXPixelForPrinting (double xVal);
    
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

        void addHorizontalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);

        int calcRightMostPixelX ();

        int calcMinTickSpacing (int pixelsPerUnit);
        int calcMajTickSpacing (int pixelsPerUnit);
        int calcLabelSpacing (int pixelsPerUnit);

        int axisLengthPx();
        
};

#endif