#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <vector>
#include <map>

enum class Color { red, blue, green, absent };

inline std::map<Color, std::string> colorMap = {
    {Color::red, "red"},
    {Color::blue, "blue"},
    {Color::green, "green"},
    {Color::absent, "grey"}
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

inline std::vector<ColorInfo> _the_color_Infos = {
    {Color::red, "red", {255, 0, 0, 255}},
    {Color::blue, "blue", {0, 255, 0, 255}},
    {Color::green, "green", {0, 0, 255, 255}},
    {Color::absent, "absent", {128, 128, 128, 255}}
};

#endif