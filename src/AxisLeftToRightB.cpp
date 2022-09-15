#include "AxisLeftToRightB.h"

AxisLeftToRightB::AxisLeftToRightB (
    std::string title,
    AxisFormat axisFormat,
    int xCrossPx,
    int yCrossPx,
    int minVal,
    int maxVal,
    int majTickSpacing,
    int minTickSpacing,
    int labelSpacing,
    int startOffset,
    int endOffset,
    int pxPerUnit
) : _title{title},
    _axis_format{axisFormat},
    _x_cross__px{xCrossPx},
    _y_cross__px{yCrossPx},
    _zero__px{_x_cross__px + startOffset},
    _min_val{minVal},
    _max_val{maxVal},
    _min_tick_spacing{minTickSpacing},
    _maj_tick_spacing{majTickSpacing},
    _label_spacing{labelSpacing},
    _start_offset__px{startOffset},
    _end_offset__px{endOffset},
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{_px_per_unit%2==0? 2 : 1}
{
    _left_most_pixel_x__px = _x_cross__px;
    _right_most_pixel_x__px = 
        _x_cross__px +
        _start_offset__px +
        _px_per_unit * (_max_val - _min_val) +
        _end_offset__px;
}

void AxisLeftToRightB::print (Renderer* renderer)
{   
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick lables are in texts vector.
    std::vector<TextRect> texts = {};
    
    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx());
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}

int AxisLeftToRightB::calcHorizontalLineLength()
{
    return _right_most_pixel_x__px - _left_most_pixel_x__px;
}

void AxisLeftToRightB::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = calcHorizontalLineLength();
    rect.h = _axis_format.axisThicknessPx();
    rect.x = _x_cross__px;
    rect.y = _y_cross__px - rect.h/2;
    
    //rect.w = 1000;
    //rect.h = 5;
    //rect.x = 30;
    //rect.y = 30;

    rects.push_back(rect);
}

void AxisLeftToRightB::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{   
    int topOfLabelYPx = _y_cross__px +
                        _axis_format.majTickLengthPx() -_axis_format.tickLengthInsideChart() +
                        _axis_format.labelLineSpacePx();
    TextRect tr;
    SDL_Rect rect;
    rect.w = _tick_thickness__px;
    // Todo should put ending label on last maj tick mark.
    // Ticks and labels.
    int currValue = _min_val;
    int currValue__px = _zero__px + (_px_per_unit * (currValue - _min_val));
    while (currValue__px <= _right_most_pixel_x__px)
    {  
        if (currValue % _label_spacing == 0) // long tick with label
        {   
            rect.x =  currValue__px - ( _tick_thickness__px / 2 );
            rect.h = _axis_format.majTickLengthPx();
            rect.y = _y_cross__px - _axis_format.tickLengthInsideChart();
            std::string label = std::to_string(currValue);
            tr = {currValue__px, topOfLabelYPx, label, 1};
            texts.push_back(tr);
            rects.push_back(rect);
        }
        else if (currValue % _min_tick_spacing == 0) // shorter tick
        {   
            rect.x =  currValue__px - ( _tick_thickness__px / 2 );
            rect.h = _axis_format.minTickLengthPx();
            rect.y = _y_cross__px + _axis_format.axisThicknessPx();
            rects.push_back(rect);
        }
        
        ++currValue;
        currValue__px = _zero__px + (_px_per_unit * (currValue - _min_val));
    }
}

void AxisLeftToRightB::addTitle (std::vector<TextRect>& texts)
{
    TextRect tr = {
        _left_most_pixel_x__px + (calcHorizontalLineLength()/2), //TODO width of text needs to be taken into account.
        _y_cross__px - _axis_format.getAxisHeightPx(),
        _title, 
        4
    };
    texts.push_back(tr);
}
