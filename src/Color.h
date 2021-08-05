#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <vector>
#include <map>

enum class Color { red, blood, blue, dark_blue, green, forrest, absent };

inline std::map<Color, std::string> colorMap = {
    {Color::red, "red"},
    {Color::blood, "blood"},
    {Color::blue, "blue"},
    {Color::dark_blue, "dark_blue"},
    {Color::green, "green"},
    {Color::forrest, "forrest"},
    {Color::absent, "grey"}
};

inline std::map<Color, Color> unhappyColorMap = {
    {Color::red, Color::blood},
    {Color::blue, Color::dark_blue},
    {Color::green, Color::forrest}
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

inline std::map<Color, std::vector<int>> _the_color_rgba = {
    {Color::red, {255, 0, 0, 255}},
    {Color::blood, {133, 0, 0, 255}},
    {Color::blue, {0, 255, 0, 255}},
    {Color::dark_blue, {0, 133, 0, 255}},
    {Color::green, {0, 0, 255, 255}},
    {Color::forrest, {0, 0, 133, 255}},
    {Color::absent,  {128, 128, 128, 255}}
};

inline std::vector<ColorInfo> _the_color_Infos = {
    {Color::red, "red", {255, 0, 0, 255}},
    {Color::blood, "blood", {255, 0, 0, 133}},
    {Color::blue, "blue", {0, 255, 0, 255}},
    {Color::dark_blue, "dark_blue", {0, 255, 0, 125}},
    {Color::green, "green", {0, 0, 255, 255}},
    {Color::forrest, "forrest", {0, 0, 133, 255}},
    {Color::absent, "absent", {128, 128, 128, 255}}
};

#endif