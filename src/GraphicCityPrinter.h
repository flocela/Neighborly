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
            int minX, // minimum x value for a house. (most west house)
            int maxX, // maximum x value for a house. (most east house)
            int minY, // minimum y value for a house. (most north house)
            int maxY, // maximum y value for a house. (most south house) 
            // space between y-axis and most west house in pixels.
            int xAxisOffset,
            // space between x-axis and most west house in pixels.
            int yAxisOffset,
            // extra length of x-axis after most west house in pixels.
            int xAxisOverrun,
            // extra length of y-axis after most west house in pixels.
            int yAxisOverrun,
            // space for titles to the left of y-axis in pixels.
            int titlesAtLeftOffset,
            // space for titles above the y-axis in pixels.
            int titlesAtTopOffset,
            int fontSize
        );

        void printCity (std::map<House*, Resident*> houseToResMap);
    
    // __px suffix means the variable is in pixels which correspond to the screen.
    // __cl suffix means the variable is using the map's coordinate system.
    // house1 may be at (1, 1). house2 may be at (2, 1). Those use the map's
    // coordinate system and the units are cells. The house locations may be at
    // (10, 10) and (20, 10) on the screen. That would be using the screen
    // coordinate system in pixels.
    private:
        Renderer* _renderer;
        std::map<Coordinate, House*> _coord_to_house_map;
        std::map<Color, std::vector<int>> _rgba_per_color;

        // chartOrigin is top left coordinate of entire chart, including titles.
        // It is a location on the screen in pixels.
        Coordinate _chart_origin__px;

        // _cell_size is the spacing between ticks on the x and y axes.
        // It is determined as the size of the house plus the surrounding border
        // around the house in pixels.
        int _cell_size__px;

        // _house_size__px is derived from _cell_size__px. _house_size__px is the
        // colored part of the cell in pixels. It does not include the border.
        int _house_size__px;

        // The coordinate where x and y axes cross on the screen in pixels.
        int _cross_hairs_x__px;
        int _cross_hairs_y__px;

        // minimum x value for a house using map coordinates. (most west house)
        int _house_min_x__cl;
        // maximum x value for a house using map coordinates. (most east house)
        int _house_max_x__cl;
        // minimum y value for a house using map coordinates. (most north house)
        int _house_min_y__cl;
        // maximum y value for a house using map coordinates. (most south house) 
        int _house_max_y__cl;

        // These are taken at the center of the house.
        // minimum x value for a house in pixels. (most west house)
        int _house_min_x__px;
        // maximum x value for a house in pixels. (most east house)
        int _house_max_x__px;
        // minimum y value for a house in pixels. (most north house)
        int _house_min_y__px;
        // maximum y value for a house in pixels. (most south house)
        int _house_max_y__px;

        // _x_axis_offset__pixel exists so houses do not lie on the y-axis.
        // Instead of the chart's min x value being _house_min_x__px (the
        // coordinates of the most west house), 
        int _x_axis_offset__px;
        int _y_axis_offset__px;

        // Overruns are how much farther the axis runs past the last house.
        // If the x-axis were to originally stop at the value _house_max_x__px, then
        // instead it will stop at the value _house_max_x__px + _x_axis_overrun__px
        int _x_axis_overrun__px;
        int _y_axis_overrun__px;

        // titlesAtTopOffset and titlesLeftOffset is room given for titles at top
        // and left of the graph.
        int _titles_at_left_offset__px;
        int _titles_at_top_offset__px;

        // The width of the ticks along the axes. Same for x and y axes.
        int _axis_tick_width__px = 2;

        // fontSize is for x and y axes.
        int _font_size;

        // _x_blocks and _y_blocks hold the axes lines and the ticks on the lines.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<SDL_Rect> _y_blocks = {};

        // _x_blocks and _y_blocks hold the numerical labels on the axis ticks.
        std::vector<TextRect> _x_texts = {};
        std::vector<TextRect> _y_texts = {};

        bool _chart_base_printed = false;

        void addCityXAxis ();
        void addCityYAxis ();
        void addTitle();
        void addHouses (std::map<House*, Resident*> houseToResMap);
        std::map<std::vector<int>, std::vector<Coordinate>> createVectorsForEachColor (
            std::map<House*, Resident*> houseToResMap
        );

        // Initialize the blocks and texts that are used by the renderer to render
        // the axes' lines, ticks, and labels
        void initXAxisBlocks ();
        void initYAxisBlocks ();

};

#endif