#include "AxisFormat.h"
#include <iostream>

int AxisFormat::getAxisHeightPx ()
{
    return _title_letter_height +
           _title_line_space__px +
           _label_letter_height +
           _label_line_space__px +
           (_maj_tick_length__px - _tick_length_inside_chart__px);

}

void AxisFormat::setMajTickLengthPx (int length)
{ 
    if (length < 1)
    {
        throw std::invalid_argument("maj tick length must be at least 1.");
    }
    else
    {
        _axis_thickness__px = length;
    } 
}

void AxisFormat::setMinTickLengthPx (int length)
{ 
    if (length < 1)
    {
        throw std::invalid_argument("min tick length must be at least 1.");
    }
    else
    {
        _axis_thickness__px = length;
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

void AxisFormat::setTitleLetterHeight (int size)
{ 
    _title_letter_height = size;
}

void AxisFormat::setTitleLineSpacePx (int size)
{ 
    if (size < 0)
    {
        throw std::invalid_argument("line spacing must be at least zero.");
    }
    else
    {
        _title_line_space__px = size;
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
        _label_letter_height = size;
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
        _label_line_space__px = size;
    }
}

void AxisFormat::setOffsetPx (int length)
{ 
    if (length < 0)
    {
        throw std::invalid_argument("offset must be at least zero.");
    }
    else
    {
        _offset__px = length;
    }
}

void AxisFormat::setOverrunPx (int length)
{ 
    if (length < 0)
    {
        throw std::invalid_argument("overrun must be at least zero.");
    }
    else
    {
        _overrun__px = length;
    }
}
