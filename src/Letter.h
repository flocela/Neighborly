#ifndef LETTER_H
#define LETTER_H

#include <stdexcept>

class Letter
{
    public:
        Letter() = default;
        Letter(int fontSize, int lineSpace);
        Letter (const Letter& o) = default;
        Letter (Letter&& o) noexcept = default;
        Letter& operator= (const Letter& o) = default;
        ~Letter () = default;

        void setFontSize (int size);
        void setLineSpace (int space);

        int fontSize () {return _font_size;};
        int letterHeight () {return _font_size;};
        int lineSpace () {return _line_space;};
        int getHeightIncLSpace () { return letterHeight() + _line_space;}

    private:
        int _font_size = 12;
        int _line_space = 2; // space below the letter.
};
#endif