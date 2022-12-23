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
    GrColorKeyPrinter() = delete;
    GrColorKeyPrinter (
        int topCenterXPx,
        int topCenterYPx,
        Letter labelSizing,
        std::unordered_map<int, BaseColor> colors, // group number to Color
        std::set<Mood> moods, // keys for colors, e.g. happy, sad, neutral
        SDL_Color textColor,
        SDL_Color textBackgroundColor
    ):
        _top_center_x__px{topCenterXPx},
        _top_center_y__px{topCenterYPx},
        _label_letter{labelSizing},
        _colors{colors},
        _moods{moods},
        _box_length__px{_label_letter.letterHeight()/2}, // box is the colored square
        _text_color{textColor},
        _text_background_color{textBackgroundColor}
    {}

    GrColorKeyPrinter (
        Letter labelLetter,
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods
    ): _label_letter{labelLetter},
       _colors{colors},
       _moods{moods},
       _box_length__px{_label_letter.letterHeight()/2}
    {}

    void print (Renderer* renderer);
    void setTopCenter (int xPx, int yPy);
    void setCharWidthMultiplier (double multiplier);
    void setTextColor (SDL_Color color);
    void setTextBackgroundColor (SDL_Color color);
    int sizeXPx () override;
    int sizeYPx () override;
    
private:
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    Letter _label_letter;
    std::unordered_map<int, BaseColor> _colors;
    std::set<Mood> _moods;
    int _box_length__px = 0;
    int _box_spacer__px = 6;
    int _column_border__px = 15;

    SDL_Color _text_color = {100, 100, 100, 100};
	SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};

};

#endif