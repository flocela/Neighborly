#ifndef GR_AXIS_VERTICAL_SIMPLE_H
#define GR_AXIS_VERTICAL_SIMPLE_H

#include <memory>
#include "Axis.h"
#include "AxisFormat.h"
#include "Renderer.h"
#include "TextRect.h"

// Used to render a vertical axis with labels on the left.
class GrAxisVerticalSimple
{

public:

    // The axis lies on a vertical line, so all points on the axis have the same x-coordinate
    // in pixels.
    // @xCoordPx is the axis's x-coordinate in pixels.
    GrAxisVerticalSimple (
        std::unique_ptr<Axis> axis,
        AxisFormat axisFormat,
        int xCoordPx
    );

    GrAxisVerticalSimple () = delete;
    GrAxisVerticalSimple (const GrAxisVerticalSimple& o) = default;
    GrAxisVerticalSimple (GrAxisVerticalSimple&& o) noexcept = default;
    GrAxisVerticalSimple& operator= (const GrAxisVerticalSimple& o) = default;
    GrAxisVerticalSimple& operator=(GrAxisVerticalSimple&& o) noexcept = default;
    ~GrAxisVerticalSimple () noexcept = default;

    // Returns length of vertical line (the axis).
    int getAxisLengthPx () const;

    // Returns the pixel of the average of the low and high values on the axis.
    int getCentralValuePx () const;

    // Ticks and numberes designate the value at a point on the axis. The length of the labels is
    // taken perpendicular to the axis (a horizontal length, as in the x-direction).
    // It includes the length of the tick outside the chart plus
    // the space between the tick and the number plus
    // the width of the digits in the number.
    int getLabelLengthPx () const;

    int getStartOffset () const;

    int getEndOffset () const;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixels (double yVal, int dotSize) const;

    // Returns the low value as given in the axis in the constructor.
    int getLowVal () const;

    // Returns the high value as given in the axis in the constructor.
    int getHighVal () const;
    
    // The label length plus the axis thickness.
    int sizeXPx () const;
    
    // Same as getAxisLengthPx()
    int sizeYPx () const;

    void print (Renderer* renderer) const;
    
    void moveCrossHairs (int xPx, int yPx);

    // There are background horizontal lines that run across the chart. They
    // line up with the major and minor tick marks.
    void setHorizLength (int horizLengthPx);
    
    // Sets the pixels per unit. Updates the major and minor tick spacing. Pixels per
    // unit must be positive.
    void setPxPerUnit (int pixelsPerUnit);

    void setDirectionOfAxis (bool forward);

private:

    std::unique_ptr<Axis> _axis;
    AxisFormat _axis_format;

    // length of horizontal background lines
    int _horiz_line_length__px = 0;

    // the axis' x-coordinate in pixels. This is the same for every pixel on the axis line.
    int _x_coord__px;

    int _min_tick_spacing; // in units, not pixels
    int _maj_tick_spacing; // in units, not pixels

    int _text_spacer = 3; // space to the right of labels, and to the left of tick marks

    // This is the axis' vertical line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& backgroundLinesMaj, // line up with the major tick marks
        std::vector<Rect>& backgroundLinesMin, // line up with the minor tick marks
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const; // numbers next to ticks

    int calcMinTickSpacing () const;

    int calcMajTickSpacing () const;
        
};

#endif