#ifndef TITLE_BASIC_H
#define TITLE_BASIC_H

#include "Color.h"
#include "Letter.h"
#include "Renderer.h"
#include "Title.h"
#include <iostream>

class Title_Basic: public Title
{

public:
    Title_Basic (
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

    Title_Basic (
        Letter letter,
        int topCenterXPx,
        int topCenterYPx,
        std::string title
    ):  _l{letter},
        _top_center_x__px{topCenterXPx}, 
        _top_center_y__px {topCenterYPx},
        _title{title}
    {}

    Title_Basic (
        Letter letter,
        std::string title
    ): _l{letter},
      _title{title}
    {}

    Title_Basic () = delete;
    Title_Basic (const Title_Basic& o) = default;
    Title_Basic (Title_Basic&& o) noexcept = default;
    Title_Basic& operator= (const Title_Basic& o) = default;
    Title_Basic& operator=(Title_Basic&& o) noexcept = default;
    ~Title_Basic () noexcept = default;

    int getLetterHeight () const override { return _l.letterHeight(); }

    int getLineSpace () const override { return _l.lineSpace(); }

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

    int sizeXPx() const override { return _title.length() * _l.letterHeight() * _l.widthMultiplier(); }

    int sizeYPx() const override { return _l.getHeightIncLSpace(); }

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