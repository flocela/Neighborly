
#include "Color.h"


std::ostream& operator<<(std::ostream& os, Color const& obj)
{ 
    std::string colorString;

    switch (obj)
    {
        case Color::green:
            colorString = "green";
            break;
        case Color::red:
            colorString = "red";
            break;
        case Color::blue:
            colorString = "blue";
            break;
        default:
            colorString = "unknown";
            break;
    }
    os << colorString;
    return os;
}