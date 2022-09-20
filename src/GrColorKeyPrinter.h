#ifndef GR_COLOR_KEY_PRINTER_H
#define GR_COLOR_KEY_PRINTER_H

#include "renderer.h"
#include "Letter.h"
#include "ColorKey.h"

// Group Color Printer
class GrColorKeyPrinter : public ColorKey
{
    public:

    GrColorKeyPrinter(); // TODO delete default constructor
    GrColorKeyPrinter (
        int topLeftCornerXPx,
        int topLeftCornerYPx,
        int xSpaceLengthPx,
        Letter titleLetter,
        std::unordered_map<int, BaseColor> colors, // group number to Color
        std::set<Mood> moods // keys for colors, e.g. happy, sad, neutral
    ):
        _top_left_x__px{topLeftCornerXPx},
        _top_left_y__px{topLeftCornerYPx},
        _x_space_length__px{xSpaceLengthPx},
        _title_letter{titleLetter},
        _colors{colors},
        _moods{moods}
    {   
        _box_length__px = _title_letter.letterHeight()/2; // box is the colored square
    }

    void print (Renderer* renderer);
    int getHeightPx () { return _title_letter.getHeightIncLSpace(); }

    void setTopLeftCorner (int xPx, int yPx) {
        _top_left_x__px = xPx;
        _top_left_y__px = yPx;
    }

    private:

    int _top_left_x__px = 0;
    int _top_left_y__px = 0;
    int _x_space_length__px = 0;
    Letter _title_letter;
    int _box_length__px = 0;
    int _box_spacer__px = 6;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;

};

#endif