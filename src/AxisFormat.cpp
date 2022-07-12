#include "AxisFormat.h"
#include <iostream>

int AxisFormat::getHeightOfAxisPx ()
{
    std::cout << "AxisFormat: titleFontSize: " << titleFontSize() << std::endl;
    std::cout << "AxisFormat: labelFontSize: " << labelFontSize() << std::endl;
    std::cout << "AxisFormat: " << titleHeightPx() << " " << labelHeightPx() << std::endl;
    return titleHeightPx() +
           _title_line_space__px +
           labelHeightPx() +
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

void AxisFormat::setTitleFontSize (int size)
{ 
    _title_font_size = size;
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

void AxisFormat::setLabelFontSize (int size)
{ 
    if (size < 1)
    {
        throw std::invalid_argument("label font size must be at least 1.");
    }
    else
    {
        _label_font_size = size;
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

int AxisFormat::titleHeightPx ()
{
    return (1.75 * _title_font_size) + _title_line_space__px;
}

int AxisFormat::labelHeightPx ()
{
    return (1.75 *_label_font_size) + _label_line_space__px;
}