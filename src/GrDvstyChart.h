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
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods,
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    GrColorKeyPrinter keyPrinter,
    GrChartA chartA,
    int topLeftXPx,
    int topLeftYPx
):  _colors{colors},
    _moods{moods},
    /*_key{
        topLeftXPx,
        topLeftYPx + sizer.titleLetter().getHeightIncLSpace(),
        sizer.xSpacePx(),
        sizer.keyLetter(),
        _colors,
        _moods
    },*/
    _neighbors{neighbors},
    _key{keyPrinter},
    _chart{chartA}
{
    _key.setTopLeftCorner(topLeftXPx, topLeftYPx);
    _chart.setTopLeft(topLeftXPx, topLeftYPx + _key.getHeightPx() );
}

// TODO this should be const Resident and const House
void print (
    std::unordered_map<const Resident*, const House*> housePerResident, // TODO why can't I make this const
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
);

private:


std::unordered_map<int, BaseColor> _colors;
std::set<Mood> _moods;
std::unordered_map<const House*, std::set<const House*>> _neighbors;
GrColorKeyPrinter _key;
GrChartA _chart;

std::set<const Resident*> getResidentsInHouses (
    std::set<const House*> houses,
    const std::unordered_map<const House*, const Resident*> residentPerHouse
);

};

#endif