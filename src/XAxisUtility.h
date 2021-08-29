#ifndef X_AXIS_UTILITY_H
#define X_AXIS_UTILITY_H

#include <string>
#include "renderer.h"
#include "Coordinate.h"
#include "PixelConverter.h"
#include <memory>


class XAxisUtility
{
    public:
        XAxisUtility (
            std::string title,
            Renderer* renderer,
            int x_coordinate__px,
            int y_coordinate__px,
            int cell_size__px,
            int minVal,
            int maxVal,
            int startOffset__px,
            int endOffset__px,
            int labelSpacing,
            int labelFontSize,
            int titleFontSize
        );
        // Renders axis from left to right with title at top (used for horizontal axes).
        void left2RightTop ();

    
    private:
        std::string _title;
        Renderer* _renderer;
        int _x_coord__px;
        int _y_coord__px;
        int _cell_size__px;
        int _min_val;
        int _max_val;
        int _start_offset__px; //offset before minimum value in pixels
        int _end_offset__px;   //overrun after maximum value in pixels
        int _label_spacing;
        int _label_font_size;
        int _title_font_size;
        
        std::unique_ptr<PixelConverter> _pc;
        int _left_most_pixel;
        int _right_most_pixel;
        int _min_val__px;
        int _max_val__px; 
        int _first_tick_val;
        int _first_tick__px;
        int _tick_width__px;
        int _tick_height__px = 4;
        
};

#endif