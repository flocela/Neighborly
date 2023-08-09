#ifndef AXIS_LEFT_TO_RIGHT_B__H
#define AXIS_LEFT_TO_RIGHT_B__H

#include "AxisFormat.h"
#include "GrAxis.h"
#include "Renderer.h"
#include "TextRect.h"

// Renders axis from left to right with title at bottom (used for horizontal axes).
class GrAxis_Horizontal :public GrAxis
{
    public:
        GrAxis_Horizontal (
            std::unique_ptr<Axis> axis,
            AxisFormat axisFormat,
            int yCrossPx // y-pixel-value of where x and y axes meet
        );
        GrAxis_Horizontal () = delete;
        GrAxis_Horizontal (const GrAxis_Horizontal& o) = default;
        GrAxis_Horizontal (GrAxis_Horizontal&& o) noexcept = default;
        GrAxis_Horizontal& operator= (const GrAxis_Horizontal& o) = default;
        GrAxis_Horizontal& operator=(GrAxis_Horizontal&& o) noexcept = default;
        ~GrAxis_Horizontal () noexcept = default;

        int getAxisLengthPx() const override;

        int getCentralValuePx () const override;

        // The labels are the numbers below the axis. Their length includes more than just the
        // number. Length is a vertical length (y-direction).
        // It includes the length of the tick outside the chart plus
        // the space between the bottom of the tick and the number plus
        // the height of the number.
        int getLabelLengthPx () const override;

        // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
        // would be {1, 5}.
        std::pair<int, int> getPixels (double xVal, int dotSize) const override;

        int sizeXPx() const override;

        // The label length plus the axis thickness.
        int sizeYPx() const override;

        void moveCrossHairs (int xPx, int yPx) override;

        // There are background horizontal lines that run across the chart. They
        // line up with the major and minor tick marks.
        void setHorizLength (int horizLengthPx) override;

        // Sets the pixels per unit. Updates the major and minor tick spacing.
        void setPxPerUnit (int pixels) override;
        
        void setTickThickness (int tickThicknessPx) override;

    protected:

    // This is the axis horizontal line.
    void implimentAddAxisLine (std::vector<Rect>& rects) const override;

    void implimentAddTicksAndLabels (
        std::vector<Rect>& backgroundLinesMaj, // horizontal lines that cross the chart
        std::vector<Rect>& backgroundLinesMin, // horizontal lines that cross the chart
        std::vector<Rect>& ticks,
        std::vector<TextRect>& texts) const override; // number next to tick

    private:
        AxisFormat _axis_format;
        int _y_cross__px; // where x and y axes cross, this is the y-coordinate
        int _min_tick_spacing;
        int _maj_tick_spacing;

        int calcMinTickSpacing () const;
        
        int calcMajTickSpacing () const;

};

#endif