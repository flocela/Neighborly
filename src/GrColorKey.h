#ifndef GR_COLOR_KEY__H
#define GR_COLOR_KEY__H

#include "Renderer.h"

// Used to show the color of each group in a particular chart graphically using a renderer.
class GrColorKey
{

protected:

    GrColorKey () = default;
    GrColorKey (const GrColorKey& o) = default;
    GrColorKey (GrColorKey&& o) noexcept = default;
    GrColorKey& operator= (const GrColorKey& o) = default;
    GrColorKey& operator= (GrColorKey&& o) noexcept = default;

public:

    virtual ~GrColorKey () noexcept = default;

    virtual void print (Renderer* renderer) const = 0;
    virtual void setTopCenter (int xPx, int yPx) = 0;
    virtual int sizeXPx() const = 0;
    virtual int sizeYPx() const = 0;
};

#endif