#include "Color.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, Color const& obj)
{ 
    string colorString;
    switch (obj)
    {
        case Color::red_neutral:
            colorString = _colorrs_map[BaseColor::red][Mood::neutral].toString();
            break;
        case Color::red_unhappy:
            colorString = _colorrs_map[BaseColor::red][Mood::unhappy].toString();
            break;
        case Color::red_happy:
            colorString = _colorrs_map[BaseColor::red][Mood::happy].toString();
            break;
        case Color::blue_neutral:
            colorString = _colorrs_map[BaseColor::blue][Mood::neutral].toString();
            break;
        case Color::blue_unhappy:
            colorString = _colorrs_map[BaseColor::blue][Mood::unhappy].toString();
            break;
        case Color::blue_happy:
            colorString = _colorrs_map[BaseColor::blue][Mood::happy].toString();
            break;
        case Color::green_neutral:
            colorString = _colorrs_map[BaseColor::green][Mood::neutral].toString();
            break;
        case Color::green_unhappy:
            colorString = _colorrs_map[BaseColor::green][Mood::unhappy].toString();
            break;
        case Color::green_happy:
            colorString = _colorrs_map[BaseColor::green][Mood::happy].toString();
            break;
        case Color::yellow_neutral:
            colorString = _colorrs_map[BaseColor::yellow][Mood::neutral].toString();
            break;
        case Color::yellow_unhappy:
            colorString = _colorrs_map[BaseColor::yellow][Mood::unhappy].toString();
            break;
        case Color::yellow_happy:
            colorString = _colorrs_map[BaseColor::yellow][Mood::happy].toString();
            break;
        default:
            colorString = "unknown";
            break;
    }
    os << colorString;
    return os;
}

ostream& operator<<(ostream& os, BaseColor const& obj)
{ 
    string colorString;

    switch (obj)
    {
        case BaseColor::green:
            colorString = "green";
            break;
        case BaseColor::blue:
            colorString = "blue";
            break;
        case BaseColor::red:
            colorString = "red";
            break;
        case BaseColor::yellow:
        colorString = "yellow";
        break;
        default:
            colorString = "unknown";
            break;
    }
    os << colorString;
    return os;
}