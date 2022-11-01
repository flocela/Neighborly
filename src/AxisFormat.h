#ifndef AXIS_FORMAT_H
#define AXIS_FORMAT_H
#include <stdexcept>

class AxisFormat
{
    public:
        AxisFormat() = default;
        AxisFormat (const AxisFormat& o) = default;
        AxisFormat (AxisFormat&& o) noexcept = default;
        AxisFormat& operator= (const AxisFormat& o) = default;
        ~AxisFormat () = default;

        int axisThicknessPx () { return _axis_thickness__px;}
        int majTickLengthPx () { return _maj_tick_length__px;}
        int minTickLengthPx () {return _min_tick_length__px;}
        int tickLengthInsideChartPx () {return _tick_length_inside_chart__px;}
        int majTickLengthOutsideChartPx () 
        {
            return _maj_tick_length__px - _tick_length_inside_chart__px;
        }
        int minTickLengthOutsideChartPx () 
        {
            return _min_tick_length__px - _tick_length_inside_chart__px;
        }

        // labels are the numbers along the axis
        int labelHeightPx () {return _label_letter_height;} 
        int labelLineSpacePx () {return _label_line_space__px;}
        double labelWidthMultiplier () {return _label_width_multiplier;}

        void setMajTickLengthPx (int length);
        void setMinTickLengthPx (int length);
        void setTickLengthInsideChartPx (int length);

        void setLabelLetterHeight (int size);
        void setLabelSpacePx (int space);
        void setLabelWidthMultiplier (double widhtMultiplier); 
    

    private:
        int _axis_thickness__px = 1;
        int _maj_tick_length__px = 10;
        int _min_tick_length__px = 4;
        // _tick_length_inside_chart__px does not include thickness of axis
        int _tick_length_inside_chart__px = 2;

        int _label_letter_height = 22;
        int _label_line_space__px = 2;
        
        // width multiplier is used when rendering the text. 
        double _label_width_multiplier = 0.3;
};

#endif