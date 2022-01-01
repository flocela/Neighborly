#ifndef PIXEL_CONVERTER_H
#define PIXEL_CONVERTER_H

class PixelConverter
{
    public:
        PixelConverter (int minVal, int minPixel, int cellSize__px); // TODO delete this doesn't work for upward y axis or right to left x axes.
        PixelConverter (int minVal, int minPixel, int maxVal, int maxPixel);
        int getPixel(int value);
        int getValue(int pixel);

    private:
        int _min_val;
        int _min_pixel;
        int _cell_size__px;

};

#endif