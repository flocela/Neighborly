#ifndef GR_DVSTY_CHART_H
#define GR_DVSTY_CHART_H

#include "unordered_map"
#include "Color.h"
#include "Plot.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"
#include "GrColorKeyPrinter.h"
#include <memory>
#include "Title.h"

class GrDvstyChart {

public:
GrDvstyChart (
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods,
    std::unordered_map<const House*, std::set<const House*>> adjacentNeighbors,
    std::unique_ptr<Title> title,
    std::unique_ptr<ColorKey> colorKey,
    std::unique_ptr<Plot> plot,
    int topLeftXPx,
    int topLeftYPx,
    int xSpace,
    int ySpace
):  _colors{colors},
    _moods{moods},
    _adj_neighbors{adjacentNeighbors},
    _title{move(title)},
    _key{move(colorKey)},
    _plot{std::move(plot)}
{   
    _title->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx);
    _key->setTopCenter(topLeftXPx + xSpace/2, topLeftYPx + _title->sizeYPx());
    _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
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
std::unordered_map<const House*, std::set<const House*>> _adj_neighbors;
std::unique_ptr<Title> _title;
std::unique_ptr<ColorKey> _key;
std::unique_ptr<Plot> _plot;

std::set<const Resident*> getResidentsInHouses (
    std::set<const House*> houses,
    const std::unordered_map<const House*, const Resident*> residentPerHouse
);

};

#endif