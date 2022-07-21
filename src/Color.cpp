
#include "Color.h"


std::ostream& operator<<(std::ostream& os, Color const& obj)
{ 
    std::string colorString;

    switch (obj)
    {
        case Color::green:
            colorString = "green";
            break;
        case Color::green_sad:
            colorString = "green_sad";
            break;
        case Color::red:
            colorString = "red";
            break;
        case Color::red_sad:
            colorString = "red_sad";
            break;
        case Color::blue:
            colorString = "blue";
            break;
        case Color::blue_sad:
            colorString = "blue_sad";
            break;
        default:
            colorString = "unknown";
            break;
    }
    os << colorString;
    return os;
}