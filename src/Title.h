#ifndef TITLE_H
#define TITLE_H

#include "Renderer.h"

// A title prints the title string in the window.
class Title
{
protected:
    Title () = default;
    Title (const Title& o) = default;
    Title (Title&& o) noexcept = default;
    Title& operator= (const Title& o) = default;
    Title& operator= (Title&& o) noexcept = default;

public:
    virtual ~Title () noexcept = default;
    
    virtual int getLetterHeight () const = 0;

    virtual int getLineSpace () const = 0;

    virtual void print (Renderer* render) const = 0;

    // the size of the block of text in the x direction
    virtual int sizeXPx() const = 0;

    // the size of the block of text in the y direction
    virtual int sizeYPx() const = 0;

    virtual void setLetterHeight (int height) = 0;

    virtual void setLineSpace (int height) = 0;

    virtual void setTextColor (std::vector<uint8_t> color) = 0;

    virtual void setTitle (std::string title) = 0;

    virtual void setTextBackgroundColor (std::vector<uint8_t> color)  = 0;

    // the title is a block of text. the top center will have these coordinates
    virtual void setTopCenter (int xPx, int yPx) = 0;
    
};

#endif