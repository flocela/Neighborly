#ifndef TITLE_H
#define TITLE_H

#include "Renderer.h"

// Abstract class for a title. 
class Title
{
public:
    virtual void print (Renderer* render) const = 0;

    // the title is a block of text. the top center will have these coordinates
    virtual void setTopCenter (int xPx, int yPx) = 0;

    // the size of the block of text in the x direction
    virtual int sizeXPx() = 0;

    // the size of the block of text in the y direction
    virtual int sizeYPx() = 0;
    
};

#endif