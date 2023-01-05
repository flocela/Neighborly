#ifndef GR_CITY_CHART_H
#define GR_CITY_CHART_H

#include "renderer.h"
#include "Coordinate.h"
#include "TextRect.h"
#include "Resident.h"
#include <vector>
#include "House.h"
#include <memory>
#include "PixelConverter.h"
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
    int xSpace,
    int ySpace
);

void print (
    std::unordered_map<const House*, const Resident*> houseToResMap,
    Renderer* renderer
);

int sizeXPx();
int sizeYPx();

private:
std::unordered_map<const House*, Coordinate> _coordinate_per_house;
std::unordered_map<int, BaseColor> _res_colors;

std::unique_ptr<Title> _title;
std::unique_ptr<GrColorKey> _key;
std::unique_ptr<Plot> _plot;

int _top_left_corner_x__px;
int _top_left_corner_y__px;
int _x_space__px;
int _y_space__px;

std::unordered_map<Color, std::vector<Point>> createVectorsOfHousesForEachColor (
    std::unordered_map<const House*, const Resident*> residentPerHouse
);

std::unordered_map<Color, std::vector<Point>> createVectorsForClearingPlot ();
    
};

#endif