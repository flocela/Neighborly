#ifndef GR_DVSTY_PRINTER_H
#define GR_DVSTY_PRINTER_H

#include "unordered_map"
#include "Color.h"
#include "GrChartASizer.h"
#include "GrChartA.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"

class GrDvstyPrinter {

public:
    GrDvstyPrinter (
        GrChartASizer sizer,
        std::unordered_map<int, Color> colors,
        std::set<std::string> moods,
        int topLeftXPx,
        int topLeftYPx,
        std::string title
    ):
    _chart{sizer, colors, moods, topLeftXPx, topLeftYPx, title},
    _colors{colors},
    _moods{moods}
    {}

    // TODO this should be const Resident and const House
    void print (
        City* city, // TODO why can't I make this const
        std::unordered_map<Resident*, House*> housePerResident, // TODO why can't I make this const
        std::unordered_map<House*, Resident*> residentPerHouse,
        int run,
        Renderer* renderer);

private:
    GrChartA _chart;
    std::unordered_map<int, Color> _colors;
    std::set<std::string> _moods;

    std::set<Resident*> getResidentsInTheseHouses (
        std::set<House*> houses,
        const std::unordered_map<House*, Resident*> residentPerHouse);

};

#endif