#include "PixelConverter.h"

PixelConverter::PixelConverter (
    int minVal,
    int minPixel,
    int cellSize__px
): _min_val{minVal}, _min_pixel{minPixel}, _cell_size__px{cellSize__px}
{}

int PixelConverter::getPixel(int value)
{
    int diff = value - _min_val;
    return _min_pixel + (diff * _cell_size__px);
}