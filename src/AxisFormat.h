#ifndef AXIS_FORMAT__H
#define AXIS_FORMAT__H

#include <vector>
#include "Color.h"
#include "Letter.h"

class AxisFormat
{
    
public:

    int axisThicknessPx () const;

    // get major tick length
    int majTickLengthPx () const;

    // get minor tick length
    int minTickLengthPx () const; 

    int majTickLengthOutsideChartPx () const;

    int minTickLengthOutsideChartPx () const;

    int tickLengthInsideChartPx () const;

    int tickThicknessPx () const;

    // labels denote the numbers along the axis
    int labelHeightPx () const;

    int labelLineSpacePx () const;

    double labelWidthMultiplier () const;

    std::vector<uint8_t> textColor () const;
    std::vector<uint8_t> textBackgroundColor () const;
    std::vector<uint8_t> axisColor () const;
    std::vector<uint8_t> tickColor () const;
    std::vector<uint8_t> tickLineBackgroundColor () const;

    bool showBackgroundTickLines () const { return _include_background_tick_marks;}

    // Label letter height is the letter height. It will be set to 1, if size is less than 1.
    void setLabelLetterHeight (int size);

    // Label space is the space below letter. It is set to zero if space is less than 1.
    void setLabelSpacePx (int space);
    
    void setLabelWidthMultiplier (double widthMultiplier);

    // Major tick length is the longer tick length. It is set to zero if length is less than zero.
    void setMajTickLengthPx (int length);

    // Minor tick length is the shorter tick length. It is set to zero if length is less than zero.
    void setMinTickLengthPx (int length);

    // A small portion of the tick crosses to inside the chart. It is set to zero if less than zero.
    void setTickLengthInsideChartPx (int length);

    // Background lines extend beyond the tick into the chart area.
    void setBackgroundTickLines (bool show);
    
    void setTextColor (std::vector<uint8_t> color);
    void setTextBackgroundColor (std::vector<uint8_t> color);
    void setAxisColor (std::vector<uint8_t> color);
    void setTickColor (std::vector<uint8_t> color);
    void setTickLineBackgroundColor (std::vector<uint8_t> color);

private:
    int _axis_thickness__px{1};
    int _tick_thickness__px{1};

    Letter _label_letter{22, 2, 0.3};

    int _maj_tick_length__px{10};
    int _min_tick_length__px{4};

    std::vector<uint8_t> _text_color = _the_color_rgba[Color::gray200];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::gray900];
    std::vector<uint8_t> _axis_color = _the_color_rgba[Color::gray100];
    std::vector<uint8_t> _tick_color = _the_color_rgba[Color::gray100];
    std::vector<uint8_t> _tick_line_background_color = _the_color_rgba[Color::gray800];

    // _tick_length_inside_chart__px does not include thickness of axis
    int _tick_length_inside_chart__px = 2; 

    // Extend tick marks horizontally across chart.
    bool _include_background_tick_marks = false;   
};

#endif