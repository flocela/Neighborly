#ifndef TITLE_H
#define TITLE_H

#include "Sizer.h"
#include "renderer.h"

class Title : public Sizer
{

public:
    virtual void print (Renderer* render) = 0;
    virtual void setTopCenter (int xPx, int yPx) = 0;

};

#endif