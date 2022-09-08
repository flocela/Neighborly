#ifndef GR_DVSTY_CHART_H
#define GR_DVSTY_CHART_H

#include "unordered_map"
#include "Color.h"
#include "GrChartASizer.h"
#include "GrChartA.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"
#include "GrColorKeyPrinter.h"

class GrDvstyChart {

public:
GrDvstyChart (
    GrChartASizer sizer,
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods,
    int topLeftXPx,
    int topLeftYPx,
    std::string title,
    std::unordered_map<const House*, std::set<const House*>> neighbors

):
_chart{sizer, colors, moods, topLeftXPx, topLeftYPx, title},
_colors{colors},
_moods{moods},
_key{
    topLeftXPx,
    topLeftYPx + sizer.titleLetter().getHeightIncLSpace(),
    sizer.xSpacePx(),
    sizer.keyLetter(),
    _colors,
    _moods
},
_neighbors{neighbors}
{}

// TODO this should be const Resident and const House
void print (
    std::unordered_map<const Resident*, const House*> housePerResident, // TODO why can't I make this const
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer);

private:
    GrChartA _chart;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    GrColorKeyPrinter _key;
    std::unordered_map<const House*, std::set<const House*>> _neighbors;

    std::set<const Resident*> getResidentsInHouses (
        std::set<const House*> houses,
        const std::unordered_map<const House*, const Resident*> residentPerHouse);

};

#endif