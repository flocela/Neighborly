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
    _start_offset_m{startOffsetMultiplier},
    _end_offset_m{endOffsetMultiplier}
{}

void AxisLeftToRightT::print (Renderer* renderer)
{   
    // All lines and ticks are drawn as SDL_Rects, which are held in rects vector.
    std::vector<SDL_Rect> rects = {};
    // Tick labels are in texts vector.
    std::vector<TextRect> texts = {};
    
    addHorizontalLine(rects);
    addTicksAndLabels(rects, texts);

    renderer->setColorToMedGrey();
    renderer->fillBlocks(rects);
    renderer->renderTexts(texts);
}


void AxisLeftToRightT::addHorizontalLine (std::vector<SDL_Rect>& rects)
{
    SDL_Rect rect{
        _x_cross__px,
        _y_cross__px,
        axisLengthPx(),
        _axis_format.axisThicknessPx()
    };

    rects.push_back(rect);
}

void AxisLeftToRightT::addTicksAndLabels (
    std::vector<SDL_Rect>& rects, 
    std::vector<TextRect>& texts
)
{   
    int curVal = _min_val;
    int curVal__px = getPixel(curVal) -(_tick_thickness__px/2);

    int botOfLabelYPx = 
        _y_cross__px -
        _axis_format.majTickLengthOutsideChartPx() -
        _axis_format.labelLineSpacePx();

    TextRect curText{
        curVal__px,
        botOfLabelYPx,
        std::to_string(curVal),
        _axis_format.labelHeightPx(),
        _axis_format.labelWidthMultiplier(),
        _axis_format.textColor(),
        _axis_format.textBackgroundColor(),
        5
    };

    int majTickYPx = _y_cross__px - _axis_format.majTickLengthOutsideChartPx();
    int minTickYPx = _y_cross__px - _axis_format.minTickLengthOutsideChartPx();
    
    SDL_Rect majTick{
        curVal__px,
        majTickYPx,
        _tick_thickness__px,
        _axis_format.majTickLengthPx()
    };

    SDL_Rect minTick{
        curVal__px,
        minTickYPx,
        _tick_thickness__px,
        _axis_format.minTickLengthPx()
    };
    
    int rightMostPixel = calcRightMostPixelWithValue_X();
    
    while (curVal__px <= rightMostPixel)
    {  
        if (curVal % _maj_tick_spacing == 0) // major tick with label
        { 
            majTick.x = curVal__px;
                
            curText._text = std::to_string(curVal);
            curText._x_pixel = curVal__px;

            texts.push_back(curText);
            rects.push_back(majTick);
        }
        else if (curVal % _min_tick_spacing == 0) // minor tick
        {   
            minTick.x = curVal__px;
            rects.push_back(minTick);
        }
        
        ++curVal;
        curVal__px = getPixel(curVal) - (_tick_thickness__px)/2;
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
}

void AxisLeftToRightT::setTickThickness (int tickThicknessPx)
{
    _tick_thickness__px = tickThicknessPx;
}

int AxisLeftToRightT::axisLengthPx ()
{
    int unit_px_odd = (_px_per_unit%2==0)? 0 : 1;
    // tick may be at edge of horizontal axis, so 1/2 of tick will hang off the end.
    return calcRightMostPixelWithValue_X() - _x_cross__px - unit_px_odd + (_tick_thickness__px/2);
}

int AxisLeftToRightT::sizeXPx ()
{
    return axisLengthPx();
}

int AxisLeftToRightT::sizeYPx ()
{
    return 
        _axis_format.axisThicknessPx() +
        _axis_format.majTickLengthOutsideChartPx() +
        _axis_format.labelLineSpacePx() +
        _axis_format.labelHeightPx();
}

int AxisLeftToRightT::calcRightMostPixelWithValue_X ()
{
    return _x_cross__px + (_px_per_unit * ( _diff + _start_offset_m + _end_offset_m));
}

int AxisLeftToRightT::calcMinTickSpacing (int pixelsPerUnit)
{ 
    return (pixelsPerUnit >= 10)? 1 : 5; 
}
        
int AxisLeftToRightT::calcMajTickSpacing (int pixelsPerUnit)
{ 
    return (pixelsPerUnit > 10)? 5 : 10; 
}

int AxisLeftToRightT::calcLabelSpacing (int pixelsPerUnit)
{ 
    return (pixelsPerUnit > 10)? 5 : 10; 
}

int AxisLeftToRightT::getPixel (double xVal)
{   
    int minXPx = _x_cross__px + _start_offset_m * _px_per_unit;

    return minXPx + _px_per_unit * (xVal - _min_val);
}

int AxisLeftToRightT::centerValXPx ()
{
    // the max value that is shown on the axis will be _max_val plus _end_offfset_m
    return getPixel(_min_val + ((_max_val + _end_offset_m - _min_val)/2.0) );
}