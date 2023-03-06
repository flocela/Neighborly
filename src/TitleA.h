#ifndef TITLE_A_H
#define TITLE_A_H

#include "Color.h"
#include "Letter.h"
#include "Renderer.h"
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
        std::vector<uint8_t> textColor,
        std::vector<uint8_t> textBackgroundColor
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

    TitleA () = delete;
    TitleA (const TitleA& o) = default;
    TitleA (TitleA&& o) noexcept = default;
    TitleA& operator= (const TitleA& o) = default;
    TitleA& operator=(TitleA&& o) noexcept = default;
    ~TitleA () = default;

    int getLetterHeight () override { return _l.letterHeight(); }

    int getLineSpace () override { return _l.lineSpace(); }

    void print (Renderer* renderer) const override {
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

    int sizeXPx() { return _title.length() * _l.letterHeight() * _l.widthMultiplier(); }

    int sizeYPx() { return _l.getHeightIncLSpace(); }

    void setLetterHeight (int height) override { _l.setLetterHeight(height);}

    // height of space below the title
    void setLineSpace (int height) override { _l.setLineSpace(height);}

    void setTextColor (std::vector<uint8_t> color) override
    {
        _text_color = color;
    }

    void setTitle (std::string title) override {_title = title;}

    void setTextBackgroundColor (std::vector<uint8_t> color) override
    {
        _text_background_color = color;
    }

    void setTopCenter (int xPx, int yPx) override{
        _top_center_x__px = xPx; 
        _top_center_y__px = yPx;
    }

private:
    Letter _l;
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    std::string _title = "";
    std::vector<uint8_t> _text_color = _the_color_rgba[Color::text];
    std::vector<uint8_t> _text_background_color = _the_color_rgba[Color::text_background];

};

#endif