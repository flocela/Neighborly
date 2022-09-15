#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisL2RTop.h"
#include "YAxisT2B.h"

Printer_Graphic::Printer_Graphic (
    std::string title,
    std::unordered_map<int, BaseColor> colors,
    std::unordered_map<const House*, Coordinate > coordPerHouse,
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int numOfRuns
)
{
    if (colors.size() > 2)
        throw(std::invalid_argument("Printer Graphic only prints two types of residents."));

    // TODO minx and miny may not be at zero
    // TODO max x and maxy may not be the same value
    std::vector<int> minsAndMaxCoords = determineMinMaxHouseCoords(coordPerHouse);
    if (minsAndMaxCoords[1] > 110 || minsAndMaxCoords[3] > 110)
         throw(std::invalid_argument("Max x and max y coordinates must be < 110."));

    int maxNumOfNeighbors = determineMaxNumberOfNeighbors(neighbors);
    if (_max_number_of_neighbors > 12)
        throw(std::invalid_argument("Can't print more than 12 neighbors."));

    // TODO what really is the max number of runs?
    std::cout << "PrinterGraphic numOfRuns: " << numOfRuns << std::endl;
    if (numOfRuns > 200) 
        throw(std::invalid_argument("Can't print more than 100 runs."));

    _colors = colors;

    _num_of_runs = numOfRuns;

    _window_title->setTitle(title);

    _coordinates_per_house = coordPerHouse;

    // one unit is the house and the border around the house
    int pixelsPerHouseUnit = cityChartCalculatePxPerUnit(
        minsAndMaxCoords[0],
        minsAndMaxCoords[1],
        minsAndMaxCoords[2],
        minsAndMaxCoords[3]
    );

    _city_chart =  createCityChart(
        pixelsPerHouseUnit,
        minsAndMaxCoords[0],
        minsAndMaxCoords[1],
        minsAndMaxCoords[2],
        minsAndMaxCoords[3]
    );

    
    /* DIVERSITY CHART */
        
    _dvsty_chart = createDvstyChart(neighbors, maxNumOfNeighbors, numOfRuns);
    

    /* HAPPINESS CHART */

    _happiness_chart = createHapChart(numOfRuns);
    
    
}

std::vector<int> Printer_Graphic::determineMinMaxHouseCoords(
    std::unordered_map<const House*, Coordinate > coordPerHouse
)
{
    // Determine the min and max house coordinates for x and y.
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int minY = std::numeric_limits<int>::max();
    int maxY = std::numeric_limits<int>::min();

    for (auto& pair : coordPerHouse)
    {
        Coordinate coord =  pair.second;
        if (coord.getX() > maxX)
            maxX = coord.getX();
        if (coord.getX() < minX)
            minX = coord.getX();
        if (coord.getY() > maxY)
            maxY = coord.getY();
        if (coord.getY() < minY)
            minY = coord.getY();
    }
    std::vector<int> minsAndMaxes;
    minsAndMaxes.push_back(minX);
    minsAndMaxes.push_back(maxX);
    minsAndMaxes.push_back(minY);
    minsAndMaxes.push_back(maxY);

    return minsAndMaxes;
}

int Printer_Graphic::determineMaxNumberOfNeighbors (
    std::unordered_map<const House*, std::set<const House*>> neighbors
)
{
    int max = 0;

    for (auto& pair : neighbors)
    {
        if ((int)(pair.second.size()) > max)
            max = pair.second.size();
    }

    return max;
}

std::unique_ptr<GrCityChart> Printer_Graphic::createCityChart (
    int unitSize,
    int minXCoord, 
    int maxXCoord, 
    int minYCoord, 
    int maxYCoord
)
{ 
    int houseSize = unitSize/2;
    houseSize =  ((unitSize - houseSize) % 2 == 0) ? houseSize : (houseSize + 1);

    GrCityChartSizer cityPrinterSizer = 
        GrCityChartSizer (
            _x_chart_space__px,
            _city_y_space__px,
            _axis_format_X,
            _axis_format_Y,
            _chart_title_letter,
            minXCoord,
            maxXCoord,
            minYCoord,
            maxYCoord,
            houseSize,
            unitSize,
            _x_offset_multiplier,
            _x_overrun_multiplier,
            true,
            _color_key_letter
        );
   
    return std::make_unique<GrCityChart>(
        cityPrinterSizer,
        _coordinates_per_house,
        _colors,
        _left_right_borders__px,
        _city_map_chart_top_left_y_coord__px
    );
}

