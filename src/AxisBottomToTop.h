#ifndef AXIS_BOTTOM_TO_TOP_H
#define AXIS_BOTTOM_TO_TOP_H

#include <string>
#include <memory>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include "AxisFormat.h"
#include "TextRect.h"

class AxisBottomToTop
{
    public:
        AxisBottomToTop (
            std::string title,
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int majTickSpacing,
            int minTickSpacing,  // in units, not pixels
            int labelSpacing, // in units, not in pixels.
            int pxPerUnit 
        );

        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void print (Renderer* renderer);

    private:
        std::string _title;
        AxisFormat _axis_format;
        int _x_cross__px;
        int _y_cross__px;
        int _min_val;
        int _max_val;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _label_spacing;
        int _px_per_unit;
        
        int _top_most_pixel_y__px;
        int _bottom_most_pixel_y__px;
        int _min_val__px;
        int _max_val__px; 

        void addVerticalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        void addTitle (std::vector<TextRect>& texts);
        
};

#endif