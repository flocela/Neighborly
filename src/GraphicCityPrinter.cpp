#include "GraphicCityPrinter.h"
#include <iostream>

GraphicCityPrinter::GraphicCityPrinter(
    Renderer *renderer,
    std::map<Coordinate, House *> coordToHouseMap,
    std::map<Color, std::vector<int>> rgbaPerColor,
    Coordinate chartOrigin,
    int gridSize,
    int minX, 
    int maxX,
    int minY, 
    int maxY,
    int xAxisOffset,
    int yAxisOffset, 
    int xAxisOverrun,
    int yAxisOverrun,
    int titlesAtLeftOffset,
    int titlesAtTopOffset,
    int fontSize
    ) : _renderer{renderer},
        _coord_to_house_map{coordToHouseMap},
        _rgba_per_color{rgbaPerColor},
        _chart_origin__px{chartOrigin},
        _cell_size__px{gridSize},
        _house_min_x__cl{minX},
        _house_max_x__cl{maxX},
        _house_min_y__cl{minY},
        _house_max_y__cl{maxY},
        _x_axis_offset__px{xAxisOffset},
        _y_axis_offset__px{yAxisOffset},
        _x_axis_overrun__px{xAxisOverrun},
        _y_axis_overrun__px{yAxisOverrun},
        _titles_at_left_offset__px{titlesAtLeftOffset},
        _titles_at_top_offset__px{titlesAtTopOffset},
        _font_size{fontSize}
{
    _house_size__px = _cell_size__px/2;
    if (_cell_size__px % 2 != 0)
        _house_size__px++;
    _x_axis_overrun__px = (_x_axis_overrun__px < _cell_size__px)? _cell_size__px : _x_axis_overrun__px;
    _cross_hairs_x__px = _chart_origin__px.getX() + _titles_at_left_offset__px;
    _cross_hairs_y__px = _chart_origin__px.getX() + _titles_at_top_offset__px;
    _house_min_x__px = _cross_hairs_x__px  + _x_axis_offset__px;
    _house_max_x__px = _house_min_x__px + (_house_max_x__cl - _house_min_x__cl) * _cell_size__px;
}

void GraphicCityPrinter::printCity(std::map<House *, Resident *> houseToResMap)
{
    addCityXAxis();
    addCityYAxis();
    addTitle();
    addHouses(houseToResMap);
}

void GraphicCityPrinter::addCityXAxis()
{
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        12);
    if (_x_blocks.size() == 0)
    {
        initXBlocks();
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
    centerBlock.x = _chart_origin__px.getX();
    centerBlock.y = _chart_origin__px.getY();
    _renderer->fillBlock(centerBlock);
}

