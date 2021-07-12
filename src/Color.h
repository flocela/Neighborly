#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <vector>

enum class Color { red, blue, green, absent };

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