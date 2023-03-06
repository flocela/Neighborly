#ifndef TEXT_RECT_H
#define TEXT_RECT_H

#include <string>
#include <vector>

// holds information for rendering text block
struct TextRect
{
    int _x_px; // top left corner x-pixel
    int _y_px; // top left corner y-pixel
    std::string _text;
    int _letter_height;
    double _width_multiplier;
    std::vector<uint8_t> _text_color;
    std::vector<uint8_t> _text_background_color;
    int _position; // used by renderer for final positioning of text block
};

#endif