void GraphicCityPrinter::addCityYAxis()
{
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        12);
    if (_y_blocks.size() == 0)
    {
        int lineLength = _house_max_y__cl - _house_min_y__cl + _y_axis_offset__px + _y_axis_overrun__px;
        // orig is where x and y axes cross
        Coordinate orig{
            _chart_origin__px.getX() + _titles_at_left_offset__px,
            _chart_origin__px.getY() + _titles_at_top_offset__px};

        _renderer->setColorToMedGrey();

        // Axis line
        SDL_Rect block;
        block.w = 1;
        block.h = lineLength * _cell_size__px;
        block.x = orig.getX();
        block.y = orig.getY();
        _y_blocks.push_back(block);

        // Axis ticks
        block.w = _cell_size__px;
        block.h = _cell_size__px / 2;
        block.x = orig.getX() - _cell_size__px / 2;

        // First tick is at _min_y, which may not be at a tens value.
        int minYPixel = orig.getY() + _y_axis_offset__px;
        // firstTensDiff is difference between _min_y and first tens value
        int firstTensDiff = 10 - (_house_min_y__cl % 10);
        block.y = minYPixel - _cell_size__px / 2;
        _y_blocks.push_back(block);
        // only show _min_y number if it doesn't overlap with first tens value
        if (firstTensDiff > 3)
        {
            TextRect tr{block.x, minYPixel, std::to_string(_house_min_y__cl), 2};
            _y_texts.push_back(tr);
        }

        // Rest of ticks. They start at the first tens value.
        int nextTick = _house_min_y__cl + firstTensDiff;
        int nextTickPixel = minYPixel + firstTensDiff * _cell_size__px;
        // blocks are drawn from top left, not from center of the block
        int nextTickBlock = nextTickPixel - _cell_size__px / 2;
        int numOfBlocks = (lineLength / 10);
        for (int ii = 0; ii < numOfBlocks; ++ii)
        {
            block.y = nextTickBlock + ii * _cell_size__px * 10; // 10 grids between ticks
            std::string text = std::to_string(nextTick + ii * 10);
            TextRect tr{block.x, nextTickPixel + ii * _cell_size__px * 10, text, 2};
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

void GraphicCityPrinter::addTitle()
{
    int lineLength = (_house_max_x__cl - _house_min_x__cl + _x_axis_offset__px + _x_axis_overrun__px) * _cell_size__px;
    int x = _chart_origin__px.getX() + _titles_at_left_offset__px + lineLength / 2;
    int y = _chart_origin__px.getY();
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        24);
    _renderer->renderText(x, y, "City Map", 3);
}

void GraphicCityPrinter::addHouses(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<Color, std::vector<Coordinate>> colorToCoordinates =
        createVectorsForEachColor(houseToResMap);
    for (auto const &colorToCoord : colorToCoordinates)
    {
        Color color = colorToCoord.first;
        _renderer->addBlocksByColor(
            _house_size__px,
            _house_size__px,
            colorToCoord.second,
            _rgba_per_color[color]);
    }
}

std::map<Color, std::vector<Coordinate>> GraphicCityPrinter::createVectorsForEachColor(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<Color, std::vector<Coordinate>> colorToCoordinatesMap = {};
    // city origin is where x and y axis meet.
    Coordinate cityOrigin{
        _chart_origin__px.getX() + _titles_at_left_offset__px,
        _chart_origin__px.getY() + _titles_at_top_offset__px};
    for (auto const &x : _coord_to_house_map)
    {
        Coordinate coord = x.first;
        House *house = x.second;
        Color colorKey;
        if (houseToResMap.count(house) == 0)
        {
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {
            Resident *res = houseToResMap[house];
            colorKey = res->getColor();
        }
        if (colorToCoordinatesMap.count(colorKey) == 0) // TODO  c++ knows how to do this in one step
        {
            std::vector<Coordinate> newCoordinateVector = {};
            colorToCoordinatesMap[colorKey] = newCoordinateVector;
        }
        int pixelX = _house_min_x__px + (coord.getX() - _house_max_x__cl) * _house_size__px - _house_size__px / 2;
        int pixelY = cityOrigin.getY() + _y_axis_offset__px + (coord.getY() - _house_min_y__cl) * _cell_size__px - _house_size__px / 2;
        Coordinate pixelCoord{pixelX, pixelY};
        colorToCoordinatesMap[colorKey].push_back(pixelCoord);
    }
    return colorToCoordinatesMap;
}

void GraphicCityPrinter::initXBlocks()
{
    // x-axis (long horizontal block)
    SDL_Rect block;
    int lineLength__px = _house_max_x__px + _x_axis_overrun__px - _cross_hairs_x__px;
    block.w = lineLength__px;
    block.h = 1;
    block.x = _cross_hairs_x__px;
    block.y = _cross_hairs_y__px;
    _x_blocks.push_back(block);

    // Ticks along the x axis have same width, height and y coordinate.
    block.w = _axis_tick_width__px;
    block.h = _cell_size__px;
    block.y = _cross_hairs_y__px - _cell_size__px / 2;

    // Add _house_min_x tick.
    // Blocks are drawn from top left, not from center of the block.
    block.x = _house_min_x__px  - _axis_tick_width__px / 2;
    _x_blocks.push_back(block);

    // Add label for _house_min_x tick unless label overlaps with 
    // future tens values labels.
    int minXHouseToFirstTensValue = 10 - (_house_min_x__cl % 10);
    if (minXHouseToFirstTensValue > 3)
    {
        TextRect houseMinXLabel{_house_min_x__px, block.y, std::to_string(_house_min_x__cl), 1};
        _x_texts.push_back(houseMinXLabel);
    }

    // Rest of ticks are spaced ten cells apart.
    // And ticks at tens values have numerical labels.
    int nextTick = _house_min_x__cl + minXHouseToFirstTensValue;
    int nextTickPixel = _house_min_x__px + minXHouseToFirstTensValue * _cell_size__px;
    // Blocks are drawn from top left, not from center of the block
    int nextTickBlock = nextTickPixel - _axis_tick_width__px / 2;
    int numOfBlocks = (_house_max_x__px - _house_min_x__px + _x_axis_overrun__px) /
                      _cell_size__px / 10;
    for (int ii = 0; ii < numOfBlocks; ++ii)
    {
        block.x = nextTickBlock + ii * _cell_size__px * 10;
        std::string text = std::to_string(nextTick + ii * 10);
        TextRect tr{nextTickPixel + ii * _cell_size__px * 10, block.y, text, 1};
        _x_blocks.push_back(block);
        _x_texts.push_back(tr);
    }
}
