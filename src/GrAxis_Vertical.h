#ifndef GR_AXIS_VERTICAL_H
#define GR_AXIS_VERTICAL_H

#include "Axis.h"
#include "AxisFormat.h"
#include "GrAxis.h"
#include "Renderer.h"
#include "BasicAxis.h"
#include "TextRect.h"

// Vertical axis, numbers run from bottom to top. Labels are on the left.
class GrAxis_Vertical : public GrAxis
{

public:

    // xCoordPx is the axis's x-coordinate in pixels. As xCoordPx increases, the axis moves right.
    GrAxis_Vertical (
        std::unique_ptr<Axis> axis,
        AxisFormat axisFormat,
        int xCoordPx
    );

    GrAxis_Vertical () = delete;
    GrAxis_Vertical (const GrAxis_Vertical& o) = default;
    GrAxis_Vertical (GrAxis_Vertical&& o) noexcept = default;
    GrAxis_Vertical& operator= (const GrAxis_Vertical& o) = default;
    GrAxis_Vertical& operator=(GrAxis_Vertical&& o) noexcept = default;
    ~GrAxis_Vertical () noexcept = default;

    int getAxisLengthPx () const override;

    int getCentralValuePx () const override;

    // Labels are the numbers to the left of the axis, but their length is more than just the
    // number.
    // It is the length of the digits in the label plus the space between the label and the tick
    // plus the length of the tick outside the chart.
    int getLabelLengthPx () const override;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    std::pair<int, int> getPixels (double yVal, int dotSize) const override;

    virtual int getMinVal () const override;

    virtual int getMaxVal () const override;
    
    // The label length plus the axis thickness.
    int sizeXPx() const override;
    
    // Same as getAxisLengthPx()
    int sizeYPx() const override;
    
    void moveCrossHairs (int xPx, int yPx) override;

    // There are background horizontal lines that run across the chart. They
    // line up with the major and minor tick marks.
    void setHorizLength (int horizLengthPx) override;
    
    // Sets the pixels per unit. Updates the major and minor tick spacing.
    void setPxPerUnit (int pixels) override;

protected:

    // This is the axis vertical line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const override;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& backgroundLinesMaj, // horizontal lines that cross the chart
        std::vector<Rect>& backgroundLinesMin, // horizontal lines that cross the chart
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const override; // number next to tick

private:
    // length of horizontal background lines
    int _horiz_line_length__px = 0;

    int _x_coord__px; // the axis's x-coordinate in pixels.
    int _min_tick_spacing; // in units, not pixels
    int _maj_tick_spacing; // in units, not pixels

    int _text_spacer = 3; // space to the right of labels, and to the left of tick marks

    int calcMinTickSpacing () const;

    int calcMajTickSpacing () const;
        
};

#endif