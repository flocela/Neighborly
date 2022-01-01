#ifndef GRAPHIC_CITY_PRINTER_H
#define GRAPHIC_CITY_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include "XAxisUtility.h"
#include "YDownAxisUtility.h"
#include <memory>
#include "PixelConverter.h"

// Takes in a Renderer* and necessary settings to draw the city chart.
// Remembers this initializing information so user can 
// easily print city houses using city coordinates.

// The x and y axes cross at the _chart_origin.
// The x axes length is
// (maxX - minX) * cellSize + xAxisOffset + xAxisOverrun.
// The y axes length is 
// (maxY - minY) * cellSize + yAxisOffset + yAxisOverrun.
// Allow 300 pixels to the left of x-axis for the axis labels and
// the chart's key.
// Allow 100 pixels above the y axis for the y-axis labels and the chart title.
class GraphicCityPrinter
{
    public:
        GraphicCityPrinter (
            Renderer* renderer,
            std::map<Coordinate, House*> coordToHouseMap,
            int crossHairsX,
            int crossHairsY,
            std::set<Color> resColors,
            int cellSize,
            int tickSpacingX,
            int tickSpacingY,
            int tickWidthPx,
            int axesWidthPx,
            int labelSpacingX,
            int labelSpacingY,
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
            int fontSizeTickLabels,
            int fontSizeKeyLabels,
            int fontSizeTitle
        );

        void printCity (std::map<House*, Resident*> houseToResMap);
    
    // __px suffix means the variable is in pixels which correspond to the screen.
    // __cl suffix means the variable is using the map's coordinate system.
    // house1 may be at (1, 1). house2 may be at (2, 1). Those use the map's
    // coordinate system and the units are cells. The house locations may be at
    // (10, 10) and (20, 10) on the screen. That would be using the screen
    // coordinate system in pixels.
    private:
        std::string _main_title = "City Map";
        Renderer* _renderer;
        std::map<Coordinate, House*> _coord_to_house_map;
        std::unique_ptr<PixelConverter> _pixel_converter_x;
        std::unique_ptr<PixelConverter> _pixel_converter_y;

        // The coordinate where x and y axes cross on the screen in pixels.
        int _cross_hairs_x__px;
        int _cross_hairs_y__px;

        // This includes sad resident colors and happy resident colors.
        std::set<Color> _res_colors;

        // _cell_size is the spacing between ticks on the x and y axes.
        // It is determined as the size of the house plus the surrounding border
        // around the house in pixels.
        int _cell_size__px;

        // _house_size__px is derived from _cell_size__px. _house_size__px is the
        // colored part of the cell in pixels. It does not include the border.
        int _house_size__px;

        

        // tick spacing on axes.
        int _tick_spacing_x;
        int _tick_spacing_y;

        // tick width in pixels.
        int _tick_width__px;

        // The width of the ticks along the axes. Same for x and y axes.
        int _axes_width__px;

        // label spacing on axes.
        int _label_spacing_x;
        int _label_spacing_y;

        // min x value for a house using map values not pixels. (most west house)
        int _house_min_x;
        // max x value for a house using map values not pixels. (most east house)
        int _house_max_x;
        // min y value for a house using map values not pixels. (most north house)
        int _house_min_y;
        // max y value for a house using map values not pixels. (most south house) 
        int _house_max_y;

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

        // TODO are these _house_min _max __px values used?
        // These are taken at the center of the house.
        // minimum x value for a house in pixels. (most west house)
        int _house_min_x__px;
        // maximum x value for a house in pixels. (most east house)
        int _house_max_x__px;
        // minimum y value for a house in pixels. (most north house)
        int _house_min_y__px;
        // maximum y value for a house in pixels. (most south house)
        int _house_max_y__px;

        // titlesAtTopOffset and titlesLeftOffset is room given for titles at top
        // and left of the graph.
        int _titles_at_left_offset__px = 290;
        int _titles_at_top_offset__px = 0;
        int _title_y__px = 0;
        int _dist_from_title_to_legend = 90;

        // fontSizes
        int _font_size_axes_tick_labels = 0;
        int _font_size_key = 0; 
        int _font_size_title = 0;
        

        // Axes
        std::unique_ptr<XAxisUtility> _x_axis_utility;
        std::unique_ptr<YDownAxisUtility> _y_axis_utility;

        // _x_blocks and _y_blocks hold the axes lines and the ticks on the lines.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<SDL_Rect> _y_blocks = {};

        // _x_blocks and _y_blocks hold the numerical labels on the axis ticks.
        std::vector<TextRect> _x_texts = {};
        std::vector<TextRect> _y_texts = {};

        bool _chart_base_printed = false;

        int count = 0;

        void addCityXAxis ();
        void addCityYAxis ();
        void addTitle();
        void printHouses (std::map<House*, Resident*> houseToResMap);
        std::map<Color, std::vector<Coordinate>> createVectorsForEachColor (
            std::map<House*, Resident*> houseToResMap
        );
        void printLegend ();

        // Initialize the blocks and texts that are used by the renderer to render
        // the axes' lines, ticks, and labels
        void initXAxisBlocks ();
        void initYAxisBlocks ();

};

#endif