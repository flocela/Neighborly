#ifndef COLOR_KEY_H
#define COLOR_KEY_H

#include "Renderer.h"

// Used to show the color of each group in a particular chart.
class ColorKey
{
    
public:
    virtual void print (Renderer* renderer) = 0;
    virtual void setTopCenter (int xPx, int yPx) = 0;
    virtual int sizeXPx() = 0;
    virtual int sizeYPx() = 0;
};

#endif