int Printer_Graphic::cityChartCalculatePxPerUnit(
    int minXCoord, 
    int maxXCoord, 
    int minYCoord, 
    int maxYCoord
)
{
    // start and end offsets are the offset_multiplier times the dot_size__px.
    // approximate the start and end offsets as offset_multiplier times the cellSize.

    int allowableXAxisLengthPx = _x_chart_space__px - _axis_format_Y.getAxisHeightPx();
    int numOfCellsX = 
        (maxXCoord - minXCoord) +
        _x_offset_multiplier +
        _x_overrun_multiplier;
    int xCellSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx = 
        _city_y_space__px -
        _chart_title_letter.getHeightIncLSpace() -
        _color_key_letter.getHeightIncLSpace() - 
        _axis_format_Y.getAxisHeightPx();

    int numOfCellsY = 
        (maxYCoord - minYCoord) +
        _y_offset_multiplier +
        _y_overrun_multiplier;

    int yCellSize =  allowableYAxisLengthPx/numOfCellsY;

    int smallestCellSize = std::min(xCellSize, yCellSize);

    // TODO what todo about smallest acceptable size??
    return (smallestCellSize < 4) ? 4 : smallestCellSize;
}

std::unique_ptr<GrDvstyChart> Printer_Graphic::createDvstyChart (
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int maxNumOfNeighbors,
    int maxNumOfRuns
)
{
    std::set<Mood> moods{Mood::neutral};
    return std::make_unique<GrDvstyChart> (
        _div_sizer,
        _colors,
        moods,
        _x_center__px + _col_side_border__px,
        _div_chart_top_y__px,
        "Diversity, Average Number of Disparate Neighbors per Resident per Run",
        neighbors,
        maxNumOfNeighbors,
        maxNumOfRuns
    );
}

std::unique_ptr<GrHapChart>  Printer_Graphic::createHapChart (int numberOfRuns)
{   
    std::set<Mood> moods{Mood::neutral};

    return std::make_unique<GrHapChart> (
        _hap_sizer,
        _colors,
        moods,
        _x_center__px + _col_side_border__px,
        _hap_chart_top_y__px,
        "Happiness, Average Happiness per Resident (shown as a percentage)",
        numberOfRuns,
        0,
        100
    );
}

void Printer_Graphic::print (
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run
)
{   
    std::unordered_map<const Resident*, const House*> housePerResident;
    std::vector<const Resident*> residents;
    for (auto pair : residentPerHouse)
    {
        if (pair.second != nullptr) // resident is not nullptr
        {
        housePerResident[pair.second] = pair.first;
        residents.push_back(pair.second);
        }
    }

    _window_title->print(_renderer.get());

    _runs_chart->print(run, _renderer.get());

    _city_chart->print(residentPerHouse, _renderer.get());

    _dvsty_chart->print(
        housePerResident,
        residentPerHouse,
        run,
        _renderer.get()
    );

    _happiness_chart->print(
        housePerResident,
        run,
        _renderer.get()
    );
    _renderer->endFrame();
} 

void Printer_Graphic::keepScreen()
{
    SDL_Event e;
    int counter = 0;
    while (SDL_WaitEvent(&e) != 0)
    {   
        counter ++;
        if (e.type == SDL_QUIT)
        {
            break;
        }
    }
}

int Printer_Graphic::maxNumOfHousesX (int screenWidth__px)
{   (void)screenWidth__px;
    //TODO figure this out
    return 100;
}

int Printer_Graphic::maxNumOfHousesY (int screenWidth__px)
{
    (void)screenWidth__px;
    //TODO figure this out
    return 100;
}
