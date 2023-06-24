#ifndef GR_DVSTY_CHART_H
#define GR_DVSTY_CHART_H

#include <unordered_map>
#include "Color.h"
#include "Plot.h"
#include "Renderer.h"
#include "City.h"
#include "Resident.h"
#include "GrColorKey.h"
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
        std::unordered_map<const House*, std::unordered_set<const House*>> adjacentNeighbors,
        std::unique_ptr<Title> title,
        std::unique_ptr<ColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
    );

    GrDvstyChart () = delete;
    GrDvstyChart (const GrDvstyChart& o) = default;
    GrDvstyChart (GrDvstyChart&& o) noexcept = default;
    GrDvstyChart& operator= (const GrDvstyChart& o) = default;
    GrDvstyChart& operator=(GrDvstyChart&& o) noexcept = default;
    ~GrDvstyChart () noexcept = default;

    void print (
        std::unordered_map<int, int> numOfResidentsPerGroupId,
        std::unordered_map<int, int> numOfDiffNeighborsPerGroupId,
        int run,
        Renderer* renderer
    ) const;

    int sizeXPx() const;
    int sizeYPx() const;

private:

    std::unordered_map<int, BaseColor> _b_color_per_groupId;
    std::set<Mood> _moods;
    std::unordered_map<const House*, std::unordered_set<const House*>> _adj_neighbors;
    std::unique_ptr<Title> _title;
    std::unique_ptr<ColorKey> _key;
    std::unique_ptr<Plot> _plot;

    // used so that key is only prited once
    mutable bool _key_has_printed = false;

    // used so that title is only printed once.
    mutable bool _title_has_printed = false;

};

#endif