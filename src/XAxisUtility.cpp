#include "XAxisUtility.h"
#include "TextRect.h"

XAxisUtility::XAxisUtility (
    std::string title,
    Renderer* renderer,
    PixelConverter* pixelConverter,
    int x_coordinate__px,
    int y_coordinate__px,
    int cellSize__px,
    int minVal,
    int maxVal,
    int endOffset__px,
    int tickSpacing,
    int labelSpacing,
    int labelFontSize,
    int titleFontSize
) : _title{title},
    _renderer{renderer},
    _pc{pixelConverter},
    _x_coord__px{x_coordinate__px},
    _y_coord__px{y_coordinate__px},
    _cell_size__px{cellSize__px},
    _min_val{minVal},
    _max_val{maxVal},
    _end_offset__px{endOffset__px},
    _tick_spacing{tickSpacing},
    _label_spacing{labelSpacing},
    _label_font_size{labelFontSize},
    _title_font_size{titleFontSize}
{
    // set _left_most_pixel and _right_most_pixel
    _left_most_pixel = _x_coord__px;
    _right_most_pixel = _pc->getPixel(_max_val) + _end_offset__px;
    
    _tick_width__px = (_cell_size__px % 2 == 0) ? 2 : 1;

}

void XAxisUtility::left2RightTitleOnTop ()
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    // Horizontal line is drawn as a wide horizontal rect
    SDL_Rect rect;
    rect.w = _right_most_pixel - _left_most_pixel;
    rect.h = 1;
    rect.x = _x_coord__px;
    rect.y = _y_coord__px;
    rects.push_back(rect);

    // Place title above center of line.
    TextRect tr = {_left_most_pixel + (rect.w/2), _y_coord__px - _title_placement_from_axis, _title, 1};
    texts.push_back(tr);

    // All ticks have same width.
    rect.w = _tick_width__px;
    // Ticks and labels.
    int currValue = _min_val;
    while (currValue <= _pc->getValue(_right_most_pixel))
    {
        int currValue__px = _pc->getPixel(currValue);
        rect.x =  currValue__px - ( _tick_width__px / 2 );
        if (currValue % _label_spacing == 0) // ticks with labels are longer
        {   
            rect.h = _tick_height__px + 4;
            rect.y = _y_coord__px - ( _tick_height__px / 2 ) - 4;
            std::string label = std::to_string(currValue);
            tr = {currValue__px, rect.y - 4, label, 1};
            texts.push_back(tr);
            rects.push_back(rect);
        }
        else if (currValue % _tick_spacing == 0)
        {
            rect.h = _tick_height__px;
            rect.y = _y_coord__px - ( _tick_height__px / 2 );
            rects.push_back(rect);
        }
        
        ++currValue;
    }

    _renderer->setColorToMedGrey();
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _label_font_size);
    _renderer->fillBlocks(rects);
    _renderer->renderTexts(texts);
}
