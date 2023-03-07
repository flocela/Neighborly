#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <map>
#include <set>
#include <unordered_map>

enum class Color { 
    red_neutral, 
    red_unhappy, 
    red_happy, 
    blue_neutral, 
    blue_unhappy, 
    blue_happy, 
    green_neutral, 
    green_unhappy, 
    green_happy, 
    absent,
    grid,
    text,
    text_background,
    background,
    tick_background_maj,
    tick_background_min
};

enum class BaseColor {red, blue, green};

enum class Mood {neutral, unhappy, happy};

std::ostream& operator<<(std::ostream& os, Color const& obj);
std::ostream& operator<<(std::ostream& os, BaseColor const& obj);

inline std::unordered_map<std::string, BaseColor> _base_colors {
    {"red", BaseColor::red},
    {"blue", BaseColor::blue},
    {"green", BaseColor::green}
};

inline BaseColor baseColor (std::string baseColor)
{
    if (baseColor == "red")
    {
        return BaseColor::red;
    }
    else if (baseColor == "blue")
    {
        return BaseColor::blue;
    }
    else {
        return BaseColor::green;
    }
}

struct ColorInfo
{
    Color _color;
    BaseColor _base_color;
    std::string _base_name;
    Mood _mood;
    std::string _mood_name;
    std::vector<uint8_t> rgba;

    std::string toString() { return _base_name + "_" + _mood_name;}
};

// TODO for red green color blindness, change green to yellow.
inline std::unordered_map<BaseColor, std::unordered_map<Mood,ColorInfo>> _colorrs_map {
    { BaseColor::blue, { 
        { Mood::neutral, 
            { Color::blue_neutral, 
              BaseColor::blue, 
              "blue",
              Mood::neutral, 
              "neutral", 
              {41, 182, 246, 255} }},
        { Mood::happy,
            { Color::blue_happy,
              BaseColor::blue,
              "blue",
              Mood::happy,
              "happy", 
              {0, 229, 255, 255} }},
        { Mood::unhappy,
            { Color::blue_unhappy,
              BaseColor::blue,
              "blue",
              Mood::unhappy,
              "unhappy",
              {1, 87, 155, 255} }}    
    }},
    { BaseColor::red, { 
        { Mood::neutral, 
            { Color::red_neutral,
              BaseColor::red,
              "red",
              Mood::neutral, 
              "neutral", 
              {244, 67, 54, 255} }},
        { Mood::happy,
            { Color::red_happy,
              BaseColor::red,
              "red",
              Mood::happy, 
              "happy", 
              {255, 64, 129, 255} }},
        { Mood::unhappy,
            { Color::red_unhappy, 
              BaseColor::red,
              "red",
              Mood::unhappy,
              "unhappy", 
              {198, 40, 40, 255} }}    
    }},
    { BaseColor::green, {
        { Mood::neutral, 
            { Color::green_neutral,
              BaseColor::green,
              "green",
              Mood::neutral,
              "neutral", 
              {46, 125, 50, 255} }},
        { Mood::happy,
            { Color::green_happy,
              BaseColor::green,
              "green",
              Mood::happy,
              "happy", 
              {118, 255, 3, 255} }},
        { Mood::unhappy, 
            { Color::green_unhappy,
              BaseColor::green,
              "green",
              Mood::unhappy,
              "unhappy", 
              {27, 94, 32, 255} }}
    }}
};

inline std::map<Color, std::vector<uint8_t>> _the_color_rgba = {
    {Color::red_neutral, _colorrs_map[BaseColor::red][Mood::neutral].rgba},
    {Color::red_happy, _colorrs_map[BaseColor::red][Mood::happy].rgba},
    {Color::red_unhappy, _colorrs_map[BaseColor::red][Mood::unhappy].rgba},
    {Color::blue_neutral, _colorrs_map[BaseColor::blue][Mood::neutral].rgba},
    {Color::blue_happy, _colorrs_map[BaseColor::blue][Mood::happy].rgba},
    {Color::blue_unhappy, _colorrs_map[BaseColor::blue][Mood::unhappy].rgba},
    {Color::green_neutral, _colorrs_map[BaseColor::green][Mood::neutral].rgba},
    {Color::green_happy, _colorrs_map[BaseColor::green][Mood::happy].rgba},
    {Color::green_unhappy, _colorrs_map[BaseColor::green][Mood::unhappy].rgba},
    {Color::absent,  {40, 40, 40, 255}},
    {Color::grid,{210, 215, 211, 255}},
    //{Color::text,{236, 240, 241, 255}},
    //{Color::text_background,{108, 122, 137}},
    {Color::text,{200, 200, 200, 220}},
    {Color::text_background,{20, 20, 20, 255}},
    {Color::background,{105, 105, 105, 255}},
    {Color::tick_background_maj, {40, 40, 40, 255}},
    {Color::tick_background_min, {20, 20, 20, 255}},
};

#endif