#ifndef GR_AXIS_VERTICAL_SIMPLE_H
#define GR_AXIS_VERTICAL_SIMPLE_H

#include <memory>
#include "Axis.h"
#include "AxisFormat.h"
#include "Renderer.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class GrAxisVerticalSimple
{

public:

    // xCoordPx is the axis' x-coordinate in pixels. All points on the axis have this x-coordinate.
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

    // Returns length of long vertical line (the axis).
    int getAxisLengthPx () const;

    // Returns the pixel of the average of the min and max values on the axis.
    int getCentralValuePx () const;

    // Labels are the numbers to the left of the axis, but their length is more than just the
    // number.
    // It is the length of the digits in the label plus the space between the label and the tick
    // plus the length of the tick outside the chart.
    int getLabelLengthPx () const;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixels (double yVal, int dotSize) const;

    // Returns the min value as given in the axis in the constructor.
    int getMinVal () const;

    // Returns the max value as given in the axis in the constructor. // TODO may never be called
    int getMaxVal () const;
    
    // The label length plus the axis thickness.
    int sizeXPx () const;
    
    // Same as getAxisLengthPx()
    int sizeYPx () const;

    void print (Renderer* renderer) const;
    
    void moveCrossHairs (int xPx, int yPx);

    // There are background horizontal lines that run across the chart. They
    // line up with the major and minor tick marks.
    void setHorizLength (int horizLengthPx);
    
    // Sets the pixels per unit. Updates the major and minor tick spacing.
    void setPxPerUnit (int pixels);

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

    // This is the axis vertical line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& backgroundLinesMaj, // horizontal lines that cross the chart
        std::vector<Rect>& backgroundLinesMin, // horizontal lines that cross the chart
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const; // number next to tick

    int calcMinTickSpacing () const;

    int calcMajTickSpacing () const;
        
};

#endif