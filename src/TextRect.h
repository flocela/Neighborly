#ifndef TEXT_RECT_H
#define TEXT_RECT_H

#include <string>
#include "SDL.h"

// holds information for rendering text block
struct TextRect
{
    int _x_pixel; // top left corner x-pixel
    int _y_pixel; // top left corner y-pixel
    std::string _text;
    int _letter_height;
    double _width_multiplier;
    SDL_Color _text_color;
    SDL_Color _text_background_color;
    int _position; // used by renderer for final positioning of text block
};

#endif