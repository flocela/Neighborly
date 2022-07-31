#ifndef X_AXIS_L2R_BOTTOM_H
#define X_AXIS_L2R_BOTTOM_H

#include <string>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include "AxisFormat.h"
#include <memory>
#include "TextRect.h"


class XAxisL2RBottom
{
    public:
        XAxisL2RBottom (
            std::string title,
            PixelConverter* pixelConverter,
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int majTickSpacing,
            int minTickSpacing,  // in units, not pixels
            int labelSpacing // in units, not in pixels.
        );
        // Renders axis from left to right with title at top (used for horizontal axes).
        void print (Renderer* renderer);

    
    private:
        std::string _title;
        Renderer* _renderer;
        PixelConverter* _pc;
        AxisFormat _axis_format;
        int _x_coord__px;
        int _y_coord__px;
        int _min_val;
        int _max_val;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _label_spacing;
        
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