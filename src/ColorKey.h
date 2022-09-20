#ifndef COLOR_KEY_H
#define COLOR_KEY_H

#include "renderer.h"

class ColorKey
{

public:
    virtual void print (Renderer* renderer) = 0;
    virtual int getHeightPx () = 0; // TODO getHeight should be part of Sizer's api
    virtual void setTopLeftCorner (int xPx, int yPx) = 0;
};

#endif