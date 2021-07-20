#ifndef GRAPHIC_CITY_PRINTER_H
#define GRAPHIC_CITY_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"

// Takes in a Renderer and city chart origin and offsets.
// Remembers this initializing information so user can 
// easily print city houses using city coordinates.
class GraphicCityPrinter
{
    public:
        GraphicCityPrinter (
            Renderer* renderer,
            std::map<Coordinate, House*> coordToHouseMap,
            std::map<Color, std::vector<int>> rgbaPerColor,
            Coordinate chartOrigin,
            int gridSize,
            int minX,
            int maxX,
            int minY,
            int maxY,
            int xAxisOffset,
            int yAxisOffset,
            int xAxisOverrun,
            int yAxisOverrun,
            int titlesAtLeftOffset,
            int titlesAtTopOffset,
            int fontSize
        ):  _renderer{renderer},
            _coord_to_house_map{coordToHouseMap},
            _rgba_per_color{rgbaPerColor},
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

        void printCity (std::map<House*, Resident*> houseToResMap);
          
    private:
        Renderer* _renderer;
        std::map<Coordinate, House*> _coord_to_house_map;
        std::map<Color, std::vector<int>> _rgba_per_color;

        // chartOrigin is top left corner of entire chart, including titles. 
        Coordinate _chart_origin;
        int _grid_size;
        int _min_x;
        int _max_x;
        int _min_y;
        int _max_y;

        // _x_axis_offset exists so houses do not lie on the y-axis. It is the number of 
        // _grid_sizes that x-axis will be offset to the left.
        // Example: If a house is at Coordinate (0,0) and that coordinate
        // corresponds to pixel (320,20), then the house will be
        // at pixel (320, 20). Now if _x_axis_offset is 3 and _grid_size is 2,
        // then the x-axis will start at pixel (314, 20) and the y_axis will lie
        // vertically at pixel 314. 
        // The house will be at (320, 20), which is not in the way of the y-axis.
        // Similar explanation for _y_axis_offset.
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

        // axes SDL_Rects and x-axis TextRects.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<TextRect> _x_texts = {};
        std::vector<SDL_Rect> _y_blocks = {};
        std::vector<TextRect> _y_texts = {};

        void addCityXAxis ();
        void addCityYAxis ();
        void addTitle();
        void addHouses(std::map<House*, Resident*> houseToResMap);
        std::map<Color, std::vector<Coordinate>> createVectorsForEachColor (
            std::map<House*, Resident*> houseToResMap
        );

};

#endif