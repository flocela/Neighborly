#include "GraphicCityPrinter.h"
#include <iostream>

void GraphicCityPrinter::printCity ()
{
    addCityXAxis();
    addCityYAxis();
    addTitle();
}

void GraphicCityPrinter::addTitle()
{
    int lineLength = (_max_x - _min_x + _x_axis_offset + _x_axis_overrun) * _grid_size;
    int x = _chart_origin.getX() + _titles_at_left_offset + lineLength/2;
    int y = _chart_origin.getY();
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        24
    );
    _renderer->renderText(x, y, "City Map", 3);
}

void GraphicCityPrinter::addCityXAxis ()
{   _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        12
    );
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
        _x_blocks.push_back(block);

        // Axis ticks
        block.w = _grid_size/2;
        block.h = _grid_size;
        block.y = orig.getY() - _grid_size/2;

        // First tick is at _min_x, which may not be at a tens value. 
        int minXPixel = orig.getX() + _x_axis_offset;
        // firstTensDeiff is difference between _min_x and first tens value
        int firstTensDiff = 10 - (_min_x % 10);
        block.x = minXPixel - _grid_size/2;
        _x_blocks.push_back(block);
        // only show _min_x number if it doesn't overlap with first tens value
        if (firstTensDiff > 3)
        {
            TextRect tr{minXPixel, block.y, std::to_string(_min_x), 1};
            _x_texts.push_back(tr);
        }

        // Rest of ticks. They start at the first tens value.
        // Difference between next tick and _min_x is nextTickDiff
        
        int nextTick = _min_x + firstTensDiff;
        int nextTickPixel = minXPixel +  firstTensDiff * _grid_size;
        // blocks are drawn from top left, not from center of the block
        int nextTickBlock = nextTickPixel - _grid_size/2;
        int numOfBlocks = ( lineLength / 10 );
        for (int ii=0; ii<numOfBlocks; ++ii)
        {
            block.x = nextTickBlock + ii * _grid_size * 10; // 10 grids between ticks
            std::string text = std::to_string(nextTick + ii *10);
            TextRect tr{nextTickPixel + ii * _grid_size * 10, block.y, text, 1};
            _x_blocks.push_back(block);
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

    
    SDL_Rect centerBlock;
    
    centerBlock.w = 2;
    centerBlock.h = 2;
    centerBlock.x = _chart_origin.getX();
    centerBlock.y = _chart_origin.getY();
    _renderer->fillBlock(centerBlock);
}

void GraphicCityPrinter::addCityYAxis ()
{  
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        12
    );   
    if (_y_blocks.size() == 0)
    {
        int lineLength = _max_y - _min_y + _y_axis_offset + _y_axis_overrun;
        // orig is where x and y axes cross
        Coordinate orig{
            _chart_origin.getX() + _titles_at_left_offset,
            _chart_origin.getY() + _titles_at_top_offset
        };

        _renderer->setColorToMedGrey();

        // Axis line
        SDL_Rect block;
        block.w = 1;
        block.h = lineLength * _grid_size;
        block.x = orig.getX();
        block.y = orig.getY();
        _y_blocks.push_back(block);

        // Axis ticks
        block.w = _grid_size;
        block.h = _grid_size/2;
        block.x = orig.getX() - _grid_size/2;

        // First tick is at _min_y, which may not be at a tens value. 
        int minYPixel = orig.getY() + _y_axis_offset;
        // firstTensDiff is difference between _min_y and first tens value
        int firstTensDiff = 10 - (_min_y % 10);
        block.y = minYPixel - _grid_size/2;
        _y_blocks.push_back(block);
        // only show _min_y number if it doesn't overlap with first tens value
        if (firstTensDiff > 3)
        {
            TextRect tr{block.x, minYPixel, std::to_string(_min_y), 2};
            _y_texts.push_back(tr);
        }
        
        // Rest of ticks. They start at the first tens value.
        int nextTick = _min_y + firstTensDiff;
        int nextTickPixel = minYPixel +  firstTensDiff * _grid_size;
        // blocks are drawn from top left, not from center of the block
        int nextTickBlock = nextTickPixel - _grid_size/2;
        int numOfBlocks = ( lineLength / 10 );
        for (int ii=0; ii<numOfBlocks; ++ii)
        {
            block.y = nextTickBlock + ii * _grid_size * 10; // 10 grids between ticks
            std::string text = std::to_string(nextTick + ii *10);
            TextRect tr{block.x, nextTickPixel + ii * _grid_size * 10, text, 2};
            _y_blocks.push_back(block);
            _y_texts.push_back(tr);
        }
    }
    for (SDL_Rect block : _y_blocks)
    {
        _renderer->fillBlock(block);
    }

    for (TextRect tr : _y_texts)
    {
        _renderer->renderText(tr.xPixel, tr.yPixel, tr.text, tr.centered);
    }
    
}