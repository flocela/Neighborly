#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisL2RTop.h"
#include "YAxisT2B.h"
#include "PlotA.h"
#include "PlotB.h"

Printer_Graphic::Printer_Graphic (
    std::string title,
    std::unordered_map<int, BaseColor> colors,
    std::unordered_map<const House*, Coordinate > coordPerHouse,
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int numOfRuns
)
{
    _window_title->setTitle(title);

    _colors = colors;

    _num_of_runs = numOfRuns;

    _coordinates_per_house = coordPerHouse;
    std::vector<int> minsAndMaxCoords = determineMinMaxHouseCoords(_coordinates_per_house);

    // one unit is the house plus the border around the house
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

    int maxNumOfNeighbors = determineMaxNumberOfNeighbors(neighbors);
        
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
{   (void)unitSize;
    std::set<Mood> moods{Mood::happy, Mood::unhappy};
    
    return std::make_unique<GrCityChart>(
        _coordinates_per_house,
        _colors,
        std::make_unique<TitleA>(
            _chart_title_letter,
            0,
            0,
            "City Map"),
        std::make_unique<GrColorKeyPrinter>(
            0,
            0,
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotB>(
            _city_plot_sizer,
            _colors, 
            moods, 
            0, 
            0,
            minXCoord, 
            maxXCoord,
            minYCoord, 
            maxYCoord,
            0,
            0),
        _left_right_borders__px,
        _city_map_chart_top_left_y_coord__px,
        _x_chart_space__px,
        _chart_y_space__px
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
        _x_offset_multiplier + // TODO this is a multiplier not an offset
        _x_overrun_multiplier;
    int xCellSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx = 
        _city_y_space__px -
        _chart_title_letter.getHeightIncLSpace() -
        _chart_key_letter.getHeightIncLSpace() - 
        _axis_format_Y.getAxisHeightPx();

    int numOfCellsY = 
        (maxYCoord - minYCoord) +
        _y_offset_multiplier +
        _y_overrun_multiplier;

    int yUnitSize =  allowableYAxisLengthPx/numOfCellsY;

    int smallestCellSize = std::min(xCellSize, yUnitSize);

    return (smallestCellSize < _smallest_allowable_cell_size__px) ? 
        _smallest_allowable_cell_size__px : smallestCellSize;
}

std::unique_ptr<GrDvstyChart> Printer_Graphic::createDvstyChart (
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int maxNumOfNeighbors,
    int maxNumOfRuns
)
{
    std::set<Mood> moods{Mood::neutral};
    return std::make_unique<GrDvstyChart> (
        _colors,
        moods,
        neighbors,
        std::make_unique<TitleA>(
            _chart_title_letter,
            0,
            0,
            "Diversity, Average Number of Disparate Neighbors per Resident per Run"),
        std::make_unique<GrColorKeyPrinter>(
            0,
            0,
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, 
            0,
            0,
            maxNumOfRuns,
            0,
            maxNumOfNeighbors,
            0,
            0),
        _x_center__px + _col_side_border__px,
        _div_chart_top_y__px,
        _x_chart_space__px,
        _diversity_chart_y_axis_fraction * _chart_y_space__px
    );
}

std::unique_ptr<GrHapChart>  Printer_Graphic::createHapChart (int numberOfRuns)
{   
    std::set<Mood> moods{Mood::neutral};

    return std::make_unique<GrHapChart> (
        _hap_sizer,
        _colors,
        moods,
        std::make_unique<TitleA>(
            _chart_title_letter,
            0,
            0,
            "Happiness, Average Happiness per Resident (shown as a percentage)"),
        std::make_unique<GrColorKeyPrinter>(
            0,
            0,
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, 
            0,
            0,
            numberOfRuns,
            0,
            100, // resident happiness range is from 0 to 100.
            0,
            0),
        _x_center__px + _col_side_border__px,
        _hap_chart_top_y__px,
        _x_chart_space__px,
        _hap_chart_y_axis_fraction * _chart_y_space__px
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
