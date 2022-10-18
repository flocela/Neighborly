#include "AxisLeftToRightB.h"

AxisLeftToRightB::AxisLeftToRightB (
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
    _px_per_unit{pxPerUnit},
    _tick_thickness__px{tickThickness},
    _min_tick_spacing{calcMinTickSpacing(_px_per_unit)},
    _maj_tick_spacing{calcMajTickSpacing(_px_per_unit)},
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

void AxisLeftToRightB::print (Renderer* renderer)
{   
    std::vector<SDL_Rect> rects = {};
    std::vector<TextRect> texts = {};
    
    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->setColorToMedGrey();
    renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _axis_format.labelHeightPx()); // TODO don't set TextFormats
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}


void AxisLeftToRightB::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px,
        _y_cross__px - _axis_format.axisThicknessPx()/2,
        axisLengthPx(),
        _axis_format.axisThicknessPx(),
    };
    rects.push_back(rect);
}

int AxisLeftToRightB::calcRightMostPixelX ()
{
    int diff = _max_val - _min_val;
    return _x_cross__px + (_px_per_unit * (diff + _start_offset_m + _end_offset_m));
}

void AxisLeftToRightB::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{   
    int minXPx = _x_cross__px + _px_per_unit * _start_offset_m;
    int tickYPx = _y_cross__px - _axis_format.tickLengthInsideChart();

    int curVal = _min_val;
    int currValue__px = minXPx + (_px_per_unit * (curVal - _min_val));

    int topOfLabelYPx = 
        _y_cross__px +
        _axis_format.majTickLengthOutsideChart() +
        _axis_format.labelLineSpacePx();

    TextRect curText{
        currValue__px,
        topOfLabelYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        1
    };

    SDL_Rect majRect{
        minXPx,
        tickYPx,
        _tick_thickness__px,
        _axis_format.majTickLengthPx()
    };

    SDL_Rect minRect{
        minXPx,
        tickYPx,
        _tick_thickness__px,
        _axis_format.minTickLengthPx()
    };

    int rightMostPixel = calcRightMostPixelX();
    
    while (currValue__px <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0)
        {   
            majRect.x = currValue__px - ( _tick_thickness__px / 2 );

            curText.text = std::to_string(curVal);
            curText.xPixel = currValue__px;

            texts.push_back(curText);
            rects.push_back(majRect);
        }
        else if (curVal % _min_tick_spacing == 0)
        {   
            minRect.x = currValue__px - ( _tick_thickness__px / 2 );
            rects.push_back(minRect);
        }
        
        ++curVal;
        currValue__px = minXPx + (_px_per_unit * (curVal - _min_val));
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

}

int AxisLeftToRightB::axisLengthPx ()
{
   return calcRightMostPixelX() - _x_cross__px + 1; // TODO is this +1 correct?
}

int AxisLeftToRightB::sizeXPx ()
{
    return axisLengthPx();
}

int AxisLeftToRightB::sizeYPx ()
{
    return 
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChart() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
}
