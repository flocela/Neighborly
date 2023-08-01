#ifndef REVERSE_AXIS_H
#define REVERSE_AXIS_H

#include <utility>

class ReverseAxis
{
public:
    ReverseAxis (
        int crossPixel,
        int minVal,
        int maxVal,
        int pxPerUnit,
        int tickThickness,
        int startOffsetMultiplier,
        int endOffset
    );

    ReverseAxis () = delete;
    ReverseAxis (const ReverseAxis& o) = default;
    ReverseAxis (ReverseAxis&& o) noexcept = default;
    ReverseAxis& operator= (const ReverseAxis& o) = default;
    ReverseAxis& operator= (ReverseAxis&& o) noexcept = default;
    ~ReverseAxis () noexcept = default;

    int getAxisLengthPx () const;

    // Returns the min val given in the constructor.
    int getMinVal () const;

    // Returns the max val given in the constrtor.
    int getMaxVal () const;

    // Returns the difference between the max and min vals given in the constructor.
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

    // Returns the pixels covered by a dot at value.
    std::pair<int, int> getPixels (double val, int dotSize) const;

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