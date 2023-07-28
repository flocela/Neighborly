#ifndef GR_COLOR_KEY_H
#define GR_COLOR_KEY_H

#include <vector>

#include "ColorKey.h"
#include "Letter.h"
#include "Renderer.h"

// Renders a key (labels corresponding to colors) for a chart.
class GrColorKey : public ColorKey
{

public:
    // A label is made for each group id and mood combination.
    // So for two groups with two moods (happy and unhappy), there will be 4 labels:
    // group1 happy, group 1 unhappy, group 2 happy, group2 unhappy.
    GrColorKey (
        // topCenter is the point at the top and center of the GrColorKey.
        int topCenterXPx, // x value of the top most center point
        int topCenterYPx, // y value of the top most center point
        Letter labelLetter, // gives the size of the lettering.
        const std::unordered_map<int, BaseColor>& colors, // base color per groupId
        std::set<Mood> moods, // keys for colors, e.g. happy, sad, neutral
        std::vector<uint8_t> textColor,
        std::vector<uint8_t> textBackgroundColor
    );

    // Sets the top center point of the key at (0, 0).
    // Uses default colors for text and background color from _the_color_rgba (See Color.h).
    GrColorKey (
        Letter labelLetter,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods
    );

    GrColorKey () = delete;
    GrColorKey (const GrColorKey& o) = default;
    GrColorKey (GrColorKey&& o) noexcept = default;
    GrColorKey& operator= (const GrColorKey& o) = default;
    GrColorKey& operator=(GrColorKey&& o) noexcept = default;
    ~GrColorKey () noexcept = default;

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
    int _box_spacer__px = 6; // space between box and label
    int _column_border__px = 8; // space around each pair of box and label.

    // Each label holds the group id and mood, for example "Group 1 happy".
    // Each pair in the _label_per_color is the color and its corresponding label.
    // The size of _label_per_color is the number of group id's times the number of moods.
    // The number of group ids is the size of _b_color_per_groupId.
    // The number of moods is the size of _moods.
    std::vector<std::pair<Color, std::string>> _label_per_color;

    // column_width is the box length + box spacer + longest label + column border * 2.
    int _column_width;

    std::vector<uint8_t> _text_color = _the_color_rgba[Color::text];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::text_background];

    void setAttributes ();
};

#endif