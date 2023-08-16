#ifndef GR_COLOR_KEY_BASIC_H
#define GR_COLOR_KEY_ASIC_H

#include <vector>

#include "GrColorKey.h"
#include "Letter.h"
#include "Renderer.h"

// Renders a key (colors corresponding to labels) for a chart.
class GrColorKey_Basic : public GrColorKey
{

public:
    // A label is made for each combination of group id and mood.
    // So for two groups with two moods (happy and unhappy), there will be 4 labels:
    // group1 happy, group 1 unhappy, group 2 happy, group2 unhappy.
    GrColorKey_Basic (
        // topCenter is the point at the top and center of the GrColorKey.
        int topCenterXPx, // x value of the top most center point
        int topCenterYPx, // y value of the top most center point
        Letter labelLetter, // gives the font size of the lettering.
        const std::unordered_map<int, BaseColor>& colors, // base color per groupId
        std::set<Mood> moods, // keys for colors, e.g. happy, sad, neutral
        std::vector<uint8_t> textColor,
        std::vector<uint8_t> textBackgroundColor
    );

    // Sets the top center point of the key at (0, 0).
    GrColorKey_Basic (
        Letter labelLetter,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods
    );

    GrColorKey_Basic () = delete;
    GrColorKey_Basic (const GrColorKey_Basic& o) = default;
    GrColorKey_Basic (GrColorKey_Basic&& o) noexcept = default;
    GrColorKey_Basic& operator= (const GrColorKey_Basic& o) = default;
    GrColorKey_Basic& operator=(GrColorKey_Basic&& o) noexcept = default;
    ~GrColorKey_Basic () noexcept = default;

    void print (Renderer* renderer) const;
    int sizeXPx () const override;
    int sizeYPx () const override;

    void setTextBackgroundColor (std::vector<uint8_t> color);
    void setTextColor (std::vector<uint8_t> color);
    void setTopCenter (int xPx, int yPy);

private:
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    Letter _label_letter;
    const std::unordered_map<int, BaseColor>& _b_color_per_groupId;
    std::set<Mood> _moods;
    int _box_length__px = 0; // box is the colored square next to the label
    int _box_spacer__px = 6; // space between colored box and label
    int _column_border__px = 8; // space around each pair of colored box and label

    // Each label holds the group id and mood, for example "Group 1 happy".
    // Each pair in the _label_per_color is the color and its corresponding label.
    // The size of _label_per_color is the number of group id's times the number of moods.
    // The number of group ids is the size of _b_color_per_groupId.
    // The number of moods is the size of _moods.
    std::vector<std::pair<Color, std::string>> _label_per_color;

    // column_width is the box width + box spacer + longest label + column border * 2.
    int _column_width;

    std::vector<uint8_t> _text_color = _the_color_rgba[Color::gray100];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::gray900];

    void setAttributes ();
};

#endif