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
        int minUnitSizePx
    ) :
       _title_letter{titleLetter},
       _key_letter{keyLetter},
       _min_unit_size__px{minUnitSizePx}
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
    
    int minUnitSize() { return _min_unit_size__px;}

private:
    Letter _title_letter;
    Letter _key_letter;
    int _min_unit_size__px = 1;
};

#endif