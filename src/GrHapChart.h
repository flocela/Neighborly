#ifndef GR_HAP_CHART_H
#define GR_HAP_CHART_H

#include "unordered_map"
#include "Color.h"
#include "PlotSizer.h"
#include "Plot.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"
#include "ColorKey.h"
#include "Title.h"

class GrHapChart {

public:
    GrHapChart (
        PlotSizer sizer,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        std::unique_ptr<Title> title,
        std::unique_ptr<ColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
    ):
    _colors{colors},
    _moods{moods},
    _title{move(title)},
    _key{move(colorKey)},
    _plot{std::move(plot)}
    {   (void) sizer;
        _title->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx);
        _key->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx + _title->sizeYPx());
        _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
        _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
    }

    // TODO this should be const Resident and const House
    void print (
        std::unordered_map<const Resident*, const House*> housePerResident, // TODO why can't I make this const
        int run,
        Renderer* renderer);

private:
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    std::unique_ptr<Title> _title;
    std::unique_ptr<ColorKey> _key;
    std::unique_ptr<Plot> _plot;

    std::set<Resident*> getResidentsInTheseHouses (
        std::set<House*> houses,
        const std::unordered_map<House*, Resident*> residentPerHouse);

};

#endif