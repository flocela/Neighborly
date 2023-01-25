#ifndef GR_CITY_CHART_H
#define GR_CITY_CHART_H

#include "Renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include <memory>
#include "AxisFormat.h"
#include "Letter.h"
#include "GrColorKey.h"
#include "Title.h"
#include "Plot.h"

// Used to print out a city map using a renderer.
class GrCityChart
{
public:
GrCityChart (
    std::unordered_map<const House*, Coordinate> coordPerHouse,
    std::unordered_map<int, BaseColor> resColors,
    std::unique_ptr<Title> title,
    std::unique_ptr<GrColorKey> key,
    std::unique_ptr<Plot> plot,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpace, // space available for the chart in the x direction
    int ySpace  // space available for the chart in they y dirction
);

void print (
    const std::unordered_map<const House*, const Resident*>& houseToResMap,
    Renderer* renderer
);

int sizeXPx();
int sizeYPx();

private:
std::unordered_map<const House*, Coordinate> _coordinate_per_house;
std::unordered_map<int, BaseColor> _resident_b_color_per_groupid;

std::unique_ptr<Title> _title;
std::unique_ptr<GrColorKey> _key;
std::unique_ptr<Plot> _plot;

// all house colors are set to absent.
// used as a way to clear the grid before new residents are colored in.
std::vector<Point> _clearing_vector;

int _top_left_corner_x__px;
int _top_left_corner_y__px;
int _x_space__px;
int _y_space__px;

// each point represents a house.
// if a house is empty it gets a default color. if it is occupied, its color depends on the 
//   resident's group id.
std::vector<Point> createVectorOfPoints (
    std::unordered_map<const House*, const Resident*> residentPerHouse
);

// there will be only one color, the default color for an empty house.
// all addresses will be represented as being empty.
std::vector<Point> createVectorForClearingGrid ();
    
};

#endif