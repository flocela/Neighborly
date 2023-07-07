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
    // If _centered_on_pixel is false, then the cross axis actually crosses this axis
    // between the returned pixel and 1 minus the returned pixel.
    int getCrossPx__px () const;

    int getCenterValPx () const;
    int getMinVal () const;
    int getMaxVal () const;
    int getDiff () const;
    int getPixelsPerUnit () const;
    int getTickThichness__px () const;
    int getStartOffsetMultiplier () const;
    int getEndOffsetMultiplier () const;
    int getFrontPixel () const;
    int getEndPixel () const;

    // Returns the pixels covered by a dot at value.
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