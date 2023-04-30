#ifndef COLOR_KEY_H
#define COLOR_KEY_H

#include "Renderer.h"

// Used to show the color of each group in a particular chart.
class ColorKey
{
protected:
    ColorKey () = default;
    ColorKey (const ColorKey& o) = default;
    ColorKey (ColorKey&& o) noexcept = default;
    ColorKey& operator= (const ColorKey& o) = default;
    ColorKey& operator= (ColorKey&& o) noexcept = default;

public:
    virtual ~ColorKey () = default;

    virtual void print (Renderer* renderer) = 0;
    virtual void setTopCenter (int xPx, int yPx) = 0;
    virtual int sizeXPx() = 0;
    virtual int sizeYPx() = 0;
};

#endif