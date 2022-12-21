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
    {   
        _title->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx);
        _key->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx + _title->sizeYPx());
        _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
        _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
    }

    void print (
        std::unordered_map<const Resident*, const House*> housePerResident,
        int run,
        Renderer* renderer
    );

    int sizeXPx();
    int sizeYPx();

private:

    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    std::unique_ptr<Title> _title;
    std::unique_ptr<ColorKey> _key;
    std::unique_ptr<Plot> _plot;

};

#endif