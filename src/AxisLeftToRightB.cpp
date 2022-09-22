#include "AxisLeftToRightB.h"

AxisLeftToRightB::AxisLeftToRightB (
    std::string title,
    AxisFormat axisFormat,
    int xCrossPx,
    int yCrossPx,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) : _title{title},
    _axis_format{axisFormat},
    _x_cross__px{xCrossPx},
    _y_cross__px{yCrossPx},
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
{
    
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


void AxisLeftToRightB::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = calcRightMostPixelX() - _x_cross__px;
    rect.h = _axis_format.axisThicknessPx();
    rect.x = _x_cross__px;
    rect.y = _y_cross__px - rect.h/2;

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
    int rightMostPixel = calcRightMostPixelX();
    int minValPx = _x_cross__px + _px_per_unit * _start_offset_m;
    int currValue__px = minValPx + (_px_per_unit * (currValue - _min_val));
    while (currValue__px <= rightMostPixel)
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
        currValue__px = minValPx + (_px_per_unit * (currValue - _min_val));
    }
}

void AxisLeftToRightB::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisLeftToRightB::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);
    _label_spacing = calcLabelSpacing(_px_per_unit);

}
