#ifndef TITLE_H
#define TITLE_H

#include "Renderer.h"

// Abstract class for a title. 
class Title
{
public:

    virtual int getLetterHeight () = 0;

    virtual int getLineSpace () = 0;

    virtual void print (Renderer* render) const = 0;

    // the size of the block of text in the x direction
    virtual int sizeXPx() = 0;

    // the size of the block of text in the y direction
    virtual int sizeYPx() = 0;

    virtual void setLetterHeight (int height) = 0;

    virtual void setLineSpace (int height) = 0;

    virtual void setTextColor (SDL_Color color) = 0;

    virtual void setTitle (std::string title) = 0;

    virtual void setTextBackgroundColor (SDL_Color color)  = 0;

    // the title is a block of text. the top center will have these coordinates
    virtual void setTopCenter (int xPx, int yPx) = 0;
    
};

#endif