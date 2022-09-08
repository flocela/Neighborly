#ifndef GR_CHART_A_SIZER_H
#define GR_CHART_A_SIZER_H

#include "AxisFormat.h"
#include "Letter.h"
#include <iostream>

class GrChartASizer
{
public:
    // unitX and unitY can only by 1, 10, or 100.
    GrChartASizer (
        int xSpacePx, // given space in x direction
        int ySpacePx,
        AxisFormat aFormatX,
        AxisFormat aFormatY,
        Letter titleLetter,
        Letter keyLetter,
        int minX,
        int maxX,
        int minY,
        int maxY,
        int unitX,
        int unitY,
        int dotSizePx,
        int startOffsetMultiplier,
        int endOffsetMultiplier,
        bool hasKey
    ) :_x_space__px{xSpacePx},
       _y_space__px{ySpacePx},
       _a_format_x{aFormatX},
       _a_format_y{aFormatY},
       _title_letter{titleLetter},
       _key_letter{keyLetter},
       _min_x{minX},
       _min_y{minY},
       _max_x{maxX},
       _max_y{maxY},
       _unit_x{unitX},
       _unit_y{unitY},
       _dot_size__px{dotSizePx},
       _start_offset_m{startOffsetMultiplier},
       _end_offset_m{endOffsetMultiplier
       },
       _has_key{hasKey}
    {

        if (unitX <= 0) // TODO should also check if even (see tick line thicknesses)
        {
            throw std::invalid_argument("unitX must be positive");
        }

        if (unitY <= 0)
        {
            throw std::invalid_argument("unitY must be positive");
        }

        // actual number of y pixels, not given number of y space in pixels.
        int num_y_px = 
            ((_max_y - _min_y) * _unit_y) +
            _dot_size__px * _start_offset_m +
            _dot_size__px * _end_offset_m +
            _title_letter.getHeightIncLSpace() +
            _a_format_x.getAxisHeightPx();

        num_y_px = (_has_key)? (num_y_px + _key_letter.getHeightIncLSpace()) : num_y_px;
        
        int num_x_px = 
            ((_max_x - _min_x) * _unit_x) +
            _dot_size__px * _start_offset_m +
            _dot_size__px * _end_offset_m +
            _a_format_y.getAxisHeightPx();
        
        if (num_y_px > _y_space__px)
        {
            std::cout << "GrChartASizer: num_y_px, _y_space_px: " << num_y_px << ", " << _y_space__px << std::endl;
            throw std::invalid_argument("y-axis is too large");
        }

        if (num_x_px > _x_space__px)
        {
            throw std::invalid_argument("x-axis is too large");
        }

        if (_dot_size__px % 2 == 0 )
        {
            _a_format_x.setTickThicknessPx(2);
            _a_format_y.setTickThicknessPx(2);
        }
        else
        {
            _a_format_y.setTickThicknessPx(1);
            _a_format_y.setTickThicknessPx(1);
        }
        
    }

    int xSpacePx () { return _x_space__px; }
    int ySpacePx () { return _y_space__px; }
    AxisFormat axisFormatX () { return _a_format_x; }
    AxisFormat axisFormatY () { return _a_format_y; }
    Letter titleLetter () { return _title_letter; }
    int keyLetterHeight () { return _key_letter.getHeightIncLSpace();}
    Letter keyLetter () { return _key_letter; }
    int minX () { return _min_x; }
    int minY () { return _min_y; }
    int maxX () { return _max_x; }
    int maxY () { return _max_y; }
    int unitX () { return _unit_x; }
    int unitY () { return _unit_y; }
    int dotSizePx () { return _dot_size__px; }
    int hasKey () { return _has_key; }
    int startOffsetM () { return _start_offset_m; }
    int endOffsetM () { return _end_offset_m; }

    // includes y axis height. // TODO no one uses this.
    int xAxisLength () 
    { 
        return (_unit_x * (_max_x - _min_x)) +
                _unit_x * _start_offset_m + 
                _unit_x * _end_offset_m +
               _a_format_y.getAxisHeightPx();
    }


private:
    int _x_space__px; // given space in the x direction
    int _y_space__px;
    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    Letter _title_letter;
    Letter _key_letter;
    int _min_x;
    int _min_y;
    int _max_x;
    int _max_y;
    int _unit_x;
    int _unit_y;
    int _dot_size__px;
    // Offsets are multipliers.
    // Length of axis before minimum value is _start_offset times _dot_size.
    // Length of axis after maximum value is _end_offset times _dot_size.
    int _start_offset_m; 
    int _end_offset_m;

    bool _has_key;

};


#endif