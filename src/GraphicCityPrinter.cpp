#include "GraphicCityPrinter.h"
#include <iostream>

void GraphicCityPrinter::printCity ()
{
    addCityXAxis();
}

void GraphicCityPrinter::addCityXAxis ()
{   
    if (_x_blocks.size() == 0)
    {
        int lineLength = _max_x - _min_x + _x_axis_offset + _x_axis_overrun;
        // orig is where x and y axes cross
        Coordinate orig{
            _chart_origin.getX() + _titles_at_left_offset,
            _chart_origin.getY() + _titles_at_top_offset
        };

        _renderer->setColorToMedGrey();

        // Axis line
        SDL_Rect block;
        block.w = lineLength * _grid_size;
        block.h = 1;
        block.x = orig.getX();
        block.y = orig.getY();
        _renderer->fillBlock(block);
        _x_blocks.push_back(block);

        // Axis ticks
        block.w = _grid_size/2;
        block.h = _grid_size;
        block.y = orig.getY() - _grid_size/2;

        // First tick is at _min_x_coord, which may not be at a tens value. 
        int minXPixel = orig.getX() + _x_axis_offset;
        block.x = minXPixel - _grid_size/2;
        _x_blocks.push_back(block);
        TextRect tr{minXPixel, block.y, std::to_string(_min_x), 1};
        _x_texts.push_back(tr);

        // Rest of ticks. They start at the first tens value.
        // Difference between next Tick and _min_x is nextTickDiff
        int nextTickDiff = 10 - (_min_x % 10);

        int nextTick = _min_x + nextTickDiff;
        int nextTickPixel = minXPixel +  nextTickDiff * _grid_size;
        // blocks are drawn from top left, not from center of the block
        int nextTickBlock = nextTickPixel - _grid_size/2;
        int numOfBlocks = ( lineLength / 10 );
        for (int ii=0; ii<numOfBlocks; ++ii)
        {
            block.x = nextTickBlock + ii * _grid_size * 10; // 10 grids between ticks
            _x_blocks.push_back(block);
            std::string text = std::to_string(nextTick + ii *10);
            TextRect tr{nextTickPixel + ii * _grid_size * 10, block.y, text, 1};
            _x_texts.push_back(tr);
        }
    }
    for (SDL_Rect block : _x_blocks)
    {
        _renderer->fillBlock(block);
    }

    for (TextRect tr : _x_texts)
    {
        _renderer->renderText(tr.xPixel, tr.yPixel, tr.text, tr.centered);
    }
    
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _font_size
    );
/*
    // number for first tick
    _renderer->renderText(minXPixel, block.y, std::to_string(_min_x_coord), 1);

    // number for second tick
    int nextNum = _min_x_coord + nextTick;
    _renderer->renderText(
        minXPixel + nextTick * _grid_size,
        block.y,
        std::to_string(nextNum),
        1
    );

    // numbers for rest of ticks
    int first50 = nextNum - (nextNum % 50) + 50;
    _renderer->renderNumbersHorizontally(
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