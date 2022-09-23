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


class AxisLeftToRightT
{
    public:
        AxisLeftToRightT (
            std::string title,
            AxisFormat axisFormat,
            int xCrossPx, // where x and y axis meet
            int yCrossPx, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );
        // Renders axis from left to right with title at top (used for horizontal axes).
        void print (Renderer* renderer);
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx) {_tick_thickness__px = tickThicknessPx;}
    
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
        int _label_spacing;
        int _start_offset_m;
        int _end_offset_m;

        void addHorizontalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);

        int calcRightMostPixelX ()
        {
            std::cout << "px_per_unit, diff, startoffset, end offsetM: ";
            std::cout << _px_per_unit << ", " << _diff << ", " << _start_offset_m << ", " << _end_offset_m << std::endl;
            return _x_cross__px + (_px_per_unit * (_diff + _start_offset_m + _end_offset_m));
        }

        int calcMinTickSpacing (int pixelsPerUnit) { return (pixelsPerUnit >= 10)? 1 : 5; }
        int calcMajTickSpacing (int pixelsPerUnit) { return (pixelsPerUnit > 10)? 5 : 10; }
        int calcLabelSpacing (int pixelsPerUnit) { return (pixelsPerUnit > 10)? 5 : 10; }
        
};

#endif