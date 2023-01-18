#ifndef LETTER_H
#define LETTER_H

#include <stdexcept>

class Letter
{
    public:
        Letter() = default;
        Letter(int letterHeight, int lineSpace, double widthMultiplier);
        Letter (const Letter& o) = default;
        Letter (Letter&& o) noexcept = default;
        Letter& operator= (const Letter& o) = default;
        ~Letter () = default;

        void setLetterHeight (int size);
        void setLineSpace (int space);
        void setWidthMultiplier (double widthMultiplier);

        int letterHeight () const {return _letter_height;}
        int lineSpace () const {return _line_space;}
        double widthMultiplier () const { return _width_multiplier;}
        int getHeightIncLSpace () const { return letterHeight() + _line_space;}

    private:
        int _letter_height = 30;
        int _line_space = 2; // clear space below letter (in pixels).
        double _width_multiplier = 0.3;
};
#endif