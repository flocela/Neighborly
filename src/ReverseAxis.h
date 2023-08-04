#ifndef REVERSE_AXIS_H
#define REVERSE_AXIS_H

#include <utility>

#include "Axis.h"

class ReverseAxis : public Axis
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

    int getAxisLengthPx () const override;

    // Returns the min val given in the constructor.
    int getMinVal () const override;

    // Returns the max val given in the constrtor.
    int getMaxVal () const override;

    // Returns the difference between the max and min vals given in the constructor.
    int getDiff () const override;

    int getPixelsPerUnit () const override;
    int getTickThichness__px () const override;

    // There is a space between the start of the axis and the first min value given in the
    // constructor. That space is the start offset multiplier times the pixels per unit.
    int getStartOffsetMultiplier () const override;

    // There is a space between the max value given in the constructor and the end of the axis.
    // That space is the end offset multiplier times the pixels per unit.
    int getEndOffsetMultiplier () const override;

    int getStartPixel () const override;
    int getEndPixel () const override;

    // Returns the pixels covered by a dot at value.
    std::pair<int, int> getPixels (double val, int dotSize) const override;

    // Returns the central pixel between the min and max values given in the constructor.
    int getCenterValPx () const;

    void moveCrossPixel (int pixel) override;
    void setPxPerUnit (int pixels) override;
    void setTickThickness (int tickThicknessPx) override;

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