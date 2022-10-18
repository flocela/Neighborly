#ifndef TEXT_RECT_H
#define TEXT_RECT_H

#include <string>
#include "SDL.h"

struct TextRect
{
    int xPixel;
    int yPixel;
    std::string text;
    int letterHeight;
    double widthMultiplier;
    int position;
};

#endif