#ifndef GR_AXIS_H
#define GR_AXIS_H

#include <memory>
#include "Axis.h"
#include "Renderer.h"

class GrAxis
{

public:

    GrAxis (std::unique_ptr<Axis> axis);
    ~GrAxis () noexcept = default;

    virtual int getAxisLengthPx () const = 0;

    // The labels are the numbers to the left of the axis, but their length is more
    // than just the number.
    // The label length is the length of the digits in the label plus
    // the space between the label and the tick plus
    // the length of the tick outside the chart.
    // The length is in the x direction.
    virtual int getLabelLengthPx () const = 0;

    // Returns the pixels covered by a dot at value. If a dot is 5 pixels wide, a possible result
    // would be {1, 5}.
    virtual std::pair<int, int> getPixels (double yVal, int dotSize) const = 0;
    
    virtual void print (Renderer* renderer) const = 0;
    
    // The label length plus the axis thickness.
    virtual int sizeXPx() const = 0;
    
    // Same as getAxisLengthPx()
    virtual int sizeYPx() const = 0;
    
    virtual void moveCrossHairs (int xPx, int yPx) = 0;

    // There are background horizontal lines that run across the chart. They
    // line up with the major and minor tick marks.
    virtual void setHorizLength (int horizLengthPx) = 0;
    
    // Sets the pixels per unit. Updates the major and minor tick spacing.
    virtual void setPxPerUnit (int pixels) = 0;
    
    virtual void setTickThickness (int tickThicknessPx) = 0;

protected:
    GrAxis () = delete;
    GrAxis (const GrAxis& o) = default;
    GrAxis (GrAxis&& o)noexcept = default;
    GrAxis& operator= (const GrAxis& o) = default;
    GrAxis& operator= (GrAxis&& o) noexcept = default;

    std::unique_ptr<Axis> _axis;

};

#endif