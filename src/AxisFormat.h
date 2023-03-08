#ifndef AXIS_FORMAT_H
#define AXIS_FORMAT_H
#include <stdexcept>
#include <vector>
#include "Color.h"
#include "SDL.h"
#include "Letter.h"

class AxisFormat
{
    public:

        int axisThicknessPx () const { return _axis_thickness__px;}
        int majTickLengthPx () const { return _maj_tick_length__px;}
        int minTickLengthPx () const {return _min_tick_length__px;}
        int majTickLengthOutsideChartPx () const;
        int minTickLengthOutsideChartPx () const;
        int tickLengthInsideChartPx () const {return _tick_length_inside_chart__px;}

        // labels are the numbers along the axis
        int labelHeightPx () const {return _label_letter.letterHeight();} 
        int labelLineSpacePx () const {return _label_letter.lineSpace();}
        double labelWidthMultiplier () const {return _label_letter.widthMultiplier();}
        std::vector<uint8_t> textColor () const { return _text_color;}
        std::vector<uint8_t> textBackgroundColor () const { return _text_background_color;}
        std::vector<uint8_t> tickColor () const { return _tick_color;}
        std::vector<uint8_t> tickBackgroundColorMaj () const { return _tick_background_color_maj;}
        std::vector<uint8_t> tickBackgroundColorMin () const { return _tick_background_color_min;}

        bool showBackgroundTickLines () const { return _include_background_tick_marks;}

        void setLabelLetterHeight (int size);
        void setLabelSpacePx (int space);
        void setLabelWidthMultiplier (double widhtMultiplier);

        void setMajTickLengthPx (int length);
        void setMinTickLengthPx (int length);
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