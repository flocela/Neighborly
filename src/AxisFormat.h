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
        int tickThickness () {return _min_tick_length__px;};
        int majTickLengthPx () { return _maj_tick_length__px;};
        int minTickLengthPx () {return _min_tick_length__px;};
        int tickLengthInsideChart() {return _tick_length_inside_chart__px;};

        int titleFontSize () {return _title_font_size;};
        int titleHeightPx ();
        int titleLineSpacePx () {return _title_line_space__px;};

        int labelFontSize () {return _label_font_size;}; // these are the numbers along the axis
        int labelHeightPx ();
        int labelLineSpacePx () {return _label_line_space__px;};

        int offsetPx () {return _offset__px;};
        int overrunPx () {return _overrun__px;};

        int getHeightOfAxisPx ();

        void setMajTickLengthPx (int length);
        void setMinTickLengthPx (int length);
        void setTickLengthInsideChartPx (int length);

        void setTitleFontSize (int size);
        void setTitleLineSpacePx (int space);

        void setLabelFontSize (int size);
        void setLabelSpacePx (int space);

        void setOffsetPx (int offsetPx);
        void setOverrunPx (int overrunPx);

    private:
        // for simplicity, thicknesses can not be set. Both are one.
        int _axis_thickness__px = 1;
        int _tick_thickness__px = 1;
        int _maj_tick_length__px = 5;
        int _min_tick_length__px = 2;
        int _tick_length_inside_chart__px = 2; // does not include thickness of axis

        int _title_font_size = 12;
        int _title_line_space__px = 2; // space below letters

        int _label_font_size = 10;  
        int _label_line_space__px = 2;

        int _offset__px = 4;
        int _overrun__px = 4;
};

#endif