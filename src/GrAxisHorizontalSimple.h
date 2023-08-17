#ifndef GRAXIS_HORIZONTAL_SIMPLE__H
#define GRAXIS_HORIZONTAL_SIMPLE__H

#include <memory>
#include "Axis.h"
#include "AxisFormat.h"
#include "Renderer.h"
#include "TextRect.h"

// Used to render a horizontal axis
class GrAxisHorizontalSimple
{

public:

    // The axis lies on a horizontal line, so all points on the axis have the same y-coordinate
    // in pixels.
    // yCoordPx is the axis's y-coordinate in pixels.
    // labelsOnTop as true, signifies that the labels will be above the axis. Otherwise
    // the labels are below the axis.
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

    // Returns length of horizontal line (the axis).
    int getAxisLengthPx() const;

    // Returns the pixel of the average of the low and high values on the axis.
    int getCentralValuePx () const;

    // Ticks and numberes designate the value at a point on the axis. The length of the labels is
    // taken perpendicular to the axis (a vertical length, as in the y-direction).
    // It includes the length of the tick outside the chart plus
    // the space between the bottom of the tick and the number plus
    // the height of the number.
    int getLabelLengthPx () const;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixels (double xVal, int dotSize) const;

    // Returns the low value as given in the axis in the constructor.
    int getLowVal () const;

    // Returns the high value as given in the axis in the constructor.
    int getHighVal () const;

    // Since this is a horizontal axis, returns the same as getAxisLengthPx().
    int sizeXPx () const;

    // The label length plus the axis thickness.
    int sizeYPx () const;

    int getStartOffset () const;

    int getEndOffset () const;

    void print (Renderer* renderer) const;

    void moveCrossHairs (int xPx, int yPx);

    // Sets the pixels per unit. Updates the major and minor tick spacing.
    void setPxPerUnit (int pixels);

    void setDirectionOfAxis (bool forward);

private:

    std::unique_ptr<Axis> _axis;
    AxisFormat _axis_format;

     // the axis's y-coordinate in pixels
    int _y_coord__px;

    // true if the labels should be above the axis, false if below
    bool _labels_on_top; 
    int _min_tick_spacing;
    int _maj_tick_spacing;

    int calcMinTickSpacing () const;
    
    int calcMajTickSpacing () const;

    // This is the axis' horizontal line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const;

};

#endif