#ifndef Y_AXIS_B2T_H
#define Y_AXIS_B2T_H

#include <string>
#include <memory>
#include "SDL.h"
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include "AxisFormat.h"
#include "TextRect.h"

class YAxisB2T
{
    public:
        YAxisB2T (
            std::string title,
            PixelConverter* pixelConverter,
            AxisFormat axisFormat,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int majTickSpacing,
            int minTickSpacing,  // in units, not pixels
            int labelSpacing, // in units, not in pixels.
            double labelUnitFactor,
            int labelDecimalPlaces
        );

        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void print (Renderer* renderer);

    private:
        std::string _title;
        PixelConverter* _pc;
        AxisFormat _axis_format;
        int _x_coord__px;
        int _y_coord__px;
        int _min_val;
        int _max_val;
        int _min_tick_spacing;
        int _maj_tick_spacing;
        int _label_spacing;
        double _label_unit_factor;
        int _label_decimal_places;
        
        int _top_most_pixel_y__px;
        int _bottom_most_pixel_y__px;
        int _min_val__px;
        int _max_val__px; 

        void addVerticalLine (std::vector<SDL_Rect>& rects);
        void addTicksAndLabels (std::vector<SDL_Rect>& rects, std::vector<TextRect>& texts);
        void addTitle (std::vector<TextRect>& texts);
        
};

#endif