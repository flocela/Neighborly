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
        std::map<int, std::pair<Color,Color>> colors
    ):
        _x_offset{topLeftCornerXPx},
        _y_offset{topLeftCornerYPx},
        _x_space_length__px{xSpaceLengthPx},
        _title_letter{titleLetter},
        _colors{colors}
    {
        // just an estimate of space needed.
        _x_space_from_center = 300;
        _x_space_for_happy_label__px = _title_letter.letterHeight() * 10 / 6;
        _x_space_for_unhappy_label__px = 2 * _title_letter.letterHeight();
        _x_space_for_group_label__px = _title_letter.letterHeight() * 34 / 10;
        _box_length__px = _title_letter.letterHeight();
        
    }

    void print(Renderer* renderer);

    private:
    int _x_offset = 0;
    int _y_offset = 0;
    int _x_space_length__px = 0;
    Letter _title_letter;
    int _x_space_from_center = 0;
    int _x_space_for_happy_label__px = 0;
    int _x_space_for_unhappy_label__px = 0;
    int _x_space_for_group_label__px = 0;
    int _box_length__px = 0;
    int _box_spacer__px = 12;
    std::map<int, std::pair<Color, Color>> _colors;

};

#endif