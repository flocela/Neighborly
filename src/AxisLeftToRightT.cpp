#include "AxisLeftToRightT.h"

AxisLeftToRightT::AxisLeftToRightT (
    AxisFormat axisFormat,
    int xCrossPx,
    int yCrossPx,
    int minVal,
    int maxVal,
    int pxPerUnit,
    int tickThickness,
    int startOffsetMultiplier,
    int endOffsetMultiplier
) :
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

void AxisLeftToRightT::print (Renderer* renderer)
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


void AxisLeftToRightT::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect;
    rect.w = calcRightMostPixelX() - _x_cross__px;
    rect.h = _axis_format.axisThicknessPx();
    rect.x = _x_cross__px;
    rect.y = _y_cross__px - rect.h/2;

    rects.push_back(rect);
}

void AxisLeftToRightT::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{  
    int topOfLabelYPx = _y_cross__px -
                        _axis_format.majTickLengthPx() + _axis_format.tickLengthInsideChart() - // TODO make this one value I can get from axis format
                        _axis_format.labelLineSpacePx();
    TextRect tr;
    SDL_Rect tick;
    tick.w = _tick_thickness__px;
    int majTickYPx = 
        _y_cross__px -
        _axis_format.majTickLengthPx() +
        _axis_format.tickLengthInsideChart();
    int minTickYPx = 
        _y_cross__px -
        _axis_format.minTickLengthPx() +
        _axis_format.tickLengthInsideChart();
    
    // Todo should put ending label on last maj tick mark.
    // Ticks and labels.
    int currValue = _min_val;
    int rightMostPixel = calcRightMostPixelX();
    int minValPx = _x_cross__px + _px_per_unit * _start_offset_m;
    int currValue__px = minValPx + (_px_per_unit * (currValue - _min_val));
    while (currValue__px <= rightMostPixel)
    {  
        if (currValue % _label_spacing == 0) // major tick with label
        { 
            tick.h = _axis_format.majTickLengthPx();
            tick.x =  currValue__px - ( _tick_thickness__px / 2 );
            tick.y = majTickYPx;
                
            std::string label = std::to_string(currValue);
            tr = {currValue__px, topOfLabelYPx, label, 5};
            texts.push_back(tr);
        }
        else if (currValue % _min_tick_spacing == 0) // minor tick
        {   
            tick.h = _axis_format.minTickLengthPx();
            tick.x =  currValue__px - ( _tick_thickness__px / 2 );
            tick.y = minTickYPx;
        }
        
        rects.push_back(tick);
        ++currValue;
        currValue__px = minValPx + (_px_per_unit * (currValue - _min_val));
    }
}

void AxisLeftToRightT::moveCrossHairs (int xPx, int yPx)
{
    _x_cross__px = xPx;
    _y_cross__px = yPx;
}

void AxisLeftToRightT::setPxPerUnit (int pixels)
{
    _px_per_unit = pixels;
    _min_tick_spacing = calcMinTickSpacing(_px_per_unit);
    _maj_tick_spacing = calcMajTickSpacing(_px_per_unit);
    _label_spacing = calcLabelSpacing(_px_per_unit);

}
