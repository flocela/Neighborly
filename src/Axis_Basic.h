#ifndef AXIS_BASIC_H
#define AXIS_BASIC_H

#include <utility>
#include "Axis.h"

// Axis_Basic represents an axis. It's tick thickness is one.
class Axis_Basic : public Axis
{

public:

    // Forward is true, means the values on the axis run in the direction of the coordinates
    // in the window.
    // Pixels in window: 000   005   010   150
    // Values on axis:   100   200   300   400

    // If forward is false, then the values on the axis run in the direction opposite
    // the coordinates in the window.
    // Pixels in window: 000   005   010    150
    // Values on axis:   400   300   200    100

    // crossPixel is at the start of the axis. It is startOffset units away from the lowVal.
    // The units for crossPixel is pixels. The units for startOffset and endOffset is units.
    // The units for pxPerUnit is px/unit.
    // The starting pixel of the axis is startOffset * pxPerUnit away from the low value pixel. The
    // end of the axis is endOffset * pxPerUnit away from the high value.

    // pxPerUnit should be positive.
    Axis_Basic (
        bool forward,
        int crossPixel,
        int lowVal,
        int highVal,
        int pxPerUnit,
        int startOffset,
        int endOffset
    );

    Axis_Basic () = delete;
    Axis_Basic (const Axis_Basic& o) = default;
    Axis_Basic (Axis_Basic&& o) noexcept = default;
    Axis_Basic& operator= (const Axis_Basic& o) = default;
    Axis_Basic& operator= (Axis_Basic&& o) noexcept = default;
    ~Axis_Basic () noexcept = default;
    int getAxisLengthPx () const override;

    // Returns the low val as given in the constructor.
    int getLowVal () const override;

    // Returns the high val as given in the constructor.
    int getHighVal () const override;

    int getPixelsPerUnit () const override;

    // Always returns 1.
    int getTickThickness__px () const override;

    int getStartOffset () const override;

    int getEndOffset () const override;

    int getStartPixel () const override;

    int getEndPixel () const override;

    // Returns the pixels covered by a dot at value. If a pixel is negative, then zero is returned
    // for that pixel. Say val is zero and corresponds to a pixel of zero, but the dotSize is 3.
    // Then pixels of {-1, 1} should be retured, but since there are no negative pixels,
    // {0, 1} is returned.
    std::pair<int, int> getPixels (double val, int dotSize) const override;

    int getCenterValPx () const;

    void moveCrossPixel (int pixel) override;
    void setPxPerUnit (int pixels) override;
    void setDirectionOfAxis (bool forward) override;

private:

    // Axis values increase in the direction of the window coordinate system.
    bool _forward = true;

    int _cross_pixel__px;
    int _low_val;
    int _high_val;

    // val that is closest to zero coordinate in window
    int _start_val;

    // val that is farthest from zero coordinate in window
    int _end_val;
    
    int _px_per_unit;
    int _tick_thickness__px{1};
    int _start_offset_m;
    int _end_offset_m;
};

#endif