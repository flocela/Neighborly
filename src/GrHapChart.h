#ifndef GR_HAP_CHART_H
#define GR_HAP_CHART_H

#include <iostream>
#include <memory>

#include "Plot.h"
#include "Renderer.h"
#include "ColorKey.h"
#include "Title.h"

class GrHapChart {

// Used to print the average happiness per each group, per run number.
// This is found by adding the happiness value of each resident in the group and
// then dividing this sum by the number of residents in the group.
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
    ~GrHapChart () noexcept = default;

    void print (
        const std::unordered_map<int, int>& numofResidentsPerGroup,
        const std::unordered_map<int, double>& happinessSumPerGroup,
        int run,
        Renderer* renderer
    ) const;

    int sizeXPx() const;
    int sizeYPx() const;

private:

    std::unordered_map<int, BaseColor> _base_color_per_group_id;
    std::unique_ptr<Title> _title;
    std::unique_ptr<ColorKey> _key;
    std::unique_ptr<Plot> _plot;

    // used so that key is only prited once
    mutable bool _key_has_printed = false;

    // used so that title is only printed once.
    mutable bool _title_has_printed = false;

};

#endif