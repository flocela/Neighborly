#ifndef AXIS_H
#define AXIS_H

#include <utility>

class Axis
{

protected:
    Axis () = default;
    Axis (const Axis& o) = default;
    Axis (Axis&& o) noexcept = default;
    Axis& operator= (const Axis& o) = default;
    Axis& operator= (Axis&& o) noexcept = default;

public:
    
    virtual ~Axis () noexcept = default;

    virtual int getAxisLengthPx () const = 0;

    // Returns the min val given in the constructor.
    virtual int getMinVal () const = 0;

    // Returns the max val given in the constructor.
    virtual int getMaxVal () const = 0;

    // Returns the difference between the min and max values given in the constructor.
    virtual int getDiff () const = 0;

    virtual int getPixelsPerUnit () const = 0;

    virtual int getTickThichness__px () const = 0;

    // There is a space between the start of the axis and the first min value given in the
    // constructor. That space is the start offset multiplier times the pixels per unit.
    virtual int getStartOffsetMultiplier () const = 0;

    // There is a space between the max value given in the constructor and the end of the axis.
    // That space is the end offset multiplier times the pixels per unit.
    virtual int getEndOffsetMultiplier () const = 0;

    // Returns pixel smallest pixel on the axis.
    virtual int getStartPixel () const = 0;

    // Returns the largest pixel on the axis.
    virtual int getEndPixel () const = 0;

    // Returns the pixels covered by a dot at the value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    virtual std::pair<int, int> getPixels (double val, int dotSize) const = 0;


    // Returns the central pixel between the min and max values given in the constructor.
    virtual int getCenterValPx () const = 0;

    virtual void moveCrossPixel (int pixel) = 0;
    virtual void setPxPerUnit (int pixels) = 0;
    virtual void setTickThickness (int tickThicknessPx) = 0;
};

#endif