#ifndef AXIS_BASIC_H
#define AXIS_BASIC_H

#include <utility>
#include "Axis.h"

class Axis_Basic : public Axis
{

public:

    // Forward is true, means the values on the axis run in the direction of the coordinates
    // in the window.
    // CrossPixel is where the perpendicular axis crosses this axis.
    Axis_Basic (
        bool forward,
        int crossPixel,
        int minVal,
        int maxVal,
        int pxPerUnit,
        int startOffsetMultiplier,
        int endOffset
    );

    Axis_Basic () = delete;
    Axis_Basic (const Axis_Basic& o) = default;
    Axis_Basic (Axis_Basic&& o) noexcept = default;
    Axis_Basic& operator= (const Axis_Basic& o) = default;
    Axis_Basic& operator= (Axis_Basic&& o) noexcept = default;
    ~Axis_Basic () noexcept = default;

    int getAxisLengthPx () const override;

    int getMinVal () const override;

    int getMaxVal () const override;

    int getDiff () const override;

    int getPixelsPerUnit () const override;

    int getTickThickness__px () const override;

    int getStartOffsetMultiplier () const override;

    int getEndOffsetMultiplier () const override;

    int getStartPixel () const override;

    int getEndPixel () const override;

    // Returns the pixels covered by a dot at value. If a pixel is negative, then zero is returned
    // for that pixel. Say val is zero and corresponds to a pixel of zero, but the dotSize is 3.
    // Then pixels of {-1, 1} should be retured, but since there are no negative pixels,
    // {-1, 1} is returned.
    std::pair<int, int> getPixels (double val, int dotSize) const override;

    int getCenterValPx () const;

    void moveCrossPixel (int pixel) override;
    void setPxPerUnit (int pixels) override;

private:

    // Axis values increase in the direction of the window coordinate system.
    bool _forward = true;

    // Where perpendicular axis crosses this axis. The cross axis is centered on a pixel. The
    // cross axis is not centered betwenn two pixels on this axis.
    int _cross_pixel__px;
    int _min_val;
    int _max_val;

    // val that is closest to zero coordinate in window
    int _start_val;

    // val that is farthest from zero coordinate in window
    int _end_val;
    
    int _diff;
    int _px_per_unit;
    int _tick_thickness__px{1};
    int _start_offset_m;
    int _end_offset_m;
};

#endif