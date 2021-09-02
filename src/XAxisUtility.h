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
            PixelConverter* pixelConverter,
            int x_coordinate__px, // where x and y axis meet
            int y_coordinate__px, // where x and y axis meet
            int cellSize__px,
            int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
            int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
            int endOffset__px, // axis continues past maxVal for endOffset__px pixels.
            int tickSpacing,  // in units, not pixels
            int labelSpacing, // in units, not in pixels.
            int labelFontSize,
            int titleFontSize
        );
        // Renders axis from left to right with title at top (used for horizontal axes).
        void left2RightTitleOnTop ();

    
    private:
        std::string _title;
        Renderer* _renderer;
        PixelConverter* _pc;
        int _x_coord__px;
        int _y_coord__px;
        int _cell_size__px;
        int _min_val;
        int _max_val;
        int _start_offset__px; //offset before minimum value in pixels
        int _end_offset__px;   //overrun after maximum value in pixels
        int _tick_spacing;
        int _label_spacing;
        int _label_font_size;
        int _title_font_size;
        int _title_placement_from_axis = 34;
        
        int _left_most_pixel;
        int _right_most_pixel;
        int _min_val__px;
        int _max_val__px; 
        int _tick_width__px;
        int _tick_height__px = 4;
        
};

#endif