#ifndef GRAXIS_HORIZONTAL_SIMPLE__H
#define GRAXIS_HORIZONTAL_SIMPLE__H

#include <memory>
#include "Axis.h"
#include "AxisFormat.h"
#include "Renderer.h"
#include "TextRect.h"

// Renders axis from left to right.
class GrAxisHorizontalSimple
{

public:

    // yCoordPx is the axis's y-coordinate in pixels. The all points on the axis line will have
    // this same y-coordinate.
    GrAxisHorizontalSimple (
        std::unique_ptr<Axis> axis,
        AxisFormat axisFormat,
        int yCoordPx,
        bool labelsOnTop
    );
    
    GrAxisHorizontalSimple () = delete;
    GrAxisHorizontalSimple (const GrAxisHorizontalSimple& o) = default;
    GrAxisHorizontalSimple (GrAxisHorizontalSimple&& o) noexcept = default;
    GrAxisHorizontalSimple& operator= (const GrAxisHorizontalSimple& o) = default;
    GrAxisHorizontalSimple& operator=(GrAxisHorizontalSimple&& o) noexcept = default;
    ~GrAxisHorizontalSimple () noexcept = default;

    // Returns length of long horizontal line (the axis).
    int getAxisLengthPx() const;

    // Returns the pixel of the average of the min and max values on the axis.
    int getCentralValuePx () const;

    // The labels are the numbers below the axis. Their length includes more than just the
    // number. Length is a vertical length (y-direction).
    // It includes the length of the tick outside the chart plus
    // the space between the bottom of the tick and the number plus
    // the height of the number.
    int getLabelLengthPx () const;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixels (double xVal, int dotSize) const;

    // Returns the min value as given in the axis in the constructor.
    int getMinVal () const;

    // Returns the max value as given in the axis in the constructor. // TODO may never be called
    int getMaxVal () const;

    // Same as getAxisLengthPx()
    int sizeXPx () const;

    // The label length plus the axis thickness.
    int sizeYPx () const;

    void print (Renderer* renderer) const;

    void moveCrossHairs (int xPx, int yPx);

    // Sets the pixels per unit. Updates the major and minor tick spacing.
    void setPxPerUnit (int pixels);

private:
    std::unique_ptr<Axis> _axis;
    AxisFormat _axis_format;
    int _y_coord__px; // the axis's y-coordinate in pixels
    bool _labels_on_top; // true if the labels should be above the axis, false if below
    int _min_tick_spacing;
    int _maj_tick_spacing;

    int calcMinTickSpacing () const;
    
    int calcMajTickSpacing () const;

    // This is the axis horizontal line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const; // number next to tick

};

#endif