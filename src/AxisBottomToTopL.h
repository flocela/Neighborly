#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include <string>
#include <memory>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include "AxisFormat.h"
#include "TextRect.h"

class AxisBottomToTopL
{
    public:
        AxisBottomToTopL (
            std::string title,
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int pxPerUnit,
            int tickThickness,
            int startOffsetMultiplier,
            int endOffsetMultiplier
        );

        // Renders axis from bottom to top, title is on left side (used for vertical axes).
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
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels
        int _label_spacing;
        int _start_offset_m; // start offst multiplier; multiply by _px_per_unit
        int _end_offset_m; // start offst multiplier; multiply by _px_per_unit

        void addVerticalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        int calcTopMostPixelY ()
        {
            return _y_cross__px - (_px_per_unit * (_diff + _start_offset_m + _end_offset_m));
        }
        int calcMinTickSpacing (int pixelsPerUnit) { return (pixelsPerUnit >= 10)? 1 : 5; }
        int calcMajTickSpacing (int pixelsPerUnit) { return (pixelsPerUnit > 10)? 5 : 10; }
        int calcLabelSpacing (int pixelsPerUnit) { return (pixelsPerUnit > 10)? 5 : 10; }
        
        
};

#endif