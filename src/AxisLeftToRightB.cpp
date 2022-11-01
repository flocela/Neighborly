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
        _axis_format.labelHeightPx());
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}


void AxisLeftToRightB::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px,
        _y_cross__px,
        axisLengthPx(),
        _axis_format.axisThicknessPx(),
    };
    rects.push_back(rect);
}

int AxisLeftToRightB::calcRightMostPixelX ()
{
    int numOfUnits = _max_val - _min_val + 1;
    return _x_cross__px + (_px_per_unit * (numOfUnits + _start_offset_m + _end_offset_m)) - 1;
}

void AxisLeftToRightB::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{   
    int curVal = _min_val;
    int curVal__px = getXPixelForPrinting(curVal) + (_px_per_unit - _tick_thickness__px)/2;

    int topOfLabelYPx = 
        _y_cross__px +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx();

    TextRect curText{
        curVal__px,
        topOfLabelYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        1
    };

    int tickYPx = _y_cross__px - _axis_format.tickLengthInsideChartPx();
    SDL_Rect majTick{
        curVal__px,
        tickYPx,
        _tick_thickness__px,
        _axis_format.majTickLengthPx()
    };

    SDL_Rect minTick{
        curVal__px,
        tickYPx,
        _tick_thickness__px,
        _axis_format.minTickLengthPx()
    };

    int rightMostPixel = calcRightMostPixelX();
    
    while (curVal__px <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0)
        {   
            majTick.x = curVal__px;

            curText.text = std::to_string(curVal);
            curText.xPixel = curVal__px;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        else if (curVal % _min_tick_spacing == 0)
        {   
            minTick.x = curVal__px;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curVal__px = getXPixelForPrinting(curVal) + (_px_per_unit - _tick_thickness__px)/2;
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
   return calcRightMostPixelX() - _x_cross__px + 1;
}

int AxisLeftToRightB::sizeXPx ()
{
    return axisLengthPx();
}

int AxisLeftToRightB::sizeYPx ()
{
    return 
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
}

int AxisLeftToRightB::calcMinTickSpacing (int pixelsPerUnit)
{
    if (_max_val - _min_val < 10)
    {
        return 1;
    }

    return (pixelsPerUnit >= 10)? 1 : 5;
}

int AxisLeftToRightB::calcMajTickSpacing (int pixelsPerUnit)
{        
    if (_max_val - _min_val < 10)
    {
        return 1;
    }
    
    return (pixelsPerUnit > 10)? 5 : 10; 
}

int AxisLeftToRightB::getXPixelForPrinting (double xVal)
{   
    int minXPx = _x_cross__px + _start_offset_m * _px_per_unit;

    return minXPx + _px_per_unit * (xVal - _min_val);
}
