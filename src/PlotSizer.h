#ifndef PLOT_SIZER_H
#define PLOT_SIZER_H

#include "AxisFormat.h"
#include "Letter.h"
#include <iostream>

class PlotSizer
{
public:
    // unitX and unitY can only by 1, 10, or 100. // TODO why can it only be these values?
    PlotSizer (
        AxisFormat aFormatX,
        AxisFormat aFormatY,
        Letter titleLetter,
        Letter keyLetter,
        int minUnitSizePx,
        int startOffsetMultiplier,
        int endOffsetMultiplier,
        bool hasKey
    ) :
       _a_format_x{aFormatX},
       _a_format_y{aFormatY},
       _title_letter{titleLetter},
       _key_letter{keyLetter},
       _min_unit_size__px{minUnitSizePx},
       _start_offset_m{startOffsetMultiplier},
       _end_offset_m{endOffsetMultiplier
       },
       _has_key{hasKey}
    {}

    AxisFormat axisFormatX () { return _a_format_x; }
    AxisFormat axisFormatY () { return _a_format_y; }
    int axisFormatYHeight () { return _a_format_y.getAxisSizePx();}
    Letter titleLetter () { return _title_letter; }
    int titleHeight () { return _title_letter.getHeightIncLSpace();}
    int keyLetterHeightInclSpace () { return _key_letter.getHeightIncLSpace();}
    int keyLetterHeight () { return _key_letter.letterHeight();}
    Letter keyLetter () { return _key_letter; }
    int hasKey () { return _has_key; }
    int startOffsetM () { return _start_offset_m; }
    int endOffsetM () { return _end_offset_m; }
    int minUnitSize() { return _min_unit_size__px;}

    int maxNumOfXDiff () { return 100;}
    int maxNumOfYDiff () { return 20;}

private:
    AxisFormat _a_format_x;
    AxisFormat _a_format_y;
    Letter _title_letter;
    Letter _key_letter;
    int _min_unit_size__px;
    // Offsets are multipliers.
    // Length of axis before minimum value is _start_offset times _dot_size.
    // Length of axis after maximum value is _end_offset times _dot_size.
    int _start_offset_m; 
    int _end_offset_m;

    bool _has_key;

};


#endif