#ifndef AXIS_FORMAT_H
#define AXIS_FORMAT_H
#include <stdexcept>
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
        SDL_Color textColor () const { return _text_color;}
        SDL_Color textBackgroundColor () const { return _text_background_color;}

        void setLabelLetterHeight (int size);
        void setLabelSpacePx (int space);
        void setLabelWidthMultiplier (double widhtMultiplier);

        void setMajTickLengthPx (int length);
        void setMinTickLengthPx (int length);
        void setTickLengthInsideChartPx (int length);
        
        void setTextBackgroundColor (SDL_Color color);
        void setTextColor (SDL_Color color);

    private:
        int _axis_thickness__px{1};

        Letter _label_letter{22, 2, 0.3};

        int _maj_tick_length__px{10};
        int _min_tick_length__px{4};
        
        SDL_Color _text_color = {100, 100, 100, 100};
        SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};

        // _tick_length_inside_chart__px does not include thickness of axis
        int _tick_length_inside_chart__px = 2;

        
        
};

#endif