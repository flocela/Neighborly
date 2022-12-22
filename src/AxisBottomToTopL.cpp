#include "AxisBottomToTopL.h"

AxisBottomToTopL::AxisBottomToTopL (
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal,
    int maxVal, 
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : 
    _axis_format{axisFormat},
    _x_cross__px{x_coordinate__px},
    _y_cross__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{tickThickness},
    _min_tick_spacing{calcMinTickSpacing(_px_per_unit)},
    _maj_tick_spacing{calcMajTickSpacing(_px_per_unit)},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

void AxisBottomToTopL::print (Renderer* renderer)
{
    std::vector<SDL_Rect> rects = {};
    std::vector<TextRect> texts = {};

    addVerticalLine(rects);
    addTicksAndLabels (rects, texts);

    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}

void AxisBottomToTopL::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px,
        calcTopMostPixelY(),
        _axis_format.axisThicknessPx(),
        axisLengthPx()
    };
    rects.push_back(rect);
}
        
void AxisBottomToTopL::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChartPx();

    // each tick is a rectangle, curVal__px is the top left pixel of that tick's rectangle
    int curVal = _min_val;
    int curVal__px = getYPixelForPrinting(_min_val) - ( _tick_thickness__px/2 );

    TextRect curText{
        majTickXPx - _text_spacer,
        curVal__px,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        3
    };

    SDL_Rect majRect{
        majTickXPx,
        curVal__px,
        _axis_format.majTickLengthPx(),
        _tick_thickness__px
    };

    SDL_Rect minRect{
        minTickXPx,
        curVal__px,
        _axis_format.minTickLengthPx(),
        _tick_thickness__px
    };

    int topMostPixelY = calcTopMostPixelY();
    while ( curVal__px >= topMostPixelY )
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect.y = curVal__px;

            curText._text = std::to_string(curVal);
            curText._y_pixel = curVal__px;

            rects.push_back(majRect);
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect.y = curVal__px;
            rects.push_back(minRect);
        }
        ++curVal;
        curVal__px = getYPixelForPrinting(curVal) - (_tick_thickness__px/2);
    }
}

int AxisBottomToTopL::calcTopMostPixelY ()
{
    int numOfUnits = _max_val - _min_val;
    return _y_cross__px - (_px_per_unit * (numOfUnits + _start_offset_m + _end_offset_m));
}

void AxisBottomToTopL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisBottomToTopL::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);

}

void AxisBottomToTopL::setTickThickness (int tickThicknessPx) 
{
    _tick_thickness__px = tickThicknessPx;
}

int AxisBottomToTopL::sizeXPx ()
{  
    // Three is max number of digits in the y-axis label.
    return 
        (3) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.axisThicknessPx();
}

int AxisBottomToTopL::sizeYPx ()
{
    return axisLengthPx();
}

int AxisBottomToTopL::axisLengthPx ()
{
    return _y_cross__px - calcTopMostPixelY();
}

int AxisBottomToTopL::calcMinTickSpacing (int pixelsPerUnit)
{ 
    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisBottomToTopL::calcMajTickSpacing (int pixelsPerUnit)
{ 
    return (pixelsPerUnit > 10)? 5 : 10;
}

int AxisBottomToTopL::getYPixelForPrinting (double yVal)
{
    int minYPx = 
        _y_cross__px -
        ( _start_offset_m * _px_per_unit ) +
        1;

    return minYPx - _px_per_unit * (yVal - _min_val);
    
}
