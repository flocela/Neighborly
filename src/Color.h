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
    yellow_neutral,
    yellow_unhappy,
    yellow_happy, 
    gray100,
    gray200,
    gray700,
    gray800,
    gray850,
    gray900
};

enum class BaseColor {red, blue, green, yellow};

enum class Mood {neutral, unhappy, happy};

std::ostream& operator<<(std::ostream& os, Color const& obj);
std::ostream& operator<<(std::ostream& os, BaseColor const& obj);
std::ostream& operator<<(std::ostream& os, Mood const& obj);

inline std::map<std::string, BaseColor> _base_colors {
    {"blue", BaseColor::blue},
    {"yellow", BaseColor::yellow},
    {"red", BaseColor::red},
    {"green", BaseColor::green}
};

inline std::vector<BaseColor> _ordered_base_colors = {
    BaseColor::blue,
    BaseColor::yellow,
    BaseColor::red,
    BaseColor::green
};

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
              //{0, 229, 255, 255} }},
              {128, 216, 255, 255} }},
        { Mood::unhappy,
            { Color::blue_unhappy,
              BaseColor::blue,
              "blue",
              Mood::unhappy,
              "unhappy",
              {2, 119, 189, 255} }}    
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
              {244, 143, 177, 255} }},
        { Mood::unhappy,
            { Color::red_unhappy, 
              BaseColor::red,
              "red",
              Mood::unhappy,
              "unhappy", 
              {183, 28, 28, 255} }}    
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
    }},
    { BaseColor::yellow, {
        { Mood::neutral, 
            { Color::yellow_neutral,
              BaseColor::yellow,
              "yellow",
              Mood::neutral,
              "neutral",
              {255, 255, 0, 255} }},
              
        { Mood::happy,
            { Color::yellow_happy,
              BaseColor::yellow,
              "yellow",
              Mood::happy,
              "happy", 
              {255, 255, 134, 255} }},
        { Mood::unhappy, 
            { Color::yellow_unhappy,
              BaseColor::yellow,
              "yellow",
              Mood::unhappy,
              "unhappy", 
              {239, 108, 0, 255} }}
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
    {Color::yellow_neutral, _colorrs_map[BaseColor::yellow][Mood::neutral].rgba},
    {Color::yellow_happy, _colorrs_map[BaseColor::yellow][Mood::happy].rgba},
    {Color::yellow_unhappy, _colorrs_map[BaseColor::yellow][Mood::unhappy].rgba},
    {Color::gray100,  {245, 245, 245, 255}},
    {Color::gray100,{238, 238, 238, 255}},
    {Color::gray200,{200, 200, 200, 220}},
    {Color::gray700,{97, 97, 97, 255}},
    {Color::gray800,{66, 66, 66, 255}},
    {Color::gray850,{50, 50, 50, 255}},
    {Color::gray900, {21, 21, 21, 255}},
};

#endif