#include "AxisTopToBottomL.h"

AxisTopToBottomL::AxisTopToBottomL (
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

void AxisTopToBottomL::print (Renderer* renderer)
{
    std::vector<SDL_Rect> rects = {};
    std::vector<TextRect> texts = {};

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx()
    );

    addVerticalLine(rects);
    addTicksAndLabels (rects, texts);

    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);

}

void AxisTopToBottomL::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px - _axis_format.axisThicknessPx()/2,
        _y_cross__px,
        _axis_format.axisThicknessPx(),
        axisLengthPx()
    };

    rects.push_back(rect);
}

int AxisTopToBottomL::calcBotMostPixelYPx ()
{
    int diff = _max_val - _min_val;
    return _y_cross__px + (_px_per_unit * (diff + _start_offset_m + _end_offset_m));
}
        
void AxisTopToBottomL::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int minYPx = _y_cross__px + ( _start_offset_m * _px_per_unit );
    int majTickXPx = _x_cross__px - _axis_format.majTickLengthOutsideChart();
    int minTickXPx = _x_cross__px - _axis_format.minTickLengthOutsideChart();

    int curVal = _min_val;
    int curVal__px = minYPx + _px_per_unit * (curVal - _min_val);

    TextRect curText = {
        _x_cross__px - _axis_format.majTickLengthOutsideChart(),
        curVal__px,
        std::to_string(_min_val),
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
    
    int botMostPixelY = calcBotMostPixelYPx();

    while (curVal__px <= botMostPixelY)
    {   
        if (curVal % _maj_tick_spacing == 0) // TODO do all maj ticks get a label?
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
        curVal__px = minYPx + _px_per_unit * (curVal - _min_val);
    }
}

void AxisTopToBottomL::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisTopToBottomL::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);

}

int AxisTopToBottomL::sizeXPx ()
{
    return 
        (_max_val/10) * _axis_format.labelWidthMultiplier() * _axis_format.labelHeightPx() +
        _axis_format.labelLineSpacePx() + // TODO should be line spacer from _axis_format
        _axis_format.majTickLengthOutsideChart() +
        _axis_format.axisThicknessPx();
}

int AxisTopToBottomL::sizeYPx()
{
    return axisLengthPx();
}

int AxisTopToBottomL::axisLengthPx()
{
    return calcBotMostPixelYPx() - _y_cross__px + 1; // TODO is this correct?
}
