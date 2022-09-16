#ifndef TITLE_H
#define TITLE_H

#include "Sizer.h"
#include "Letter.h"
#include "renderer.h"

class Title : public Sizer
{

public:
    Title (Letter l): _l{l} {}
    Title (Letter l, std::string title): _l{l}, _title{title} {}
    Title (int letterHeight, int lineSpace): _l{Letter{letterHeight, lineSpace}} {}
    Title (
        int letterHeight,
        int lineSpace,
        int topCenterXPx,
        int topCenterYPx
    ): _l{Letter{letterHeight, lineSpace}}, 
       _top_center_x__px{topCenterXPx}, 
       _top_center_y__px {topCenterYPx} {}

    // returns the number of letters in the title.
    int sizeX() { return _title.length(); }

    // returns the size of the size of the title including line space below the title
    int sizeY() { return _l.getHeightIncLSpace(); }

    void setLetterHeight (int height) { _l.setLetterHeight(height);}

    // height of space below the title
    void setLineSpace (int height)  { _l.setLineSpace(height);}

    void setTitle (std::string title ) {_title = title;}

    void setTopCenter (int x, int y) {
        _top_center_x__px = x; 
        _top_center_y__px = y;
    }

    int getLetterHeight () { return _l.letterHeight(); }

    int getLineSpace () { return _l.lineSpace(); }

    void print (Renderer* renderer) {
        renderer->setTextFormats({100, 100, 100, 100},
                                 {0xAA, 0xFF, 0xFF, 0xFF},
                                 _l.letterHeight());
        renderer->renderText(_top_center_x__px, _top_center_y__px, _title, 1);
    }

private:
    Letter _l;
    int _top_center_x__px;
    int _top_center_y__px;
    std::string _title = "";

};

#endif