#include "AxisTopToBottomL.h"
#include <iomanip>

AxisTopToBottomL::AxisTopToBottomL (
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

void AxisTopToBottomL::print (Renderer* renderer)
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

void AxisTopToBottomL::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = _axis_format.axisThicknessPx();
    rect.h = _y_cross__px  - calcBotMostPixelY() + 1; // TODO, do I need this 1, or should it be thickness?
    rect.x = _x_cross__px - rect.w/2; // is the rect.w/2 needed? Is thickness of axis taken into account in rect.y?
    rect.y = _y_cross__px;
    rects.push_back(rect);
}
        
void AxisTopToBottomL::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int leftEdgeOfLabelXPx = _x_cross__px -
                             _axis_format.majTickLengthPx() +
                             _axis_format.tickLengthInsideChart() -
                             _axis_format.labelHeightPx(); // TODO there are no more axis labels

    int minYPx = _y_cross__px + ( _start_offset_m * _px_per_unit );

    TextRect curText = {
        leftEdgeOfLabelXPx,
        minYPx,
        std::to_string(_min_val),
        3
    };

    SDL_Rect curTick;
    curTick.h = _tick_thickness__px;

    int curVal = _min_val;
    int curVal__px = minYPx + _px_per_unit * (curVal - _min_val);
    int botMostPixelY = calcBotMostPixelY();

    while (curVal__px <= botMostPixelY)
    {   
        if (curVal % _label_spacing == 0) // TODO do all maj ticks get a label?
        {
            curTick.x = _x_cross__px - 
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart();
            curTick.w = _axis_format.majTickLengthPx();
            curTick.y = curVal__px - (_tick_thickness__px/2); // TODO check subtracting half thickness
            rects.push_back(curTick);

            curText.text = std::to_string(curVal);
            curText.yPixel = curVal__px;
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            curTick.x = _x_cross__px - _axis_format.minTickLengthPx();
            curTick.w = _axis_format.minTickLengthPx();
            curTick.y = curVal__px - (_tick_thickness__px/2);
            rects.push_back(curTick);
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
    _label_spacing = calcLabelSpacing(_px_per_unit);

}


