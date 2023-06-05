#ifndef GR_HAP_CHART_H
#define GR_HAP_CHART_H

#include "unordered_map"
#include "Color.h"
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
    );

    GrHapChart () = delete;
    GrHapChart (const GrHapChart& o) = default;
    GrHapChart (GrHapChart&& o) noexcept = default;
    GrHapChart& operator= (const GrHapChart& o) = default;
    GrHapChart& operator=(GrHapChart&& o) noexcept = default;
    ~GrHapChart () = default;

    void print (
        std::unordered_map<int, int> numofResidentsPerGroup,
        std::unordered_map<int, double> happinessSumPerGroup,
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