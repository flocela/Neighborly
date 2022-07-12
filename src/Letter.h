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

        void setLetterHeight (int size);
        void setLineSpace (int space);

        int letterHeight () {return _letter_height;};
        int lineSpace () {return _line_space;};
        int getHeightIncLSpace () { return letterHeight() + _line_space;}

    private:
        int _letter_height = 15;
        int _line_space = 2; // space below the letter.
};
#endif