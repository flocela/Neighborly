#ifndef FORWARD_AXIS_H
#define FORWARD_AXIS_H

#include <utility>

class ForwardAxis
{
public:
    ForwardAxis (
        int crossPixel,
        int minVal,
        int maxVal,
        int pxPerUnit,
        int tickThickness,
        int startOffsetMultiplier,
        int endOffset
    );

    ForwardAxis () = delete;
    ForwardAxis (const ForwardAxis& o) = default;
    ForwardAxis (ForwardAxis&& o) noexcept = default;
    ForwardAxis& operator= (const ForwardAxis& o) = default;
    ForwardAxis& operator= (ForwardAxis&& o) noexcept = default;
    ~ForwardAxis () noexcept = default;

    int getAxisLengthPx () const;

    // Returns the pixel where the cross axis crosses this axis.
    int getCrossPx__px () const;

    // Returns the central pixel between the min and max values given in the constructor.
    int getCenterValPx () const;

    int getMinVal () const;
    int getMaxVal () const;

    // Returns the difference between the min and max values given in the constructor.
    int getDiff () const;

    int getPixelsPerUnit () const;
    int getTickThichness__px () const;

    // There is a space between the start of the axis and the first min value given in the
    // constructor. That space is the start offset multiplier times the pixels per unit.
    int getStartOffsetMultiplier () const;

    // There is a space between the max value given in the constructor and the end of the axis.
    // That space is the end offset multiplier times the pixels per unit.
    int getEndOffsetMultiplier () const;
    
    int getStartPixel () const;
    int getEndPixel () const;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixel (double val, int dotSize) const;

    void moveCrossPixel (int pixel);
    void setPxPerUnit (int pixels);
    void setTickThickness (int tickThicknessPx);

private:

    // Where cross axis crosses this axis. The cross axis is centered on a pixel. The
    // cross axis is not centered betwenn two pixels on this axis.
    int _cross_pixel__px;

    int _min_val;
    int _max_val;
    int _diff;
    int _px_per_unit;
    int _tick_thickness__px;
    int _start_offset_m;
    int _end_offset_m;
};

#endif