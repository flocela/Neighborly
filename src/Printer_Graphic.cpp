#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <iostream>
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

    // minsAndMaxCoords are coordinates, not pixels.
    _coordinates_per_house = coordPerHouse;
    std::vector<int> minsAndMaxCoords = determineMinMaxHouseCoords(_coordinates_per_house);

    _city_chart =  createCityChart(
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

void Printer_Graphic::print (
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run
)
{   

    _renderer->setColorToRed();
    SDL_Rect rect {
        5,
        0,
        5,
        1195
    };
    _renderer->fillBlock(rect);

    std::cout << "PrinterGraphic _city_map_chart_top_left_y_coord__px: " << _city_map_chart_top_left_y_coord__px << std::endl;
    std::cout << "PrinterGraphic _city_y_space__px: " << _city_y_space__px << std::endl;


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

    /*_happiness_chart->print(
        housePerResident,
        run,
        _renderer.get()
    );*/

    _renderer->endFrame();
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
    int minXCoord, 
    int maxXCoord, 
    int minYCoord, 
    int maxYCoord
)
{   
    std::set<Mood> moods{Mood::happy, Mood::unhappy};
    
    return std::make_unique<GrCityChart>(
        _coordinates_per_house,
        _colors,
        std::make_unique<TitleA>(
            _chart_title_letter,
            "City Map"),
        std::make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotB>(
            _city_plot_sizer,
            _colors, 
            moods, 
            minXCoord, 
            maxXCoord,
            minYCoord, 
            maxYCoord),
        _left_right_borders__px,
        _city_map_chart_top_left_y_coord__px,
        _x_chart_space__px,
        _chart_y_space__px
    );
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
            "Diversity, Average Number of Disparate Neighbors per Resident per Run"),
        std::make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, // min number of runs
            maxNumOfRuns,
            0, // min number of neighbors
            maxNumOfNeighbors
        ),
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
            "Happiness, Average Resident Happiness per Group, per Run"),
        std::make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        std::make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, // minimum number of runs
            numberOfRuns,
            0, // minimum resident happiness
            100 // resident happiness range is from 0 to 100.
        ),
        _x_center__px + _col_side_border__px,
        _hap_chart_top_y__px,
        _x_chart_space__px,
        _hap_chart_y_axis_fraction * _chart_y_space__px
    );
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
