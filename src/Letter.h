#ifndef LETTER__H
#define LETTER__H

#include <stdexcept>

class Letter
{
    public:

        Letter() = default;
        Letter(int letterHeight, int lineSpace, double widthMultiplier);
        Letter (const Letter& o) = default;
        Letter (Letter&& o) noexcept = default;
        Letter& operator= (const Letter& o) = default;
        Letter& operator= (Letter&& o) = default;
        ~Letter () noexcept = default;

        int letterHeight () const {return _letter_height;}
        int lineSpace () const {return _line_space__px;}
        int getHeightIncLSpace () const { return letterHeight() + _line_space__px;}
        double widthMultiplier () const { return _width_multiplier;}
        
        void setLetterHeight (int size);
        void setLineSpace (int space);
        void setWidthMultiplier (double widthMultiplier);

    private:
    
        int _letter_height = 30;
        int _line_space__px = 2; // clear space below letter (in pixels).
        double _width_multiplier = 0.35;
};
#endif