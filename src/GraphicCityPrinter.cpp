#include "GraphicCityPrinter.h"
#include <iostream>

GraphicCityPrinter::GraphicCityPrinter(
    Renderer* renderer,
    std::map<Coordinate, House*> coordToHouseMap,
    int crossHairsX,
    int crossHairsY,
    std::set<Color> resColors,
    int cellSize,
    int tickSpacingX,
    int tickSpacingY,
    int tickWidthPx,
    int axesWidthPx,
    int labelSpacingX,
    int labelSpacingY,
    int minX,
    int maxX,
    int minY,
    int maxY,
    int xAxisOffset,
    int yAxisOffset,
    int xAxisOverrun,
    int yAxisOverrun,
    int fontSizeTickLabels,
    int fontSizeKeyLabels,
    int fontSizeTitle
    ) : _renderer{renderer},
        _coord_to_house_map{coordToHouseMap},
        _cross_hairs_x__px{crossHairsX},
        _cross_hairs_y__px{crossHairsY},
        _res_colors{resColors},
        _cell_size__px{cellSize},
        _tick_spacing_x{tickSpacingX},
        _tick_spacing_y{tickSpacingY},
        _tick_width__px{tickWidthPx},
        _axes_width__px{axesWidthPx},
        _label_spacing_x{labelSpacingX},
        _label_spacing_y{labelSpacingY},
        _house_min_x{minX},
        _house_max_x{maxX},
        _house_min_y{minY},
        _house_max_y{maxY},
        _x_axis_offset__px{xAxisOffset},
        _y_axis_offset__px{yAxisOffset},
        _x_axis_overrun__px{xAxisOverrun},
        _y_axis_overrun__px{yAxisOverrun},
        _font_size_axes_tick_labels{fontSizeTickLabels},
        _font_size_key{fontSizeKeyLabels},
        _font_size_title{fontSizeTitle}
        
{  
    _pixel_converter_x = std::make_unique<PixelConverter>(
        _house_min_x,
        _cross_hairs_x__px + _x_axis_offset__px,
        _cell_size__px
    );
    _pixel_converter_y = std::make_unique<PixelConverter>(
        _house_min_y,
        _cross_hairs_y__px + _y_axis_offset__px,
        _cell_size__px
    );

    _house_min_x__px = _pixel_converter_x->getPixel(_house_min_x);
    _house_min_y__px = _pixel_converter_y->getPixel(_house_min_y);
    _house_max_x__px = _pixel_converter_x->getPixel(_house_max_x);
    _house_max_y__px = _pixel_converter_x->getPixel(_house_max_y);
    _house_size__px = (_cell_size__px % 2 == 0) ? 
        _cell_size__px / 2 : _cell_size__px / 2 + 1;

    _title_y__px = _cross_hairs_y__px + (_house_max_y__px - _house_min_y__px) / 20;

    // TODO may not be necessary to have overrun larger than cell size. House will 
    // fit into allotted size of axis.
    //_x_axis_overrun__px = (_x_axis_overrun__px < _cell_size__px)? _cell_size__px : _x_axis_overrun__px;
    //_y_axis_overrun__px = (_y_axis_overrun__px < _cell_size__px)? _cell_size__px : _y_axis_overrun__px;
    addCityXAxis();
    addCityYAxis();
    addTitle();
    printLegend();
}


void GraphicCityPrinter::printCity(std::map<House *, Resident *> houseToResMap)
{  (void) houseToResMap; // TODO why do I have a (void) here?
    _x_axis_utility->left2RightTitleOnTop();
    _y_axis_utility->top2BottomTitleOnLeft();
    printHouses(houseToResMap);
}

void GraphicCityPrinter::addCityXAxis()
{   
    _x_axis_utility = std::make_unique<XAxisUtility>(
        "xAxis",
        _renderer,
        _pixel_converter_x.get(),
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _cell_size__px,
        _house_min_x,
        _house_max_x,
        _x_axis_overrun__px,
        _tick_spacing_x,
        _label_spacing_x,
        _font_size_axes_tick_labels,
        _font_size_key
    );
}

