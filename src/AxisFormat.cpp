#include "AxisFormat.h"

#include <iostream>

using namespace std;

int AxisFormat::axisThicknessPx () const { return _axis_thickness__px;}

int AxisFormat::majTickLengthPx () const { return _maj_tick_length__px;}

int AxisFormat::minTickLengthPx () const {return _min_tick_length__px;}

int AxisFormat::tickLengthInsideChartPx () const {return _tick_length_inside_chart__px;}

int AxisFormat::labelHeightPx () const {return _label_letter.letterHeight();} 

int AxisFormat::labelLineSpacePx () const {return _label_letter.lineSpace();}

double AxisFormat::labelWidthMultiplier () const {return _label_letter.widthMultiplier();}

vector<uint8_t> AxisFormat::textColor () const { return _text_color;}

vector<uint8_t> AxisFormat::textBackgroundColor () const { return _text_background_color;}

vector<uint8_t> AxisFormat::axisColor () const {return _axis_color;}

vector<uint8_t> AxisFormat::tickColor () const { return _tick_color;}

vector<uint8_t> AxisFormat::tickLineBackgroundColor () const { return _tick_line_background_color;}

int AxisFormat::majTickLengthOutsideChartPx () const
{
    return _maj_tick_length__px - _tick_length_inside_chart__px - axisThicknessPx();
}

int AxisFormat::minTickLengthOutsideChartPx () const
{
    return _min_tick_length__px - _tick_length_inside_chart__px - axisThicknessPx();
}

void AxisFormat::setLabelLetterHeight (int size)
{ 
    size = (size < 1)? 1 : size;
    _label_letter.setLetterHeight(size);
}

void AxisFormat::setLabelSpacePx (int size)
{ 
    size = (size < 0)? 0 : size;
    _label_letter.setLineSpace(size);
}

void AxisFormat::setLabelWidthMultiplier (double widthMultiplier)
{
    _label_letter.setWidthMultiplier(widthMultiplier);
}

void AxisFormat::setMajTickLengthPx (int length)
{ 
    _maj_tick_length__px = (length < 0)? 0 : length;
}

void AxisFormat::setMinTickLengthPx (int length)
{ 
    _min_tick_length__px = (length < 0)? 0 : length;
}

void AxisFormat::setTickLengthInsideChartPx (int length)
{ 
    _tick_length_inside_chart__px = (length < 0)? 0 : length;
}

void AxisFormat::setBackgroundTickLines (bool show)
{
    _include_background_tick_marks = show;
}

void AxisFormat::setTextColor (vector<uint8_t> color)
{
    _text_color = color;
}
        
void AxisFormat::setTextBackgroundColor (vector<uint8_t> color)
{
    _text_background_color = color;
}

void AxisFormat::setAxisColor (std::vector<uint8_t> color)
{
    _axis_color = color;
}

void AxisFormat::setTickColor (vector<uint8_t> color)
{
    _tick_color = color;
}

void AxisFormat::setTickLineBackgroundColor (vector<uint8_t> color)
{
    _tick_line_background_color = color;
}