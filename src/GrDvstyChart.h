#ifndef GR_DVSTY_CHART_H
#define GR_DVSTY_CHART_H

#include "unordered_map"
#include "Color.h"
#include "Plot.h"
#include "renderer.h"
#include "City.h"
#include "Resident.h"
#include "GrColorKey.h"
#include <memory>
#include "Title.h"

class GrDvstyChart {

public:

// Used to print the average diversity of each group, per the run number.
// diversity of one resident is the number of disparate neighbors.
// diversity per group is the the number of disparate neighbors
// divided by the number of residents in the group.
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
):  _b_color_per_groupId{colors},
    _moods{moods},
    _adj_neighbors{adjacentNeighbors},
    _title{move(title)},
    _key{move(colorKey)},
    _plot{std::move(plot)}
{   
    _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx);
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx + _title->sizeYPx());
}

void print (
    std::unordered_map<const Resident*, const House*> housePerResident,
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
) const;

int sizeXPx();
int sizeYPx();

private:

std::unordered_map<int, BaseColor> _b_color_per_groupId;
std::set<Mood> _moods;
std::unordered_map<const House*, std::set<const House*>> _adj_neighbors;
std::unique_ptr<Title> _title;
std::unique_ptr<ColorKey> _key;
std::unique_ptr<Plot> _plot;

// used so that key is only prited once
mutable bool _key_has_printed = false;

// used so that title is only printed once.
mutable bool _title_has_printed = false;

};

#endif