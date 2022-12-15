#ifndef AXIS_BOTTOM_TO_TOP_L_H
#define AXIS_BOTTOM_TO_TOP_L_H

#include "renderer.h"
#include "SDL.h"
#include "AxisFormat.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class AxisBottomToTopL
{
    public:
        AxisBottomToTopL (
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

        void print (Renderer* renderer);
        void moveCrossHairs (int xPx, int yPx);
        void setPxPerUnit (int pixels);
        void setTickThickness (int tickThicknessPx);
        int sizeXPx();
        int sizeYPx();

        // returns the y-pixel for the top left corner for this yVal's unit.
        int getYPixelForPrinting (double yVal);

    private:
        AxisFormat _axis_format;
        int _x_cross__px;
        int _y_cross__px;
        int _min_val;
        int _max_val;
        int _px_per_unit;
        int _tick_thickness__px;
        int _min_tick_spacing; // in units, not pixels
        int _maj_tick_spacing; // in units, not pixels
        // start offset multiplier; multiply by _px_per_unit to get length of axis
        // from cross hairs to where min_val's unit starts.
        int _start_offset_m; 
        // end offset multiplier; multiply by _px_per_unit to get length of axis
        // after max_val's unit ends 
        int _end_offset_m; // end offset multiplier; multiply by _px_per_unit
        int _text_spacer = 3; // space to the right of labels, and the the left of tick marks

        void addVerticalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        int calcTopMostPixelY ();
        int calcMinTickSpacing (int pixelsPerUnit);
        int calcMajTickSpacing (int pixelsPerUnit);

        int axisLengthPx ();
        
        
        
};

#endif