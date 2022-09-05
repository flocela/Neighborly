#ifndef GR_HAP_CHART_SIZER_H
#define GR_HAP_CHART_SIZER_H

#include "AxisFormat.h"
#include "Letter.h"
#include <iostream>

class GrHapChartSizer 
{
    public:
        GrHapChartSizer (
            int xSpaceLengthPx,
            int ySpaceLengthPx,
            AxisFormat axisFormatX,
            AxisFormat axisFormatY,
            Letter titleLetter,
            int minX,
            int maxX
        ): _x_space_length__px{xSpaceLengthPx},
        _y_space_length__px{ySpaceLengthPx},
        _axis_format_x{axisFormatX},
        _axis_format_y{axisFormatY},
        _title_letter{titleLetter},
        _min_x{minX},
        _max_x{maxX}
        {}

        int getXSpaceLengthPx () {return _x_space_length__px;}
        int getYSpaceLengthPx () {return _y_space_length__px;}
        AxisFormat getAxisFormatX () {return _axis_format_x;}
        AxisFormat getAxisFormatY () {return _axis_format_y;}
        Letter getTitleLetter () {return _title_letter;}
        int getMinX () {return _min_x;}
        int getMaxX () {return _max_x;}
    
    private:
        int _x_space_length__px;
        int _y_space_length__px;
        AxisFormat _axis_format_x;
        AxisFormat _axis_format_y;
        Letter _title_letter;
        int _min_x; // Run zero
        int _max_x; // Last run

};

#endif