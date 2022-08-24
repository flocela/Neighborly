#ifndef AXIS_LEFT_TO_RIGHT_H
#define AXIS_LEFT_TO_RIGHT_H

#include <string>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include "AxisFormat.h"
#include <memory>
#include "TextRect.h"


class AxisLeftToRightB
{
    public:
        AxisLeftToRightB (
            std::string title,
            AxisFormat axisFormat,
            int xCrossPx, // where x and y axis meet
            int yCrossPx, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int majTickSpacing,
            int minTickSpacing,  // in units, not pixels
            int labelSpacing, // in units, not in pixels.
            int startOffset,
            int endOffset,
            int pxPerUnit
        );
        // Renders axis from left to right with title at top (used for horizontal axes).
        void print (Renderer* renderer);

    
    private:
        std::string _title;
        Renderer* _renderer;
        AxisFormat _axis_format;
        int _x_cross__px;
        int _y_cross__px;
        int _zero__px;
        int _min_val;
        int _max_val;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _label_spacing;
        int _start_offset__px;
        int _end_offset__px;
        int _px_per_unit;
        
        int _left_most_pixel_x__px;
        int _right_most_pixel_x__px;
        int _min_val__px;
        int _max_val__px; 

        int calcHorizontalLineLength();
        void addHorizontalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        void addTitle (std::vector<TextRect>& texts);

        
};

#endif