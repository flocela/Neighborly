#include "YAxisB2T.h"
#include <iomanip>

YAxisB2T::YAxisB2T (
    std::string title,
    PixelConverter* pixelConverter,
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
    int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
    int majTickSpacing,
    int minTickSpacing,  // in units, not pixels
    int labelSpacing, // in units, not in pixels.
    double labelUnitFactor,
    int labelDecimalPlaces
) : _title{title},
    _pc{pixelConverter},
    _axis_format{axisFormat},
    _x_coord__px{x_coordinate__px},
    _y_coord__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _min_tick_spacing{minTickSpacing},
    _maj_tick_spacing{majTickSpacing},
    _label_spacing{labelSpacing},
    _label_unit_factor{labelUnitFactor},
    _label_decimal_places{labelDecimalPlaces}
{
    // set _top_most_pixel and _bottom_most_pixel
    _top_most_pixel_y__px = _pc->getPixel(_max_val) - _axis_format.overrunPx() - 1;
    _bottom_most_pixel_y__px = _y_coord__px;
}

void YAxisB2T::print (Renderer* renderer)
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
        _axis_format.titleHeightPx());
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

void YAxisB2T::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = _axis_format.axisThicknessPx();
    rect.h = _bottom_most_pixel_y__px - _top_most_pixel_y__px + 1;
    rect.x = _x_coord__px - rect.w/2;
    rect.y = _y_coord__px - rect.h;
    rects.push_back(rect);
}
        
void YAxisB2T::addTicksAndLabels (
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
        double printedVal = (double)curVal*(double)(_label_unit_factor);
        std::ostringstream obj1;
        obj1 << std::fixed;
        obj1 << std::setprecision(_label_decimal_places);
        obj1 << printedVal;

        if (curVal % _label_spacing == 0) // TODO do all maj ticks get a label?
        {
            curRect.x = _x_coord__px - 
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart();
            curRect.w = _axis_format.majTickLengthPx();
            curRect.y = curVal__px + (_axis_format.tickThickness()/2);
            rects.push_back(curRect);

            curText.text = obj1.str();
            curText.yPixel = curVal__px;
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            curRect.x = _x_coord__px - _axis_format.minTickLengthPx();
            curRect.w = _axis_format.minTickLengthPx();
            curRect.y = curVal__px + (_axis_format.tickThickness()/2);
            rects.push_back(curRect);
        }
        ++curVal;
    }

}

// TODO we don't have have titles on axes anymore.
void YAxisB2T::addTitle (std::vector<TextRect>& texts)
{
    TextRect tr = {
        _x_coord__px - _axis_format.getHeightOfAxisPx(),
        _top_most_pixel_y__px + (_bottom_most_pixel_y__px - _top_most_pixel_y__px)/2,
        _title, 
        1
    };
    texts.push_back(tr);
}
