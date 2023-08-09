#ifndef PLOT_FORMAT_H
#define PLOT_FORMAT_H

#include "AxisFormat.h"
#include "Letter.h"

class PlotFormat
{
public:
    PlotFormat (
        Letter titleLetter,
        Letter keyLetter,
        int minUnitSizePx,
        int startOffsetMultiplier,
        int endOffsetMultiplier
    ) :
       _title_letter{titleLetter},
       _key_letter{keyLetter},
       _min_unit_size__px{minUnitSizePx},
       _start_offset_m{startOffsetMultiplier},
       _end_offset_m{endOffsetMultiplier}
    {}

    PlotFormat () = delete;
    PlotFormat (const PlotFormat& o) = default;
    PlotFormat (PlotFormat&& o) noexcept = default;
    PlotFormat& operator= (const PlotFormat& o) = default;
    PlotFormat& operator=(PlotFormat&& o) noexcept = default;
    ~PlotFormat () noexcept = default;

    Letter keyLetter () { return _key_letter; }
    int keyLetterHeight () { return _key_letter.letterHeight();}
    int keyLetterHeightInclSpace () { return _key_letter.getHeightIncLSpace();}

    Letter titleLetter () { return _title_letter; }
    int titleHeight () { return _title_letter.getHeightIncLSpace();}

    int endOffsetM () { return _end_offset_m; }
    int startOffsetM () { return _start_offset_m; }
    
    int minUnitSize() { return _min_unit_size__px;}

private:
    Letter _title_letter;
    Letter _key_letter;
    int _min_unit_size__px = 1;
    
    // offsets are multipliers. length of axis before minimum value is _start_offset times _unit_size.
    int _start_offset_m;

    // offsets are multipliers. length of axis after maximum value is _end_offset times _unit_size.
    int _end_offset_m;
};

#endif