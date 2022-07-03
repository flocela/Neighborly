#include "XAxisL2R.h"

XAxisL2R::XAxisL2R (
    std::string title,
    PixelConverter* pixelConverter,
    AxisFormat axisFormat,
    int x_coordinate__px,
    int y_coordinate__px,
    int minVal,
    int maxVal,
    int majTickSpacing,
    int minTickSpacing,
    int labelSpacing
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
    _left_most_pixel_x__px = _x_coord__px;
    _right_most_pixel_x__px = _pc->getPixel(_max_val) + _axis_format.overrunPx();

}

void XAxisL2R::print (Renderer* renderer)
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    addTitle(texts);
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.titleFontSize());
    renderer->renderTexts(texts);
    texts.clear();

    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelFontSize());
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}

int XAxisL2R::calcHorizontalLineLength()
{
    return _right_most_pixel_x__px - _left_most_pixel_x__px;
}

void XAxisL2R::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = calcHorizontalLineLength();
    rect.h = _axis_format.axisThicknessPx();
    rect.x = _x_coord__px;
    rect.y = _y_coord__px - rect.h/2;
    rects.push_back(rect);
}

void XAxisL2R::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{
    int topOfLabelYPx = _y_coord__px -
                        _axis_format.majTickLengthPx() +
                        _axis_format.tickLengthInsideChart() -
                        _axis_format.labelHeightPx();
    TextRect tr{
        _pc->getPixel(_min_val),
        topOfLabelYPx,
        std::to_string(_min_val), 
        1
    };

    SDL_Rect rect;
    rect.w = _axis_format.tickThickness();
    
    // Ticks and labels.
    int currValue = _min_val;
    int rightMostPixel__px = _pc->getValue(_right_most_pixel_x__px);

    while (currValue <= rightMostPixel__px)
    {
        int currValue__px = _pc->getPixel(currValue);
        
        if (currValue % _label_spacing == 0) // long tick with label
        {   
            rect.x =  currValue__px - ( _axis_format.tickThickness() / 2 );
            rect.h = _axis_format.majTickLengthPx();
            rect.y = _y_coord__px - 
                    ( _axis_format.majTickLengthPx() - _axis_format.tickLengthInsideChart() );
            std::string label = std::to_string(currValue);
            tr = {currValue__px, topOfLabelYPx, label, 1};
            texts.push_back(tr);
            rects.push_back(rect);
        }
        else if (currValue % _min_tick_spacing == 0) // shorter tick
        {
            rect.x =  currValue__px - ( _axis_format.tickThickness() / 2 );
            rect.h = _axis_format.minTickLengthPx();
            rect.y = _y_coord__px - ( _axis_format.minTickLengthPx() );
            rects.push_back(rect);
        }
        
        ++currValue;
    }
}

void XAxisL2R::addTitle (std::vector<TextRect>& texts)
{
    TextRect tr = {
        _left_most_pixel_x__px + (calcHorizontalLineLength()/2), //TODO width of text needs to be taken into account.
        _y_coord__px - _axis_format.getHeightOfAxisPx(),
        _title, 
        1
    };
    texts.push_back(tr);
}
