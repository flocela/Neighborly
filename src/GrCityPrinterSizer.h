#ifndef GR_CITY_PRINTER_SIZER_H
#define GR_CITY_PRINTER_SIZER_H

#include "AxisFormat.h"
#include "Letter.h"

// Used to determine how large the cell sizes will be in the GrCityPrinter.
// Also is taken as an argument in the GrCityPrinter
class GrCityPrinterSizer 
{   
    public:

        GrCityPrinterSizer (
            int xSpaceLengthPx,
            int ySpaceLengthPx,
            AxisFormat axisFormatX,
            AxisFormat axisFormatY,
            Letter titleLetter,
            int minX, // minimum x value for a house. (most west house)
            int maxX, // maximum x value for a house. (most east house)
            int minY, // minimum y value for a house. (most north house)
            int maxY // maximum y value for a house. (most south house)
        ): _x_space_length__px{xSpaceLengthPx},
           _y_space_length__px{ySpaceLengthPx},
           _axis_format_x{axisFormatX},
           _axis_format_y{axisFormatY},
           _title_letter{titleLetter},
           _min_x{minX},
           _max_x{maxX},
           _min_y{minY},
           _max_y{maxY}
        {}

        int getXSpaceLengthPx () {return _x_space_length__px;}
        int getYSpaceLengthPx () {return _y_space_length__px;}
        AxisFormat getAxisFormatX () {return _axis_format_x;}
        AxisFormat getAxisFormatY () {return _axis_format_y;}
        Letter getTitleLetter () {return _title_letter;}
        int getMinX () {return _min_x;}
        int getMaxX () {return _max_x;}
        int getMinY () {return _min_y;}
        int getMaxY () {return _max_y;}

    private:
        int _x_space_length__px;
        int _y_space_length__px;
        AxisFormat _axis_format_x;
        AxisFormat _axis_format_y;
        Letter _title_letter;
        int _min_x; // coordinate x-value of west most house
        int _max_x; // coordinate x-value of east most house
        int _min_y; // coordinate y-value of north most house
        int _max_y; // coordiante y-value of south most house
};

#endif