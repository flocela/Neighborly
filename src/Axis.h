#ifndef AXIS_H
#define AXIS_H

#include <utility>

// Represents an axis. Used to get the pixels designating values on the axis.
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

    // Returns the low value that must be labeled on the axis.
    virtual int getLowVal () const = 0;

    // Returns the high value that must be labeled on the axis.
    virtual int getHighVal () const = 0;

    virtual int getPixelsPerUnit () const = 0;

    virtual int getTickThickness__px () const = 0;

    // There is a space between the start of the axis and the low value. That space is the
    // start offset times the pixels per unit.
    virtual int getStartOffset () const = 0;

    // There is a space between the high value and the end of the axis.
    // That space is the end offset times the pixels per unit. The max value is the
    // value given by getMaxVal().
    virtual int getEndOffset () const = 0;

    // Returns pixel smallest pixel (closest to zero) on the axis.
    virtual int getStartPixel () const = 0;

    // Returns the largest pixel (farthest from zero) on the axis.
    virtual int getEndPixel () const = 0;

    // Returns the pixels covered by a dot at the value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    virtual std::pair<int, int> getPixels (double val, int dotSize) const = 0;


    // Returns the central pixel between the low and high values. The low and high values are given
    // by getLowVal() and getHighVal().
    virtual int getCenterValPx () const = 0;

    virtual void moveCrossPixel (int pixel) = 0;
    virtual void setPxPerUnit (int pixels) = 0;
    virtual void setDirectionOfAxis (bool forward) = 0;
};

#endif