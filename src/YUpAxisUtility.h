#ifndef Y_UP_AXIS_UTILITY_H
#define Y_UP_AXIS_UTILITY_H

#include <string>
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include <memory>


class YUpAxisUtility
{
    public:
        YUpAxisUtility (
            std::string title,
            Renderer* renderer,
            PixelConverter* pixelConverter,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int cell_size__px,    // one unit size in pixels
            int minVal, // min value delineated with tick. Located startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px number of pixels afer maxVal.
            int endOffset__px, // axis continues past maxVal for endOffset__px number of pixels.
            int tickSpacing,  // in units, not pixels
            int labelSpacing, // in units, not in pixels.
            int labelFontSize,
            int titleFontSize
        );

        // Renders axis from bottom to top, title is on left side (used for vertical axes).
        void bottom2TopTitleOnLeft ();

    private:
        std::string _title;
        Renderer* _renderer;
        PixelConverter* _pc;
        int _x_coord__px;
        int _y_coord__px;
        int _cell_size__px;
        int _min_val;
        int _max_val;
        int _start_offset__px; // the number of pixels before the minimum value
        int _end_offset__px;   // the number of pixels after the maximum value
        int _tick_spacing;
        int _label_spacing;
        int _label_font_size;
        int _title_font_size;
        int _title_placement_from_axis = 50;

        int _top_most_pixel;
        int _bottom_most_pixel;
        int _min_val__px;
        int _max_val__px; 
        int _tick_width__px;
        int _tick_length__px = 4;
        
};

#endif