#ifndef GR_COLOR_KEY_PRINTER_H
#define GR_COLOR_KEY_PRINTER_H

#include "renderer.h"
#include "Letter.h"
#include "ColorKey.h"
#include "SDL.h"

// Group Color Printer
class GrColorKeyPrinter : public ColorKey
{
    public:

    GrColorKeyPrinter(); // TODO delete default constructor
    GrColorKeyPrinter (
        int topCenterXPx,
        int topCenterYPx,
        Letter labelLetter,
        std::unordered_map<int, BaseColor> colors, // group number to Color
        std::set<Mood> moods // keys for colors, e.g. happy, sad, neutral
    ):
        _top_center_x__px{topCenterXPx},
        _top_center_y__px{topCenterYPx},
        _label_letter{labelLetter},
        _colors{colors},
        _moods{moods}
    {   
        _box_length__px = _label_letter.letterHeight()/2; // box is the colored square
    }

    void print (Renderer* renderer);
    int sizeXPx () override;
    int sizeYPx () override { return _label_letter.getHeightIncLSpace(); }
    void setCharWidthMultiplier (double multiplier) { _char_width_multiplier = multiplier;}

    void setTopCenter (int xPx, int yPx) {
        _top_center_x__px = xPx;
        _top_center_y__px = yPx;
    }

    private:

    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    int _column_border__px = 15;
    Letter _label_letter;
    int _box_length__px = 0;
    int _box_spacer__px = 6;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;

    // only used to find sizeX()
    // determines the width of each letter based on the height of each letter.
    double _char_width_multiplier = .3;
    std::vector<int> textColor = {100, 100, 100, 100}; // TODO maybe remove
	std::vector<int> textBackgroundColor = {0xAA, 0xFF, 0xFF, 0xFF}; // TODO maybe remove

};

#endif