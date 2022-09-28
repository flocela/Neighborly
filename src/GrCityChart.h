#ifndef GR_CITY_CHART_H
#define GR_CITY_CHART_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include "XAxisL2RTop.h"
#include "YAxisT2B.h"
#include <memory>
#include "PixelConverter.h"
#include "AxisFormat.h"
#include "Letter.h"
#include "GrCityChartSizer.h"
#include "GrColorKeyPrinter.h"
#include "Title.h"
#include "Plot.h"
#include "Chart.h"

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
class GrCityChart
{
    public:
        GrCityChart (
            std::unordered_map<const House*, Coordinate> coordToHouseMap,
            std::unordered_map<int, BaseColor> resColors,
            std::unique_ptr<Title> title,
            std::unique_ptr<GrColorKeyPrinter> key,
            std::unique_ptr<Plot> plot,
            int topLeftCornerXPx,
            int topLeftCornerYPx,
            int xSpace,
            int ySpace
        );

        void print (
            std::unordered_map<const House*, const Resident*> houseToResMap,
            Renderer* renderer
        );
    
    // __px suffix means the variable is in pixels which correspond to the screen.
    // __cl suffix means the variable is using the map's coordinate system.
    // house1 may be at (1, 1). house2 may be at (2, 1). Those use the map's
    // coordinate system and the units are cells. The house locations may be at
    // (10, 10) and (20, 10) on the screen. That would be using the screen
    // coordinate system in pixels.
    private:
        std::unordered_map<const House*, Coordinate> _coord_to_house_map;
        // This includes sad resident colors and happy resident colors.
        std::unordered_map<int, BaseColor> _res_colors;

        std::unique_ptr<Title> _title;
        std::unique_ptr<GrColorKeyPrinter> _key;
        std::unique_ptr<Plot> _plot;
       
        int _top_left_corner_x__px;
        int _top_left_corner_y__px;
        int _x_space__px;
        int _y_space__px;

        AxisFormat _axis_format_X;
        AxisFormat _axis_format_Y;

        // _house_size__px is derived from _cell_size__px. _house_size__px is the
        // colored part of the cell in pixels. It does not include the border.
        int _house_size__px;

        bool _chart_base_printed = false;

        int count = 0;

        std::unordered_map<Color, std::vector<Point>> createVectorsOfHousesForEachColor (
            std::unordered_map<const House*, const Resident*> houseToResMap
        );
        
};

#endif