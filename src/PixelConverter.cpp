#include "PixelConverter.h"

PixelConverter::PixelConverter (
    int minVal,
    int minPixel,
    int cellSize__px
): _min_val{minVal}, _min_pixel{minPixel}, _cell_size__px{cellSize__px}
{}

PixelConverter::PixelConverter (
    int minVal,
    int minPixel,
    int maxVal,
    int maxPixel
) : _min_val{minVal}, _min_pixel{minPixel}, _cell_size__px{(maxPixel - minPixel) / (maxVal - minVal)}
{}


int PixelConverter::getPixel(int value)
{
    int diff = value - _min_val;
    return _min_pixel + (diff * _cell_size__px);
}

int PixelConverter::getValue(int pixel)
{
    return _min_val + ( ( pixel - _min_pixel ) /_cell_size__px );
}