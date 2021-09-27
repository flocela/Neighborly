#ifndef GRAPHIC_CITY_PRINTER_BUILDER_H
#define GRAPHIC_CITY_PRINTER_BUILDER_H

#include "renderer.h"
#include "Coordinate.h"
#include "House.h"
#include "Color.h"
#include <set>

class GraphicCityPrinterBuilder
{
    public:
        // TODO add all constructors... destructor

        GraphicCityPrinterBuilder addRenderer (Renderer* renderer);
        GraphicCityPrinterBuilder addCoordinateToHouseMap (
            std::map<Coordinate,House*> map
        );
        GraphicCityPrinterBuilder addCrossHairsCoordinate (Coordinate coord);
        GraphicCityPrinterBuilder addResidentColors (std::set<Color> resColors);
        GraphicCityPrinterBuilder addCellSize (int cellSize);
        GraphicCityPrinterBuilder addXAxisTickSpacing (int tickSpacing);
        GraphicCityPrinterBuilder addYAxisTickSpacing (int tickSpacing);
        GraphicCityPrinterBuilder addAxesWidthInPixels (int axesWidth);
        GraphicCityPrinterBuilder addXAxisLabelSpacing (int labelSpacing);
        GraphicCityPrinterBuilder addYAxisLabelSpacing (int labelSpacing);
        GraphicCityPrinterBuilder addMinimumXValueForHouse (int minXHouse);
        GraphicCityPrinterBuilder addMaximumXValueForHouse (int maxXHouse);
        GraphicCityPrinterBuilder addMinimumYValueForHouse (int minYHouse);
        GraphicCityPrinterBuilder addMaximumYValueForHouse (int maxYHouse);
        GraphicCityPrinterBuilder addXAxisOffsetInPixels (int xAxisOffset);
        GraphicCityPrinterBuilder addYAxisOffsetInPixels (int yAxisOffset);
        GraphicCityPrinterBuilder addXAxisOverrunInPixels (int xAxisOverrun);
        GraphicCityPrinterBuilder addYAxisOverrunInPixels (int yAxisOverrun);
        GraphicCityPrinterBuilder addFontSizeForTickLabels (int fontSize);
        GraphicCityPrinterBuilder addFontSizeForKeyLabels (int fontSize);
        GraphicCityPrinterBuilder addFontSizeForTitle (int fontSize);

    private:
        Renderer* _renderer;
        std::map<Coordinate, House*> _coordinate_to_house_map;
        int _cross_hairs_x;
        int _cross_hairs_y;
        std::set<Color> _resident_colors;
        int _cell_size;
        int _tick_spacing_x;
        int _tick_spacing_y;
        int _axes_width__px;
        int _label_spacing_x;
        int _label_spacing_y;
        int _min_house_x;
        int _max_house_x;
        int _min_house_y;
        int _max_house_y;
        int _x_axis_offset;
        int _y_axis_offset;
        int _x_axis_overrun;
        int _y_axis_overrun;
        int _font_size_tick_labels;
        int _font_size_key_labels;
        int _font_size_title;
};

#endif