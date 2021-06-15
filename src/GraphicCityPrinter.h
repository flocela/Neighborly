#ifndef GRAPHIC_CITY_PRINTER_H
#define GRAPHIC_CITY_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include <vector>

// Takes in a Renderer and city chart origin and offsets.
// Remembers this initializing information so user can 
// easily print city houses using city coordinates.
class GraphicCityPrinter
{
    public:
        GraphicCityPrinter (
            Renderer* renderer,
            Coordinate chartOrigin,
            int gridSize,
            int minX,
            int maxX,
            int minY,
            int maxY,
            int xAxisOverrun,
            int yAxisOverrun,
            int xAxisOffset,
            int yAxisOffset,
            int titlesAtLeftOffset,
            int titlesAtTopOffset,
            int fontSize
        ):  _renderer{renderer},
            _chart_origin{chartOrigin},
            _grid_size{gridSize},
            _min_x{minX},
            _max_x{maxX},
            _min_y{minY},
            _max_y{maxY},
            _x_axis_offset{xAxisOffset},
            _y_axis_offset{yAxisOffset},
            _x_axis_overrun{xAxisOverrun},
            _y_axis_overrun{yAxisOverrun},
            _titles_at_left_offset{titlesAtLeftOffset},
            _titles_at_top_offset{titlesAtTopOffset},
            _font_size{fontSize}
        {}

        void printCity ();
          
    private:
        Renderer* _renderer;
        // chartOrigin is top left corner of entire chart, including titles. 
        // Coordinate uses window coordinate system.
        Coordinate _chart_origin;
        int _grid_size;
        int _min_x;
        int _max_x;
        int _min_y;
        int _max_y;
        // xAxisOffset exists so houses do not lie on the y-axis. It is the number of 
        // _grid_sizes that xAxis will be offset to the left.
        // Instead of xAxis starting at 320, it will start at 314 if offset is 3
        // and the _grid_size is 2.
        int _x_axis_offset;
        int _y_axis_offset;
        // overruns are how much farther the axis runs past the last house
        int _x_axis_overrun;
        int _y_axis_overrun;
        // titlesAtTopOffset and titlesLeftOffset is room given for titles at top
        // and left of the graph.
        // fontSize is for x and y axes.
        int _titles_at_left_offset;
        int _titles_at_top_offset;
        int _font_size;

        // x-axis SDL_Rects and x-axis TextRects.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<TextRect> _x_texts = {};

        void addCityXAxis ();



};

#endif