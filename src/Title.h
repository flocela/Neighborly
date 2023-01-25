#ifndef TITLE_H
#define TITLE_H

#include "Renderer.h"

class Title
{

public:
    virtual void print (Renderer* render) const = 0;
    virtual void setTopCenter (int xPx, int yPx) = 0;
    virtual int sizeXPx() = 0;
    virtual int sizeYPx() = 0;
    
};

#endif