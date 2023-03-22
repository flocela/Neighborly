#ifndef AXIS_FORMAT_H
#define AXIS_FORMAT_H
#include <vector>
#include "Color.h"
#include "Letter.h"

class AxisFormat
{
public:

    int axisThicknessPx () const;
    int majTickLengthPx () const;
    int minTickLengthPx () const;
    int majTickLengthOutsideChartPx () const;
    int minTickLengthOutsideChartPx () const;
    int tickLengthInsideChartPx () const;

    // labels are the numbers along the axis
    int labelHeightPx () const;
    int labelLineSpacePx () const;
    double labelWidthMultiplier () const;
    std::vector<uint8_t> textColor () const;
    std::vector<uint8_t> textBackgroundColor () const;
    std::vector<uint8_t> tickColor () const;
    std::vector<uint8_t> tickBackgroundColorMaj () const;
    std::vector<uint8_t> tickBackgroundColorMin () const;

    bool showBackgroundTickLines () const { return _include_background_tick_marks;}

    // label letter height will be set to 1, if size is less than 1.
    void setLabelLetterHeight (int size);

    // label space, space below letter, is set to zero if space is less than 1.
    void setLabelSpacePx (int space);
    void setLabelWidthMultiplier (double widthMultiplier);

    // maj tick length is set to zero if length is less than zero.
    void setMajTickLengthPx (int length);

    // min tick length is set to zero if length is less than zero.
    void setMinTickLengthPx (int length);

    // tick length inside chart is set to zero if less than zero.
    void setTickLengthInsideChartPx (int length);

    void setBackgroundTickLines (bool show);
    
    void setTextBackgroundColor (std::vector<uint8_t> color);
    void setTextColor (std::vector<uint8_t> color);
    void setTickColor (std::vector<uint8_t> color);
    void setTickBackgroundColorMaj (std::vector<uint8_t> color);
    void setTickBackgroundColorMin (std::vector<uint8_t> color);

private:
    int _axis_thickness__px{1};

    Letter _label_letter{22, 2, 0.3};

    int _maj_tick_length__px{10};
    int _min_tick_length__px{4};

    std::vector<uint8_t> _text_color = _the_color_rgba[Color::text];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::text_background];
    std::vector<uint8_t> _tick_color = _the_color_rgba[Color::grid];
    std::vector<uint8_t> _tick_background_color_maj = _the_color_rgba[Color::tick_background_maj];
    std::vector<uint8_t> _tick_background_color_min = _the_color_rgba[Color::tick_background_min];

    // _tick_length_inside_chart__px does not include thickness of axis
    int _tick_length_inside_chart__px = 2; 

    // extend tick marks horizontally across chart
    bool _include_background_tick_marks = false;   
};

#endif