#ifndef GR_CITY_PRINTER_H
#define GR_CITY_PRINTER_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include "XAxisL2R.h"
#include "YAxisT2B.h"
#include <memory>
#include "PixelConverter.h"
#include "AxisFormat.h"
#include "Letter.h"
#include "GrCityPrinterSizer.h"

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
class GrCityPrinter
{
    public:
        GrCityPrinter (
            GrCityPrinterSizer grCityPrinterSizer,
            Renderer* renderer,
            std::map<Coordinate, House*> coordToHouseMap,
            std::map<int, std::pair<Color, Color>> resColors,
            int topLeftCornerXPx,
            int topLeftCornerYPx
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
        // This includes sad resident colors and happy resident colors.
        std::map<int, std::pair<Color, Color>> _res_colors;

        int _top_left_corner_x__px;
        int _top_left_corner_y__px;
        int _x_given_space__px;
        int _y_given_space__px;

        // cell_size * offsetMultiplier is length from crosshairs to center of first cell.
        int _offset_multiplier = 2; 
        int _overrun_multiplier = _offset_multiplier;

        // The coordinate where x and y axes cross on the screen in pixels.
        int _cross_hairs_x__px;
        int _cross_hairs_y__px;

        AxisFormat _axis_format_X;
        AxisFormat _axis_format_Y;
        Letter _title_letter;

        int _title_x__px;
        int _title_y__px;

        // Does not include any text, just the axis. 
        int _x_axis_length__px;

        // _cell_size is the spacing between ticks on the x and y axes.
        // It is determined as the size of the house plus the surrounding border
        // around the house in pixels.
        int _cell_size__px = 0;

        // _house_size__px is derived from _cell_size__px. _house_size__px is the
        // colored part of the cell in pixels. It does not include the border.
        int _house_size__px;

        // tick spacing on axes.
        int _min_tick_spacing_x;
        int _min_tick_spacing_y;
        int _maj_tick_spacing_x;
        int _maj_tick_spacing_y;

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

        // Axes
        std::unique_ptr<XAxisL2R> _x_axis_utility;
        std::unique_ptr<YAxisT2B> _y_axis_utility;

        // _x_blocks and _y_blocks hold the axes lines and the ticks on the lines.
        std::vector<SDL_Rect> _x_blocks = {};
        std::vector<SDL_Rect> _y_blocks = {};

        // _x_blocks and _y_blocks hold the numerical labels on the axis ticks.
        std::vector<TextRect> _x_texts = {};
        std::vector<TextRect> _y_texts = {};

        bool _chart_base_printed = false;

        int count = 0;

        std::unique_ptr<PixelConverter> _pixel_converter_x;
        std::unique_ptr<PixelConverter> _pixel_converter_y;

        void addCityXAxis ();
        void addCityYAxis ();
        void printHouses (std::map<House*, Resident*> houseToResMap);
        std::map<Color, std::vector<Coordinate>> createVectorsOfHousesForEachColor (
            std::map<House*, Resident*> houseToResMap
        );

        Color getHappyColor (int resGroup);
        Color getUnhappyColor (int resGroup);

        int majTickSpacing (int axisLength__coord);
        int minTickSpacing (int axisLength__coord);

        int labelSpacing (int axisLength);

        int calcYCrossHairsPx();
        int calcCellSizePx();
        int calcHouseSizePx();
        int calcXAxisLengthPx();
        int calcYAxisLengthPx();
        std::unique_ptr<PixelConverter> createPixelConverterX();
        std::unique_ptr<PixelConverter> createPixelConverterY();

        void printTitle();
        void printXAxis();
        void printYAxis();
        

};

#endif