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

        int axisThicknessPx () { return _axis_thickness__px;};
        int tickThickness () {return _tick_thickness__px;};
        int majTickLengthPx () { return _maj_tick_length__px;};
        int minTickLengthPx () {return _min_tick_length__px;};
        int tickLengthInsideChart() {return _tick_length_inside_chart__px;};

        int titleHeightPx (){return _title_letter_height;}
        int titleLineSpacePx () {return _title_line_space__px;};

        int labelHeightPx () {return _label_letter_height;} // these are the numbers along the axis
        int labelLineSpacePx () {return _label_line_space__px;};

        int offsetPx () {return _offset__px;};
        int overrunPx () {return _overrun__px;};

        int getAxisHeightPx ();

        void setMajTickLengthPx (int length);
        void setMinTickLengthPx (int length);
        void setTickLengthInsideChartPx (int length);

        void setTitleLetterHeight (int height);
        void setTitleLineSpacePx (int space);

        void setLabelLetterHeight (int size);
        void setLabelSpacePx (int space);

        void setOffsetPx (int offsetPx);
        void setOverrunPx (int overrunPx);

    private:
        // for simplicity, thicknesses can not be set. Both are one.
        int _axis_thickness__px = 1;
        int _tick_thickness__px = 2;
        int _maj_tick_length__px = 10;
        int _min_tick_length__px = 2;
        int _tick_length_inside_chart__px = 2; // does not include thickness of axis

        int _title_letter_height = 22;
        int _title_line_space__px = 2; // space below letters

        int _label_letter_height = 22;  
        int _label_line_space__px = 2;

        int _offset__px = 20;
        int _overrun__px = 20;
};

#endif