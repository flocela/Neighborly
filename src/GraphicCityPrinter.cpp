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
    _y_axis_overrun__px = (_y_axis_overrun__px < _cell_size__px)? _cell_size__px : _y_axis_overrun__px;
    _cross_hairs_x__px = _chart_origin__px.getX() + _titles_at_left_offset__px;
    _cross_hairs_y__px = _chart_origin__px.getY() + _titles_at_top_offset__px;
    _house_min_x__px = _cross_hairs_x__px  + _x_axis_offset__px;
    _house_max_x__px = _house_min_x__px + (_house_max_x__cl - _house_min_x__cl) * _cell_size__px;
    _house_min_y__px = _cross_hairs_y__px  + _y_axis_offset__px;
    _house_max_y__px = _house_min_y__px + (_house_max_y__cl - _house_min_y__cl) * _cell_size__px;
}

void GraphicCityPrinter::printCity(std::map<House *, Resident *> houseToResMap)
{  (void) houseToResMap;
    if (!_chart_base_printed)
    {
        addCityXAxis();
        addCityYAxis();
        addTitle();
        _chart_base_printed = true;
    }
    addHouses(houseToResMap);
}

void GraphicCityPrinter::addCityXAxis()
{   
    _renderer->setColorToMedGrey();
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        12);
    if (_x_blocks.size() == 0)
    {
        initXAxisBlocks();
    }

    _renderer->fillBlocks(_x_blocks);
    _renderer->renderTexts(_x_texts);

    // TODO delete this. Just for reference.
    SDL_Rect centerBlock;

    centerBlock.w = 2;
    centerBlock.h = 2;
    centerBlock.x = _chart_origin__px.getX();
    centerBlock.y = _chart_origin__px.getY();
    _renderer->fillBlock(centerBlock);
}

void GraphicCityPrinter::addCityYAxis()
{   
    _renderer->setColorToMedGrey();
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        12);
    if (_y_blocks.size() == 0)
    {
        initYAxisBlocks();
    }
    _renderer->fillBlocks(_y_blocks);
    _renderer->renderTexts(_y_texts);
}

void GraphicCityPrinter::addTitle()
{
    int lineLength = _house_max_x__px + _x_axis_overrun__px - _cross_hairs_x__px;
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
    std::map<std::vector<int>, std::vector<Coordinate>> colorToCoordinates =
        createVectorsForEachColor(houseToResMap);
    for (auto const &colorToCoord : colorToCoordinates)
    {
        _renderer->addBlocksByColor(
            _house_size__px,
            _house_size__px,
            colorToCoord.second,
            colorToCoord.first);
    }
}

std::map<std::vector<int>, std::vector<Coordinate>> GraphicCityPrinter::createVectorsForEachColor(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<std::vector<int>, std::vector<Coordinate>> colorToCoordinatesMap = {};

    for (auto const &x : _coord_to_house_map)
    {
        Coordinate coord = x.first;
        House *house = x.second;
        std::vector<int> colorKey;
        if (houseToResMap.count(house) == 0)
        {
            // No resident has this address. So this house is empty.
            colorKey = _rgba_per_color[Color::absent];
        }
        else
        {
            Resident *res = houseToResMap[house];
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                colorKey = getUnhappyColor(res->getColor());
            else
                colorKey = getHappyColor(res->getColor());
        }
        if (colorToCoordinatesMap.count(colorKey) == 0) // TODO  c++ knows how to do this in one step
        {
            std::vector<Coordinate> newCoordinateVector = {};
            colorToCoordinatesMap[colorKey] = newCoordinateVector;
        }
        int pixelX = _house_min_x__px + (coord.getX() - _house_min_x__cl) * _cell_size__px - _house_size__px / 2;
        int pixelY = _house_min_y__px + (coord.getY() - _house_min_y__cl) * _cell_size__px - _house_size__px / 2;
        Coordinate pixelCoord{pixelX, pixelY};
        colorToCoordinatesMap[colorKey].push_back(pixelCoord);
    }
    return colorToCoordinatesMap;
}

