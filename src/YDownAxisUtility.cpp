#include "YDownAxisUtility.h"
#include "TextRect.h"

YDownAxisUtility::YDownAxisUtility (
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
    // set _top_most_pixel and _bottom_most_pixel
    _top_most_pixel = _y_coord__px;
    _bottom_most_pixel = _pc->getPixel(_max_val) + _end_offset__px;

    _tick_width__px = (_cell_size__px % 2 == 0) ? 2 : 1;

}

void YDownAxisUtility::top2BottomTitleOnLeft ()
{
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};

    // Vertical line is drawn as a tall horizontal rect
    SDL_Rect rect;
    rect.w = 1;
    rect.h = _bottom_most_pixel - _top_most_pixel;
    rect.x = _x_coord__px;
    rect.y = _y_coord__px;
    rects.push_back(rect);

    // Place title to the left of the center of the line.
    TextRect tr = {_x_coord__px - _title_placement_from_axis, _top_most_pixel + (rect.h/2), _title, 1};
    texts.push_back(tr);

    // All ticks have same width.
    rect.h = _tick_width__px;

    // Ticks and labels.
    int currValue = _min_val;
    while (currValue <= _pc->getValue(_bottom_most_pixel))
    {
        int currValue__px = _pc->getPixel(currValue);
        rect.y =  currValue__px - ( _tick_width__px / 2 );
        
        if (currValue % _label_spacing == 0) // ticks with labels are longer
        {   
            rect.w = _tick_length__px + 4;
            rect.x = _x_coord__px - ( _tick_length__px / 2 ) - 4;
            std::string label = std::to_string(currValue);
            tr = {rect.x - 4, currValue__px, label, 2};
            texts.push_back(tr);
            rects.push_back(rect);
        }
        else if (currValue % _tick_spacing == 0)
        {
            rect.w = _tick_length__px;
            rect.x = _x_coord__px - ( _tick_length__px / 2 );
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
