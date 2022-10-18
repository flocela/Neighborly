#include "AxisBottomToTopL.h"

AxisBottomToTopL::AxisBottomToTopL (
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
    int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal. 
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

    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx());
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}

void AxisBottomToTopL::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px - _axis_format.axisThicknessPx()/2,
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
    int minYPx = _y_cross__px - ( _start_offset_m * _px_per_unit );
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChart();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChart();

    int curVal = _min_val;
    int curVal__px = minYPx - _px_per_unit * (curVal - _min_val);

    TextRect curText{
        majTickXPx - _text_spacer, // should be line spacer from _axis_format
        curVal__px,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        3
    };

    SDL_Rect majRect{
        majTickXPx,
        curVal__px - (_tick_thickness__px/2),
        _axis_format.majTickLengthPx(),
        _tick_thickness__px
    };

    SDL_Rect minRect{
        minTickXPx,
        curVal__px - (_tick_thickness__px/2),
        _axis_format.minTickLengthPx(),
        _tick_thickness__px
    };

    int topMostPixelY = calcTopMostPixelY();

    while ( curVal__px >= topMostPixelY )
    {   
        if (curVal % _maj_tick_spacing == 0)
        {
            majRect.y = curVal__px - (_tick_thickness__px/2);
            
            curText.text = std::to_string(curVal);
            curText.yPixel = curVal__px;

            rects.push_back(majRect);
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            minRect.y = curVal__px - (_tick_thickness__px/2);
            rects.push_back(minRect);
        }
        ++curVal;
        curVal__px = minYPx - _px_per_unit * (curVal - _min_val);
    }
}

int AxisBottomToTopL::calcTopMostPixelY ()
{
    int diff = _max_val - _min_val;
    return _y_cross__px - (_px_per_unit * (diff + _start_offset_m + _end_offset_m));
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

int AxisBottomToTopL::sizeXPx ()
{
    return 
        (_max_val/10) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _text_spacer + // TODO should be line spacer from _axis_format
        _axis_format.majTickLengthOutsideChart() +
        _axis_format.axisThicknessPx();
}

int AxisBottomToTopL::sizeYPx ()
{
    return axisLengthPx();
}

int AxisBottomToTopL::axisLengthPx ()
{
    return _y_cross__px - calcTopMostPixelY() + 1; // TODO do I have to add the one?
}



