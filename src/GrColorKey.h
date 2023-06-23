#ifndef GR_COLOR_KEY_H
#define GR_COLOR_KEY_H

#include "Renderer.h"
#include "Letter.h"
#include "ColorKey.h"
#include "SDL.h"
#include <utility>
#include <vector>
#include <algorithm>

class GrColorKey : public ColorKey
{

public:
    GrColorKey (
        // the point at the top and center of the GrColorKey. the top most, central most point.
        int topCenterXPx, // x value of the top most center point.
        int topCenterYPx, // y value of the top most center point.
        Letter labelLetter, // each groupId will be labeled. this gives the size of the lettering
        std::unordered_map<int, BaseColor> colors, // base color per groupId
        std::set<Mood> moods, // keys for colors, e.g. happy, sad, neutral
        std::vector<uint8_t> textColor,
        std::vector<uint8_t> textBackgroundColor
    );

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
    int sizeXPx () override;
    int sizeYPx () override;

    void setTextBackgroundColor (std::vector<uint8_t> color);
    void setTextColor (std::vector<uint8_t> color);
    void setTopCenter (int xPx, int yPy);

private:
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    Letter _label_letter;
    std::unordered_map<int, BaseColor> _b_color_per_groupId;
    std::set<Mood> _moods;
    int _box_length__px = 0; // box is the colored square
    int _box_spacer__px = 6;
    int _column_border__px = 8;
    std::vector<std::pair<Color, std::string>> _label_per_color;
    int _column_width;

    std::vector<uint8_t> _text_color = _the_color_rgba[Color::text];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::text_background];

    void setAttributes ();
};

#endif