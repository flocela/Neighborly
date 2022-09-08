#ifndef GR_COLOR_KEY_PRINTER_H
#define GR_COLOR_KEY_PRINTER_H

#include "renderer.h"
#include "Letter.h"

// Group Color Printer
class GrColorKeyPrinter
{
    public:

    GrColorKeyPrinter() = delete;
    GrColorKeyPrinter (
        int topLeftCornerXPx,
        int topLeftCornerYPx,
        int xSpaceLengthPx,
        Letter titleLetter,
        std::unordered_map<int, BaseColor> colors, // group number to Color
        std::set<Mood> moods // keys for colors, e.g. happy, sad, neutral
    ):
        _x_offset{topLeftCornerXPx},
        _y_offset{topLeftCornerYPx},
        _x_space_length__px{xSpaceLengthPx},
        _title_letter{titleLetter},
        _colors{colors},
        _moods{moods}
    {   
        _box_length__px = _title_letter.letterHeight()/2; // box is the colored square
    }

    void print (Renderer* renderer);
    int getHeightPx ();

    private:

    int _x_offset = 0;
    int _y_offset = 0;
    int _x_space_length__px = 0;
    Letter _title_letter;
    int _box_length__px = 0;
    int _box_spacer__px = 6;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;

};

#endif