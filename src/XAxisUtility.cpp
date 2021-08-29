#include "XAxisUtility.h"
#include "TextRect.h"

XAxisUtility::XAxisUtility (
    std::string title,
    Renderer* renderer,
    int x_coordinate__px,
    int y_coordinate__px,
    int cellSize__px,
    int minVal,
    int maxVal,
    int startOffset__px,
    int endOffset__px,
    int labelSpacing,
    int labelFontSize,
    int titleFontSize
) : _title{title},
    _renderer{renderer},
    _x_coord__px{x_coordinate__px},
    _y_coord__px{y_coordinate__px},
    _cell_size__px{cellSize__px},
    _min_val{minVal},
    _max_val{maxVal},
    _start_offset__px{startOffset__px},
    _end_offset__px{endOffset__px},
    _label_font_size{labelFontSize},
    _title_font_size{titleFontSize}
{
    _left_most_pixel = _x_coord__px;
    _min_val__px = _left_most_pixel + _start_offset__px;

    _pc = std::make_unique<PixelConverter>(_min_val, _min_val__px, _cell_size__px);

    _max_val__px = _pc->getPixel(_max_val);
    _right_most_pixel = _max_val__px + endOffset__px;

    if (labelSpacing < 1 || (maxVal - minVal < labelSpacing)) 
        _label_spacing = maxVal - minVal;
    
    _label_spacing = (labelSpacing < 10) ? 10 : labelSpacing;
    int diffFromFirstTickToMinVal = labelSpacing - (_min_val % labelSpacing);
    _first_tick_val = minVal + diffFromFirstTickToMinVal;
    _first_tick__px = _pc->getPixel(_first_tick_val);

    _tick_width__px = (_cell_size__px % 2 == 0) ? 2 : 1;

}

void XAxisUtility::left2RightTop ()
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

    // Ticks along the axis have same height and same y-coordinate.
    rect.w = _tick_width__px;
    rect.h = _tick_height__px;
    rect.y = _y_coord__px - ( _tick_height__px / 2 );

    // Rest of ticks.
    int currValue = _min_val;
    while (currValue <= _max_val)
    {
        int currValue__px = _pc->getPixel(currValue);
        rect.x =  currValue__px - ( _tick_width__px / 2 );
        rects.push_back(rect);
        if (currValue % _label_spacing == 0)
        {
            std::string label = std::to_string(currValue);
            TextRect tr = {currValue__px, rect.y, label, 1};
            texts.push_back(tr);
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

/*void XAxisUtility::left2RightTop ()
{   

    // Extra tick
    block.x = tickUpperLeftCornerX__px + (extraTickVal - minVal) * cellSize__px;
    
    rects.push_back(block);

    // Draw rest of ticks and labels.
    block.x = tickUpperLeftCornerX__px + (tickFirstVal - minVal) * cellSize__px;
    int currValue = tickFirstVal;
    std::cout << "currValue, maxVal, tickSpacing " << currValue << ", " << maxVal << tickSpacing << std::endl;
    while (currValue <= maxVal)
    {
        block.x = tickUpperLeftCornerX__px + (currValue - minVal) * cellSize__px;
        std::cout << "block w, h, x, y  " << block.w << ", " << block.h << ", " 
        << block.x << ", " << block.y << std::endl;
        rects.push_back(block);
        if ( (currValue - firstLabelVal) % labelSpacing)
        {
            std::string label = std::to_string(currValue);
            TextRect tr{block.x, block.y, label, 1};
            texts.push_back(tr);
        }
        currValue += tickSpacing;
    }

    renderer.setColorToMedGrey();
    renderer.setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        labelFontSize);
        renderer.fillBlocks(rects);
        renderer.renderTexts(texts);
}*/
