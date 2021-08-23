#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <vector>
#include <map>
#include <set>

enum class Color { red, red_sad, blue, blue_sad, green, green_sad, absent };

inline std::map<Color, Color> _unhappy_color_map = {
    {Color::red, Color::red_sad},
    {Color::blue, Color::blue_sad},
    {Color::green, Color::green_sad}
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
    Color::red,
    Color::blue,
    Color::green
};

inline std::map<Color, std::vector<int>> _the_color_rgba = {
    {Color::red, {255, 0, 0, 255}},
    {Color::red_sad, {133, 0, 0, 255}},
    {Color::blue, {0, 255, 0, 255}},
    {Color::blue_sad, {0, 133, 0, 255}},
    {Color::green, {0, 0, 255, 255}},
    {Color::green_sad, {0, 0, 133, 255}},
    {Color::absent,  {128, 128, 128, 255}}
};

inline std::map<Color, ColorInfo> _the_color_Infos = {
    {Color::red, {Color::red, "red", {255, 0, 0, 255}}},
    {Color::red_sad, {Color::red_sad, "red_sad", {255, 0, 0, 133}}},
    {Color::blue, {Color::blue, "blue", {0, 255, 0, 255}}},
    {Color::blue_sad, {Color::blue_sad, "blue_sad", {0, 255, 0, 125}}},
    {Color::green, {Color::green, "green", {0, 0, 255, 255}}},
    {Color::green_sad, {Color::green_sad, "green_sad", {0, 0, 133, 255}}},
    {Color::absent, {Color::absent, "absent", {128, 128, 128, 255}}}
};

#endif