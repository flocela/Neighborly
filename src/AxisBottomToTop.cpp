#include "AxisBottomToTop.h"
#include <iomanip>

AxisBottomToTop::AxisBottomToTop (
    std::string title,
    AxisFormat axisFormat,
    int x_coordinate__px, // where x and y axis meet
    int y_coordinate__px, // where x and y axis meet
    int minVal, // min value delineated with tick. It is startOffset__px from the start of axis.
    int maxVal, // max value delineated with tick. Axis continues for endOffset__px afer maxVal.
    int majTickSpacing,
    int minTickSpacing,  
    int labelSpacing,
    int pxPerUnit 
) : _title{title},
    _axis_format{axisFormat},
    _x_cross__px{x_coordinate__px},
    _y_cross__px{y_coordinate__px},
    _min_val{minVal},
    _max_val{maxVal},
    _min_tick_spacing{minTickSpacing},
    _maj_tick_spacing{majTickSpacing},
    _label_spacing{labelSpacing},
    _px_per_unit{pxPerUnit}
{
    int diff = _max_val - _min_val;
    _top_most_pixel_y__px = 
        _y_cross__px -
        _px_per_unit * (diff) -
        _axis_format.offsetPx() -
        _axis_format.overrunPx();
    _bottom_most_pixel_y__px = _y_cross__px; // TODO this is the same as _min_val__px
    _min_val__px = _y_cross__px;
    _max_val__px = _y_cross__px + _px_per_unit * (diff); // TODO is this ever used?
}

void AxisBottomToTop::print (Renderer* renderer)
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    //addTitle(texts);

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.titleHeightPx());
    renderer->renderTexts(texts);
    texts.clear();

    addVerticalLine(rects);
    //addTicksAndLabels (rects, texts);

    /*renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx());*/
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);

}

void AxisBottomToTop::addVerticalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = _axis_format.axisThicknessPx();
    rect.h = _bottom_most_pixel_y__px - _top_most_pixel_y__px + 1;
    rect.x = _x_cross__px - rect.w/2; // is the rect.w/2 needed? Is thickness of axis taken into account in rect.y?
    rect.y = _top_most_pixel_y__px;
    rects.push_back(rect);
}
        
void AxisBottomToTop::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int leftEdgeOfLabelXPx = _x_cross__px -
                             _axis_format.majTickLengthPx() +
                             _axis_format.tickLengthInsideChart() -
                             _axis_format.labelHeightPx(); // TODO there are no more axis labels

    TextRect curText = {
        leftEdgeOfLabelXPx,
        _min_val__px,
        std::to_string(_min_val),
        2
    };

    SDL_Rect curRect;
    curRect.h = _axis_format.tickThickness();
    int curVal = _min_val;
    
    while (curVal <= _max_val)
    {
        int curVal__px = _min_val__px + _px_per_unit * (curVal - _min_val);

        if (curVal % _label_spacing == 0) // TODO do all maj ticks get a label?
        {
            curRect.x = _x_cross__px - 
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart();
            curRect.w = _axis_format.majTickLengthPx();
            curRect.y = curVal__px + (_axis_format.tickThickness()/2);
            rects.push_back(curRect);

            curText.text = std::to_string(curVal);
            curText.yPixel = curVal__px;
            texts.push_back(curText);
        }
        else if (curVal % _min_tick_spacing == 0)
        {
            curRect.x = _x_cross__px - _axis_format.minTickLengthPx();
            curRect.w = _axis_format.minTickLengthPx();
            curRect.y = curVal__px + (_axis_format.tickThickness()/2);
            rects.push_back(curRect);
        }
        ++curVal;
    }

}

// TODO we don't have have titles on axes anymore.
void AxisBottomToTop::addTitle (std::vector<TextRect>& texts)
{
    TextRect tr = {
        _x_cross__px - _axis_format.getAxisHeightPx(),
        _top_most_pixel_y__px + (_bottom_most_pixel_y__px - _top_most_pixel_y__px)/2,
        _title, 
        1
    };
    texts.push_back(tr);
}
