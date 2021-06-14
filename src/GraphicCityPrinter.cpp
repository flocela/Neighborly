#include "GraphicCityPrinter.h"
#include <iostream>

void GraphicCityPrinter::printCity ()
{
    addCityXAxis();
}

void GraphicCityPrinter::addCityXAxis ()
{   
    if (xAxisBlocks.size() == 0)
    {
        std::cout << "GraphicCityPrinter: line 13" << std::endl; 
        int lineLength = _max_x - _min_x + _x_axis_offset + _x_axis_overrun;
        // xAxisOrigPixel and yAxisOrigPixel is where x and y axes cross
        int xAxisOrigPixel = _chart_origin.getX() + _titles_at_left_offset;
        int yAxisOrigPixel = _chart_origin.getY() + _titles_at_top_offset;

        _renderer->setColorToMedGrey();

        // Axis line
        SDL_Rect block;
        block.w = lineLength * _grid_size;
        block.h = 1;
        block.x = xAxisOrigPixel;
        block.y = yAxisOrigPixel;
        std::cout << "GraphicCityPrinter: " << block.w << " " << block.h << " " << block.x << " " << block.y << std::endl;
        //std::cout << "max_x, min_x, x_axis_offset"
        _renderer->fillBlock(block);
        xAxisBlocks.push_back(block);

        // Axis ticks
        block.w = _grid_size/2;
        block.h = _grid_size;
        block.y = yAxisOrigPixel - _grid_size/2;

        // First tick is at _min_x_coord, which may not be at a tens value. 
        int minXPixel = xAxisOrigPixel + _titles_at_top_offset * _grid_size;
        block.x = minXPixel - _grid_size/2;
        xAxisBlocks.push_back(block);

        // Rest of ticks. They start at the first tens value.
        int nextTick = 10 - (_min_x % 10);
        block.x = minXPixel +  nextTick * _grid_size - _grid_size/2;
        int numOfBlocks = ( lineLength / 10 );
        for (int ii=0; ii<numOfBlocks; ++ii)
        {
            block.x = block.x + ii * _grid_size * 10; // 10 grids between ticks
            xAxisBlocks.push_back(block);
        }
    }
    for (SDL_Rect block : xAxisBlocks)
    {
        _renderer->fillBlock(block);
    }
    /*
    
    _renderer.setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        fontSize
    );

    // number for first tick
    _renderer.renderText(minXPixel, block.y, std::to_string(_min_x_coord), 1);

    // number for second tick
    int nextNum = _min_x_coord + nextTick;
    _renderer.renderText(
        minXPixel + nextTick * _grid_size,
        block.y,
        std::to_string(nextNum),
        1
    );

    // numbers for rest of ticks
    int first50 = nextNum - (nextNum % 50) + 50;
    _renderer.renderNumbersHorizontally(
        minXPixel + (first50 - _min_x_coord) * _grid_size,
        block.y,
        first50,
        50,
        50 * _grid_size,
        (lineLength + _min_x_coord - first50)/50 + 1,
        1
    );*/
    
    SDL_Rect centerBlock;
    
    centerBlock.w = 2;
    centerBlock.h = 2;
    centerBlock.x = _chart_origin.getX();
    centerBlock.y = _chart_origin.getY();
    _renderer->fillBlock(centerBlock);
}