#ifndef TITLE_A_H
#define TITLE_A_H

#include "Letter.h"
#include "renderer.h"
#include "Title.h"

class TitleA: public Title
{

public:
    TitleA (
        Letter letter,
        int topCenterXPx,
        int topCenterYPx,
        std::string title
    ): _l{letter}, 
       _top_center_x__px{topCenterXPx}, 
       _top_center_y__px {topCenterYPx},
       _title{title} {}

    // returns the number of letters in the title.
    int sizeXPx() { return _title.length(); }

    // returns the size of the title including line space below the title
    int sizeYPx() { return _l.getHeightIncLSpace(); }

    void setLetterHeight (int height) { _l.setLetterHeight(height);}

    // height of space below the title
    void setLineSpace (int height)  { _l.setLineSpace(height);}

    void setTitle (std::string title ) {_title = title;}

    void setTopCenter (int xPx, int yPx) override{
        _top_center_x__px = xPx; 
        _top_center_y__px = yPx;
    }

    int getLetterHeight () { return _l.letterHeight(); }

    int getLineSpace () { return _l.lineSpace(); }

    void print (Renderer* renderer) override {
        renderer->setTextFormats({100, 100, 100, 100},
                                 {0xAA, 0xFF, 0xFF, 0xFF},
                                 _l.letterHeight());
        renderer->renderText(
            _top_center_x__px,
            _top_center_y__px,
            _title,
            _l.letterHeight(),
            _l.widthMultiplier(),
            1);
    }

private:
    Letter _l;
    int _top_center_x__px = 0;
    int _top_center_y__px = 0;
    std::string _title = "";

};

#endif