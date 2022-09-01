#ifndef COLOR_H
#define COLOR_H

#include <ostream>
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
    absent
};

// TODO for red green color blindness, change green to yellow.
inline std::unordered_map<Color, std::unordered_map<std::string, Color>> _color_map{
    { Color::blue_neutral, { {"neutral", Color::blue_neutral}, {"unhappy", Color::blue_unhappy}, {"happy", Color::blue_happy} } },
    { Color::red_neutral, { {"neutral", Color::red_neutral}, {"unhappy", Color::red_unhappy}, {"happy", Color::red_happy} } },
    { Color::green_neutral, { {"neutral", Color::green_neutral}, {"unhappy", Color::green_unhappy}, {"happy", Color::green_happy} } },
};

inline std::map<Color, Color> _unhappy_color_map {
    {Color::red_neutral, Color::red_unhappy},
    {Color::blue_neutral, Color::blue_unhappy},
    {Color::green_neutral, Color::green_unhappy}
};

std::ostream& operator<<(std::ostream& os, Color const& obj);

struct ColorInfo
{
    Color _my_color;
    std::string _my_string;
    std::vector<int> rgba;
    //std::ostream& toStream (std::ostream& ost) const;
};

/*
std::ostream& operator<< (std::ostream& ost, const ColorInfo& c)
{
    return c.toStream(ost);
}*/

inline std::set<Color> _base_colors = {
    Color::red_neutral,
    Color::blue_neutral,
    Color::green_neutral
};

inline std::map<Color, std::vector<int>> _the_color_rgba = {
    {Color::red_neutral, {244, 67, 54, 255}},
    {Color::red_happy, {255, 64, 129, 255}},
    {Color::red_unhappy, {198, 40, 40, 255}},
    {Color::blue_neutral, {41, 182, 246, 255}},
    {Color::blue_happy, {0, 229, 255, 255}},
    {Color::blue_unhappy, {1, 87, 155, 255}},
    {Color::green_neutral, {46, 125, 50, 255}},
    {Color::green_happy, {118, 255, 3, 255}},
    {Color::green_unhappy, {27, 94, 32, 255}},
    {Color::absent,  {60, 60, 60, 255}}
};

inline std::unordered_map<Color, ColorInfo> _the_color_infos = {
    {Color::red_neutral, {Color::red_neutral, "red_neutral", {244, 67, 54, 255}}},
    {Color::red_happy, {Color::red_happy, "red_happy", {255, 64, 129, 255}}},
    {Color::red_unhappy, {Color::red_unhappy, "red_unhappy", {198, 40, 40, 255}}},
    {Color::blue_neutral, {Color::blue_neutral, "blue_neutral", {41, 182, 246, 255}}},
    {Color::blue_happy, {Color::blue_happy, "blue_happy", {0, 229, 255, 255}}},
    {Color::blue_unhappy, {Color::blue_unhappy, "blue_unhappy", {1, 87, 155, 255}}},
    {Color::green_neutral, {Color::green_neutral, "green_neutral", {46, 125, 50, 255}}},
    {Color::green_happy, {Color::green_happy, "green_happy", {118, 255, 3, 255}}},
    {Color::green_unhappy, {Color::green_unhappy, "green_unhappy", {27, 94, 32, 255}}},
    {Color::absent, {Color::absent, "absent", {60, 60, 60, 255}}}
};

#endif