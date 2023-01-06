#ifndef GR_COLOR_KEY_H
#define GR_COLOR_KEY_H

#include "renderer.h"
#include "Letter.h"
#include "ColorKey.h"
#include "SDL.h"
#include <utility>
#include <vector>
#include <algorithm>

class GrColorKey : public ColorKey
{

public:
GrColorKey() = delete;
GrColorKey (
    // the point at the top and center of the GrColorKey. the top most, central most point.
    int topCenterXPx, // x value of the top most center point.
    int topCenterYPx, // y value of the top most center point.
    Letter labelLetter, // each groupId will be labeled. this gives the size of the lettering
    std::unordered_map<int, BaseColor> colors, // base color per groupId
    std::set<Mood> moods, // keys for colors, e.g. happy, sad, neutral
    SDL_Color textColor,
    SDL_Color textBackgroundColor
);

GrColorKey (
    Letter labelLetter,
    std::unordered_map<int, BaseColor> colors,
    std::set<Mood> moods
);

void print (Renderer* renderer);
void setTopCenter (int xPx, int yPy);
void setTextColor (SDL_Color color);
void setTextBackgroundColor (SDL_Color color);
int sizeXPx () override;
int sizeYPx () override;
    
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

void setAttributes ();

SDL_Color _text_color = {100, 100, 100, 100};
SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};

};

#endif