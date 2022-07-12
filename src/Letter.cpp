#include "Letter.h"

Letter::Letter (int fontSize, int lineSpace):
    _letter_height{fontSize},
    _line_space{lineSpace}
{}

void Letter::setLetterHeight (int size)
{
    if (size < 1)
    {
        throw std::invalid_argument("font size must be at least 1.");
    }
    else
    {
        _letter_height = size;
    }
}

void Letter::setLineSpace (int space)
{
    if (space < 0)
    {
        throw std::invalid_argument("line space must be at least 0.");
    }
    else
    {
        _line_space = space;
    }
}