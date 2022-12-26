#ifndef TITLE_A_H
#define TITLE_A_H

#include "Letter.h"
#include "renderer.h"
#include "Title.h"
#include <iostream>

class TitleA: public Title
{

public:
    TitleA (
        Letter letter,
        int topCenterXPx,
        int topCenterYPx,
        std::string title,
        SDL_Color textColor,
        SDL_Color textBackgroundColor
    ): _l{letter}, 
       _top_center_x__px{topCenterXPx}, 
       _top_center_y__px {topCenterYPx},
       _title{title},
       _text_color{textColor},
       _text_background_color{textBackgroundColor}
    {}

    TitleA (
        Letter letter,
        int topCenterXPx,
        int topCenterYPx,
        std::string title
    ):  _l{letter},
        _top_center_x__px{topCenterXPx}, 
        _top_center_y__px {topCenterYPx},
        _title{title}
    {}

    TitleA (
        Letter letter,
        std::string title
    ): _l{letter},
      _title{title}
    {}

    int sizeXPx() { return _title.length() * _l.letterHeight() * _l.widthMultiplier(); }

    int sizeYPx() { return _l.getHeightIncLSpace(); }

    void setLetterHeight (int height) { _l.setLetterHeight(height);}

    // height of space below the title
    void setLineSpace (int height)  { _l.setLineSpace(height);}

    void setTitle (std::string title ) {_title = title;}

    void setTopCenter (int xPx, int yPx) override{
        _top_center_x__px = xPx; 
        _top_center_y__px = yPx;
    }

    void setTextColor (SDL_Color color) 
    {
        _text_color = color;
    }

    void setTextBackgroundColor (SDL_Color color)
    {
        _text_background_color = color;
    }

    int getLetterHeight () { return _l.letterHeight(); }

    int getLineSpace () { return _l.lineSpace(); }

    void print (Renderer* renderer) override {
        renderer->renderText(
            _top_center_x__px,
            _top_center_y__px,
            _title,
            _l.letterHeight(),
            _l.widthMultiplier(),
            _text_color,
            _text_background_color,
            1);
    }

private:
    Letter _l;
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    std::string _title = "";
    SDL_Color _text_color = {100, 100, 100, 100};
    SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};

};

#endif