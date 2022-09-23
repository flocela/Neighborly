#include "AxisBottomToTopL.h"
#include <iomanip>

AxisBottomToTopL::AxisBottomToTopL (
    std::string title,
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
    int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal. 
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : _title{title},
    _axis_format{axisFormat},
    _x_cross__px{x_coordinate__px},
    _y_cross__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _diff{_max_val - _min_val},
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{tickThickness},
    _min_tick_spacing{calcMinTickSpacing(_px_per_unit)},
    _maj_tick_spacing{calcMajTickSpacing(_px_per_unit)},
    _label_spacing{calcLabelSpacing(_px_per_unit)},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

void AxisBottomToTopL::print (Renderer* renderer)
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx());
    renderer->renderTexts(texts);
    texts.clear();

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
    SDL_Rect rect;
    rect.w = _axis_format.axisThicknessPx();
    rect.h = _y_cross__px  - calcTopMostPixelY() + 1;
    rect.x = _x_cross__px - rect.w/2; // is the rect.w/2 needed? Is thickness of axis taken into account in rect.y?
    rect.y = calcTopMostPixelY();
    rects.push_back(rect);
}
        
void AxisBottomToTopL::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int leftEdgeOfLabelXPx = _x_cross__px -
                             _axis_format.majTickLengthPx() +
                             _axis_format.tickLengthInsideChart() -
                             _axis_format.labelHeightPx(); // TODO there are no more axis labels

    int minYPx = _y_cross__px - ( _start_offset_m * _px_per_unit );

    TextRect curText = {
        leftEdgeOfLabelXPx,
        minYPx,
        std::to_string(_min_val),
        2
    };

    SDL_Rect curRect;
    curRect.h = _tick_thickness__px;
    int curVal = _min_val;
    int curVal__px = minYPx - _px_per_unit * (curVal - _min_val);

    while (curVal__px >= calcTopMostPixelY())
    {   
        if (curVal % _label_spacing == 0) // TODO do all maj ticks get a label?
        {
            curRect.x = _x_cross__px - 
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart();
            curRect.w = _axis_format.majTickLengthPx();
            curRect.y = curVal__px - (_tick_thickness__px/2);
            rects.push_back(curRect);

            curText.text = std::to_string(curVal);
            curText.yPixel = curVal__px;
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            curRect.x = _x_cross__px - _axis_format.minTickLengthPx();
            curRect.w = _axis_format.minTickLengthPx();
            curRect.y = curVal__px - (_tick_thickness__px/2);
            rects.push_back(curRect);
        }
        ++curVal;
        curVal__px = minYPx - _px_per_unit * (curVal - _min_val);
    }
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
    _label_spacing = calcLabelSpacing(_px_per_unit);

}


