#ifndef GR_HAP_CHART_H
#define GR_HAP_CHART_H

#include "unordered_map"
#include "Color.h"
#include "PlotSizer.h"
#include "Plot.h"
#include "Renderer.h"
#include "City.h"
#include "Resident.h"
#include "ColorKey.h"
#include "Title.h"

#include <iostream>

class GrHapChart {

public:

GrHapChart (
    std::unordered_map<int, BaseColor> colors,
    std::unique_ptr<Title> title,
    std::unique_ptr<ColorKey> colorKey,
    std::unique_ptr<Plot> plot,
    int topLeftXPx,
    int topLeftYPx,
    int xSpace,
    int ySpace
): _colors{colors},
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
    int run,
    Renderer* renderer
) const;

int sizeXPx();
int sizeYPx();

private:

std::unordered_map<int, BaseColor> _colors;
std::unique_ptr<Title> _title;
std::unique_ptr<ColorKey> _key;
std::unique_ptr<Plot> _plot;

};

#endif