void GraphicCityPrinter::initXAxisBlocks()
{
    // x-axis (long horizontal block)
    SDL_Rect block;
    block.w = _house_max_x__px + _x_axis_overrun__px - _cross_hairs_x__px;
    block.h = 1;
    block.x = _cross_hairs_x__px;
    block.y = _cross_hairs_y__px;
    _x_blocks.push_back(block);

    // Ticks along the x axis have same width, height and y coordinate.
    block.w = _axis_tick_width__px;
    block.h = _cell_size__px;
    block.y = _cross_hairs_y__px - _cell_size__px / 2;

    // Add tick delineating _house_min_x (the most west house).
    // Blocks are drawn from top left, not from center of the block.
    block.x = _house_min_x__px  - _axis_tick_width__px / 2;
    _x_blocks.push_back(block);

    // Add label for tick at _house_min_x, unless label overlaps with 
    // future tens values labels.
    int minXHouseToFirstTensValue = 10 - (_house_min_x__cl % 10);
    if (minXHouseToFirstTensValue > 3)
    {
        TextRect houseMinXLabel{_house_min_x__px, block.y, std::to_string(_house_min_x__cl), 1};
        _x_texts.push_back(houseMinXLabel);
    }

    // Add ticks and labels at tens values.
    int nextTick = _house_min_x__cl + minXHouseToFirstTensValue;
    int nextTickPixel = _house_min_x__px + minXHouseToFirstTensValue * _cell_size__px;
    // Blocks are drawn from top left, not from center of the block
    int nextTickBlock = nextTickPixel - _axis_tick_width__px / 2;
    int numOfBlocks = (_house_max_x__px - _house_min_x__px + _x_axis_overrun__px) /
                      _cell_size__px / 10;
    for (int ii = 0; ii < numOfBlocks; ++ii)
    {
        block.x = nextTickBlock + ii * _cell_size__px * 10;
        std::string label = std::to_string(nextTick + ii * 10);
        TextRect tr{nextTickPixel + ii * _cell_size__px * 10, block.y, label, 1};
        _x_blocks.push_back(block);
        _x_texts.push_back(tr);
    }
}

void GraphicCityPrinter::initYAxisBlocks()
{
    // y-axis (long vertical block)
    SDL_Rect block;
    block.w = 1;
    block.h = _house_max_y__px + _y_axis_overrun__px - _cross_hairs_y__px;
    block.x = _cross_hairs_x__px;
    block.y = _cross_hairs_y__px;
    _y_blocks.push_back(block);

    // Ticks along the y axis have same width, height and y coordinate.
    block.w = _cell_size__px;
    block.h = _axis_tick_width__px;
    block.x = _cross_hairs_x__px - _cell_size__px / 2;

    // Add tick delineating _house_min_y.
    // Blocks are drawn from top left, not from center of the block.
    block.y = _house_min_y__px  - _axis_tick_width__px / 2;
    _y_blocks.push_back(block);

    // Add label at _house_min_y, unless label overlaps with 
    // future tens values labels.
    int minYHouseToFirstTensValue = 10 - (_house_min_y__cl % 10);

    //if (minYHouseToFirstTensValue > 3)
    if (true)
    {   
        std::string label = std::to_string(_house_min_y__cl);
        TextRect houseMinYLabel{block.x, _house_min_y__px, label, 2};
        _x_texts.push_back(houseMinYLabel);
    }

    // Add ticks and labels for ticks at tens values.
    int nextTick = _house_min_y__cl + minYHouseToFirstTensValue;
    int nextTickPixel = _house_min_y__px + minYHouseToFirstTensValue * _cell_size__px;
    // Blocks are drawn from top left, not from center of the block
    int nextTickBlock = nextTickPixel - _axis_tick_width__px / 2;
    int numOfBlocks = (_house_max_y__px - _house_min_y__px + _y_axis_overrun__px) /
                      _cell_size__px / 10;
    for (int ii = 0; ii < numOfBlocks; ++ii)
    {
        block.y = nextTickBlock + ii * _cell_size__px * 10;
        std::string text = std::to_string(nextTick + ii * 10);
        TextRect tr{block.x, nextTickPixel + ii * _cell_size__px * 10, text, 2};
        _y_blocks.push_back(block);
        _y_texts.push_back(tr);
    }
}

std::vector<int> GraphicCityPrinter::getUnhappyColor (Color color)
{
    std::vector<int> rgba = _rgba_per_color[color];
    rgba[3] = rgba[3] - 100;
    return rgba;
}

std::vector<int> GraphicCityPrinter::getHappyColor (Color color)
{
    return _rgba_per_color[color];
}
