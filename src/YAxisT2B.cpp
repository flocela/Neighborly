#include "YAxisT2B.h"

YAxisT2B::YAxisT2B (
    std::string title,
    PixelConverter* pixelConverter,
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
    int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
    int majTickSpacing,
    int minTickSpacing,  // in units, not pixels
    int labelSpacing // in units, not in pixels.
) : _title{title},
    _pc{pixelConverter},
    _axis_format{axisFormat},
    _x_coord__px{x_coordinate__px},
    _y_coord__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _min_tick_spacing{minTickSpacing},
    _maj_tick_spacing{majTickSpacing},
    _label_spacing{labelSpacing}
{
    // set _top_most_pixel and _bottom_most_pixel
    _top_most_pixel_y__px = _y_coord__px;
    _bottom_most_pixel_y__px = _pc->getPixel(_max_val) + _axis_format.overrunPx();
}

void YAxisT2B::print (Renderer* renderer)
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    addTitle(texts);
    
    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.titleFontSize());
    renderer->renderTexts(texts);
    texts.clear();

    addVerticalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelFontSize());
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);

}

void YAxisT2B::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = _axis_format.axisThicknessPx();
    rect.h = _bottom_most_pixel_y__px - _top_most_pixel_y__px;
    rect.x = _x_coord__px - rect.w/2;
    rect.y = _y_coord__px;
    rects.push_back(rect);
}
        
void YAxisT2B::addTicksAndLabels (
    std::vector<SDL_Rect>& rects,
    std::vector<TextRect>& texts
)
{
    int leftEdgeOfLabelXPx = _x_coord__px -
                             _axis_format.majTickLengthPx() +
                             _axis_format.tickLengthInsideChart() -
                             _axis_format.labelHeightPx();

    TextRect curText = {
        leftEdgeOfLabelXPx,
        _pc->getPixel(_min_val),
        std::to_string(_min_val),
        2
    };

    SDL_Rect curRect;
    curRect.h = _axis_format.tickThickness();
    int curVal = _min_val;
    
    while (curVal <= _max_val)
    {
        int curVal__px = _pc->getPixel(curVal);

        if (curVal % _label_spacing == 0) // TODO do all maj ticks get a label?
        {
            curRect.x = _x_coord__px - 
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart();
            curRect.w = _axis_format.majTickLengthPx();
            curRect.y = curVal__px + (_axis_format.tickThickness()/2);
            rects.push_back(curRect);

            curText.text = std::to_string(curVal);
            curText.yPixel = curVal__px,
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            curRect.x = _x_coord__px - _axis_format.minTickLengthPx();
            curRect.y = curVal__px;
            rects.push_back(curRect);
        }
        ++curVal;
    }
}

void YAxisT2B::addTitle (std::vector<TextRect>& texts)
{
    TextRect tr = {
        _x_coord__px - _axis_format.getHeightOfAxisPx(),
        _top_most_pixel_y__px + (_bottom_most_pixel_y__px - _top_most_pixel_y__px)/2,
        _title, 
        1
    };
    texts.push_back(tr);
}