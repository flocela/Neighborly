#include "AxisFormat.h"

void AxisFormat::setMajTickLengthPx (int length)
{ 
    _maj_tick_length__px = length;
}

void AxisFormat::setMinTickLengthPx (int length)
{ 
    if (length < 1)
    {
        throw std::invalid_argument("min tick length must be at least 1.");
    }
    else
    {
        _min_tick_length__px = length;
    }
}

void AxisFormat::setTickLengthInsideChartPx (int length)
{ 
    if (length < 1)
    {
        throw std::invalid_argument("tick length inside chart must be at least 0.");
    }
    else if (length >= _maj_tick_length__px)
    {
        throw std::invalid_argument("tick length inside of chart can't be smaller than whole length of tick");
    }
    else
    {
        _tick_length_inside_chart__px = length;
    }
}


void AxisFormat::setLabelLetterHeight (int size)
{ 
    if (size < 1)
    {
        throw std::invalid_argument("label font size must be at least 1.");
    }
    else
    {
        _label_letter.setLetterHeight(size);
    }
}

void AxisFormat::setLabelSpacePx (int size)
{ 
    if (size < 0)
    {
        throw std::invalid_argument("line spacing must be at least zero.");
    }
    else
    {
        _label_letter.setLineSpace(size);
    }
}

void AxisFormat::setLabelWidthMultiplier (double widthMultiplier)
{
    _label_letter.setWidthMultiplier(widthMultiplier);
}

void AxisFormat::setTextColor (SDL_Color color)
{
    _text_color = color;
}
        
void AxisFormat::setTextBackgroundColor (SDL_Color color)
{
    _text_background_color = color;
}
