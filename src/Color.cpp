
#include "Color.h"

// TODO check Color.h operator <<
std::ostream& operator<<(std::ostream& os, Color const& obj)
{ 
    std::string colorString;

    switch (obj)
    {
        case Color::green_neutral:
            colorString = "green_neutral";
            break;
        case Color::green_unhappy:
            colorString = "green_unhappy";
            break;
        case Color::red_neutral:
            colorString = "red_neutral";
            break;
        case Color::red_unhappy:
            colorString = "red_unhappy";
            break;
        case Color::blue_neutral:
            colorString = "blue_neutral";
            break;
        case Color::blue_unhappy:
            colorString = "blue_unhappy";
            break;
        default:
            colorString = "unknown";
            break;
    }
    os << colorString;
    return os;
}