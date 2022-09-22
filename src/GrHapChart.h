#ifndef GR_HAP_CHART_H
#define GR_HAP_CHART_H

#include "unordered_map"
#include "Color.h"
#include "PlotASizer.h"
#include "PlotA.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"
#include "GrColorKeyPrinter.h"

class GrHapChart {

public:
    GrHapChart (
        PlotASizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        int topLeftXPx,
        int topLeftYPx,
        std::string title,
        int numRuns,
        int minY,
        int maxY
    ):
    _plot{sizer, colors, moods, topLeftXPx, topLeftYPx, 0, numRuns, minY, maxY,100, 100}, // TODO it's not 100
    _colors{colors},
    _moods{moods},
    _key{
        topLeftXPx,
        topLeftYPx + sizer.titleLetter().getHeightIncLSpace(),
        sizer.keyLetter(),
        _colors,
        _moods
    }
    {
    (void) title;}

    // TODO this should be const Resident and const House
    void print (
        std::unordered_map<const Resident*, const House*> housePerResident, // TODO why can't I make this const
        int run,
        Renderer* renderer);

private:
    PlotA _plot;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    GrColorKeyPrinter _key;

    std::set<Resident*> getResidentsInTheseHouses (
        std::set<House*> houses,
        const std::unordered_map<House*, Resident*> residentPerHouse);

};

#endif