void GraphicCityPrinter::addCityYAxis()
{   
    _y_axis_utility = std::make_unique<YDownAxisUtility>(
        "yAxis",
        _renderer,
        _pixel_converter_y.get(),
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _cell_size__px,
        _house_min_y,
        _house_max_y,
        _y_axis_overrun__px,
        _tick_spacing_y,
        _label_spacing_y,
        _font_size_axes_tick_labels,
        _font_size_key
    );
}

void GraphicCityPrinter::addTitle()
{   
    int x = _cross_hairs_x__px - _titles_at_left_offset__px;
    // Place Title a little below top of map (divide by 20).
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _font_size_title);
    _renderer->renderText(x, _title_y__px, "City Map", 4);
}

void GraphicCityPrinter::printHouses(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<Color, std::vector<Coordinate>> colorToCoordinates =
        createVectorsForEachColor(houseToResMap);
    for (auto const &colorToCoord : colorToCoordinates)
    {
        _renderer->addBlocksByColor(
            _house_size__px,
            _house_size__px,
            colorToCoord.second,
            _the_color_infos[colorToCoord.first].rgba);
    }
}

void GraphicCityPrinter::printLegend ()
{   
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _font_size_key);
    int x = _cross_hairs_x__px - _titles_at_left_offset__px;
    int y = _title_y__px + _dist_from_title_to_legend;
    
    for (Color color : _res_colors)
    {   
        _renderer->addBlock(
            _font_size_key,
            _font_size_key,
            Coordinate{x, y + (_font_size_key/2)},
            _the_color_infos[color].rgba
        );
        _renderer->renderText(x + (2 * _font_size_key), y, _the_color_infos[color]._my_string, 4);
        y = y + (4 * _font_size_key);
    }
}

std::map<Color, std::vector<Coordinate>> GraphicCityPrinter::createVectorsForEachColor(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<Color, std::vector<Coordinate>> colorToCoordinatesMap = {};

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
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                colorKey = _unhappy_color_map[res->getColor()];
            else
                colorKey = res->getColor();
        }
        if (colorToCoordinatesMap.count(colorKey) == 0) // TODO  c++ knows how to do this in one step
        {
            std::vector<Coordinate> newCoordinateVector = {};
            colorToCoordinatesMap[colorKey] = newCoordinateVector;
        }
        int pixelsX = _pixel_converter_x->getPixel(coord.getX()) - _house_size__px / 2;
        int pixelsY = _pixel_converter_y->getPixel(coord.getY()) - _house_size__px / 2;
        Coordinate pixelCoord{pixelsX, pixelsY};
        colorToCoordinatesMap[colorKey].push_back(pixelCoord);
    }
    return colorToCoordinatesMap;
}

void GraphicCityPrinter::initXAxisBlocks()
{/*
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
    int minXHouseToFirstTensValue = 10 - (_house_min_x % 10);
    if (minXHouseToFirstTensValue > 3)
    {
        TextRect houseMinXLabel{_house_min_x__px, block.y, std::to_string(_house_min_x), 1};
        _x_texts.push_back(houseMinXLabel);
    }

    // Add ticks and labels at tens values.
    int nextTick = _house_min_x + minXHouseToFirstTensValue;
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
    }*/
}

void GraphicCityPrinter::initYAxisBlocks()
{/*
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
    int minYHouseToFirstTensValue = 10 - (_house_min_y % 10);

    //if (minYHouseToFirstTensValue > 3)
    if (true)
    {   
        std::string label = std::to_string(_house_min_y);
        TextRect houseMinYLabel{block.x, _house_min_y__px, label, 2};
        _x_texts.push_back(houseMinYLabel);
    }

    // Add ticks and labels for ticks at tens values.
    int nextTick = _house_min_y + minYHouseToFirstTensValue;
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
    }*/
}
