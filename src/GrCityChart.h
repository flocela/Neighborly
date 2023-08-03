#ifndef GR_CITY_CHART_H
#define GR_CITY_CHART_H

#include <memory>
#include <vector>

#include "Coordinate.h"
#include "GrColorKey_Basic.h"
#include "House.h"
#include "Plot.h"
#include "Renderer.h"
#include "Resident.h"
#include "ResPerHouse.h"
#include "Title.h"

// Used to print out a city map using a renderer. Shows where each resident is 
// on the map. Each resident is assigned a color based on their group id and their
// happiness value.
// Includes title for this map.
// Includes printing the key to the map (color for each group id).
class GrCityChart
{
public:
    GrCityChart (
        std::unordered_map<const House*, Coordinate> coordPerHouse,
        std::unordered_map<int, BaseColor> resColors, //resident BaseColors per id group
        std::unique_ptr<Title> title,
        std::unique_ptr<GrColorKey_Basic> key,
        std::unique_ptr<Plot> plot,
        int topLeftCornerXPx,
        int topLeftCornerYPx,
        int xSpace, // space available for the chart in the x direction
        int ySpace  // space available for the chart in they y dirction
    );
    GrCityChart () = delete;
    GrCityChart (const GrCityChart& o) = default;
    GrCityChart (GrCityChart&& o) noexcept = default;
    GrCityChart& operator= (const GrCityChart& o) = default;
    GrCityChart& operator=(GrCityChart&& o) noexcept = default;
    ~GrCityChart () noexcept = default;

    void print (
        const ResPerHouse& houseToResMap,
        Renderer* renderer
    ) const;

    int sizeXPx() const;
    int sizeYPx() const;

    private:
    std::unordered_map<const House*, Coordinate> _coordinate_per_house;
    std::unordered_map<int, BaseColor> _resident_b_color_per_groupid;

    std::unique_ptr<Title> _title;
    std::unique_ptr<GrColorKey_Basic> _key;
    std::unique_ptr<Plot> _plot;

    int _top_left_corner_x__px;
    int _top_left_corner_y__px;
    int _x_space__px;
    int _y_space__px;

    // Points contain an x and y coordinate and a color.
    // _clearing_vector contains a Point for each house coordinate and each point is
    // assigned the absent color. This is used to clear the map before rendering the 
    // new set of Points with the new data from print().
    std::vector<Point> _clearing_vector;

    Color _absent_color = Color::gray850;

    // Each Point represents a house.
    // If a house is empty it gets a default color. If it is occupied, its color depends on the 
    // resident's group id and happiness value.
    std::vector<Point> createVectorOfPoints (const ResPerHouse& residentPerHouse) const;

    // Creates _clearing_vector.
    std::vector<Point> createVectorForClearingGrid ();
    
};

#endif