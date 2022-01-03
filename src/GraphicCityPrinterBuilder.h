#ifndef GRAPHIC_CITY_PRINTER_BUILDER_H
#define GRAPHIC_CITY_PRINTER_BUILDER_H

#include "renderer.h"
#include "Coordinate.h"
#include "House.h"
#include "Color.h"
#include "GraphicCityPrinter.h"
#include <set>
#include <memory>

class GraphicCityPrinterBuilder
{
    public:
        // TODO add all constructors... destructor
        GraphicCityPrinterBuilder () = default;
        GraphicCityPrinterBuilder (const GraphicCityPrinterBuilder& o) = default;
        GraphicCityPrinterBuilder(GraphicCityPrinterBuilder&& o) noexcept = default;
        GraphicCityPrinterBuilder& operator= (const GraphicCityPrinterBuilder& o) = default;
        ~GraphicCityPrinterBuilder () = default;

        std::unique_ptr<GraphicCityPrinter> build();
        GraphicCityPrinterBuilder& addRenderer (Renderer* renderer);
        GraphicCityPrinterBuilder& addCoordinateToHouseMap 
        (
            std::map<Coordinate,House*> map
        );
        GraphicCityPrinterBuilder& addCrossHairsCoordinate (Coordinate coord);
        GraphicCityPrinterBuilder& addResidentColors (std::set<Color> resColors);
        GraphicCityPrinterBuilder& addCellSize (int cellSize);
        GraphicCityPrinterBuilder& addXAxisTickSpacing (int tickSpacing);
        GraphicCityPrinterBuilder& addYAxisTickSpacing (int tickSpacing);
        GraphicCityPrinterBuilder& addWidthOfTicksInPixels (int tickWidthPx);
        GraphicCityPrinterBuilder& addAxesWidthInPixels (int axesWidth);
        GraphicCityPrinterBuilder& addXAxisLabelSpacing (int labelSpacing);
        GraphicCityPrinterBuilder& addYAxisLabelSpacing (int labelSpacing);
        GraphicCityPrinterBuilder& addMinimumXValueForHouse (int minXHouse);
        GraphicCityPrinterBuilder& addMaximumXValueForHouse (int maxXHouse);
        GraphicCityPrinterBuilder& addMinimumYValueForHouse (int minYHouse);
        GraphicCityPrinterBuilder& addMaximumYValueForHouse (int maxYHouse);
        GraphicCityPrinterBuilder& addXAxisOffsetInPixels (int xAxisOffset);
        GraphicCityPrinterBuilder& addYAxisOffsetInPixels (int yAxisOffset);
        GraphicCityPrinterBuilder& addXAxisOverrunInPixels (int xAxisOverrun);
        GraphicCityPrinterBuilder& addYAxisOverrunInPixels (int yAxisOverrun);
        GraphicCityPrinterBuilder& addFontSizeForTickLabels (int fontSize);
        GraphicCityPrinterBuilder& addFontSizeForKeyLabels (int fontSize);
        GraphicCityPrinterBuilder& addFontSizeForTitle (int fontSize);

        Coordinate getCrossHairsCoordinate () {return Coordinate{_cross_hairs_x, _cross_hairs_y};};
        std::set<Color> getResidentColors () {return _resident_colors;};
        int getCellSize () {return _cell_size;}
        int getXAxisTickSpacing () {return _tick_spacing_x;}
        int getYAxisTickSpacing () {return _tick_spacing_y;}
        int getWidthOfTicksInPixels () {return _tick_width_px;}
        int getAxesWidthInPixels () {return _axes_width_px;}
        int getXAxisLabelSpacing () {return _label_spacing_x;}
        int getYAxisLabelSpacing () {return _label_spacing_y;}
        int getMinimumXValueForHouse () {return _min_house_x;}
        int getMaximumXValueForHouse () {return _max_house_x;}
        int getMinimumYValueForHouse () {return _min_house_y;}
        int getMaximumYValueForHouse () {return _max_house_y;}
        int getXAxisOffsetInPixels () {return _x_axis_offset;}
        int getYAxisOffsetInPixels () {return _y_axis_offset;}
        int getXAxisOverrunInPixels () {return _x_axis_overrun;}
        int getYAxisOverrunInPixels () {return _y_axis_overrun;}
        int getFontSizeForTickLabels () {return _font_size_tick_labels;}
        int getFontSizeForKeyLabels () {return _font_size_key_labels;}
        int getFontSizeForTitle () {return _font_size_title;}

    private:
        Renderer* _renderer;
        std::map<Coordinate, House*> _coordinate_to_house_map;
        int _cross_hairs_x;
        int _cross_hairs_y;
        std::set<Color> _resident_colors;
        int _cell_size;
        int _tick_spacing_x;
        int _tick_spacing_y;
        int _tick_width_px;
        int _axes_width_px;
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