#ifndef GR_DVSTY_CHART_H
#define GR_DVSTY_CHART_H

#include <memory>
#include <unordered_map>

#include "GrColorKey.h"
#include "Plot.h"
#include "Renderer.h"
#include "Title.h"

// Used to print the average diversity of each group, per the run number.
// Diversity of one resident is the number of disparate neighborst they have.
// Diversity per group is adding the diversity of each resident in a group to come up with a total
// sum, then dividing that sum by the number of residents in the group.
class GrDvstyChart {

public:

    GrDvstyChart (
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
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
        const std::unordered_map<int, int>& numOfResidentsPerGroupId,
        const std::unordered_map<int, int>& numOfDiffNeighborsPerGroupId,
        int run,
        Renderer* renderer
    ) const;

    int sizeXPx() const;
    int sizeYPx() const;

private:

    std::unordered_map<int, BaseColor> _b_color_per_group_id;
    std::set<Mood> _moods;
    std::unique_ptr<Title> _title;
    std::unique_ptr<ColorKey> _key;
    std::unique_ptr<Plot> _plot;

    // used so that key is only prited once
    mutable bool _key_has_printed = false;

    // used so that title is only printed once.
    mutable bool _title_has_printed = false;

};

#endif