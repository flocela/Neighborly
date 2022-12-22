#ifndef TEXT_RECT_H
#define TEXT_RECT_H

#include <string>
#include "SDL.h"

struct TextRect
{
    int _x_pixel;
    int _y_pixel;
    std::string _text;
    int _letter_height;
    double _width_multiplier;
    SDL_Color _text_color;
    SDL_Color _text_background_color;
    int _position;
};

#endif