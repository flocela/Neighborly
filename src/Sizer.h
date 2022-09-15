#ifndef SIZER_H
#define SIZER_H
 
class Sizer
{

public:
    // returns its size in the x direction in units. The unit size is determined by the class.
    virtual int sizeX() = 0;

    // returns its size in the y direction in units. The unit size is determined by the class.
    virtual int sizeY() = 0;

};



#endif