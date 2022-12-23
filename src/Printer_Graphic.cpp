#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <iostream>
#include "PlotA.h"
#include "PlotB.h"

using namespace std;

Printer_Graphic::Printer_Graphic (
    string title,
    unordered_map<int, BaseColor> colors,
    unordered_map<const House*, Coordinate > coordPerHouse,
    unordered_map<const House*, set<const House*>> neighbors,
    int numOfRuns
): _colors{colors},
   _coordinates_per_house{coordPerHouse},
   _num_of_runs{numOfRuns},
   _window_title{make_unique<TitleA>(_window_title_letter, _x_center__px, _top_border__px, title)}
{   

    vector<int> minsAndMaxCoords = determineMinMaxHouseCoords(_coordinates_per_house);

    _city_chart =  createCityChart(
        minsAndMaxCoords[0],
        minsAndMaxCoords[1],
        minsAndMaxCoords[2],
        minsAndMaxCoords[3]
    );
    
    int maxNumOfNeighbors = determineMaxNumberOfNeighbors(neighbors);
        
    _dvsty_chart = createDvstyChart(neighbors, maxNumOfNeighbors, _num_of_runs);
    
    _happiness_chart = createHapChart(_num_of_runs);
    
    _runs_chart = createRunsChart(_num_of_runs);
    
}

void Printer_Graphic::print (
    unordered_map<const House*, const Resident*> residentPerHouse,
    int run
)
{   
    /*_renderer->setColorToRed();
    SDL_Rect rect {
        5,
        0,
        5,
        1195
    };
    _renderer->fillBlock(rect);*/

    unordered_map<const Resident*, const House*> housePerResident;
    vector<const Resident*> residents;
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

vector<int> Printer_Graphic::determineMinMaxHouseCoords(
    unordered_map<const House*, Coordinate > coordPerHouse
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
    vector<int> minsAndMaxes;
    minsAndMaxes.push_back(minX);
    minsAndMaxes.push_back(maxX);
    minsAndMaxes.push_back(minY);
    minsAndMaxes.push_back(maxY);

    return minsAndMaxes;
}

int Printer_Graphic::determineMaxNumberOfNeighbors (
    unordered_map<const House*, set<const House*>> neighbors
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

unique_ptr<TitleA> Printer_Graphic::createWindowTitle (
    Letter letter,
    int topCenterX__px,
    int topCenterY__px,
    string title
)
{
    return make_unique<TitleA>(letter, topCenterX__px, topCenterY__px, title);
}

unique_ptr<GrCityChart> Printer_Graphic::createCityChart (
    int minXCoord, 
    int maxXCoord, 
    int minYCoord, 
    int maxYCoord
)
{   
    set<Mood> moods{Mood::happy, Mood::unhappy};

    return make_unique<GrCityChart>(
        _coordinates_per_house,
        _colors,
        make_unique<TitleA>(
            _chart_title_letter,
            "City Map"),
        make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotB>(
            _city_plot_sizer,
            _colors, 
            moods, 
            minXCoord, 
            maxXCoord,
            minYCoord, 
            maxYCoord),
        _side_borders__px,
        _city_map_chart_top_left_y_coord__px,
        _x_chart_space__px,
        _city_y_space__px
    );
}

unique_ptr<GrDvstyChart> Printer_Graphic::createDvstyChart (
    unordered_map<const House*, set<const House*>> neighbors,
    int maxNumOfNeighbors,
    int maxNumOfRuns
)
{
    set<Mood> moods{Mood::neutral};

    return make_unique<GrDvstyChart> (
        _colors,
        moods,
        neighbors,
        make_unique<TitleA>(
            _chart_title_letter,
            "Diversity, Average Number of Disparate Neighbors per Resident per Run"),
        make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, // min number of runs
            maxNumOfRuns,
            0, // min number of neighbors
            maxNumOfNeighbors
        ),
        _x_center__px + _col_inside_border__px,
        _div_chart_top_y__px,
        _x_chart_space__px,
        _diversity_chart_y_axis_fraction * _chart_y_space__px
    );
}

unique_ptr<GrHapChart>  Printer_Graphic::createHapChart (int numberOfRuns)
{   
    set<Mood> moods{Mood::neutral};

    return make_unique<GrHapChart> (
        _colors,
        moods,
        make_unique<TitleA>(
            _chart_title_letter,
            "Happiness, Average Resident Happiness per Group, per Run"),
        make_unique<GrColorKeyPrinter>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotA>(
            _div_sizer,
            _colors, 
            moods, 
            0, // minimum number of runs
            numberOfRuns,
            0, // minimum resident happiness
            100 // resident happiness range is from 0 to 100.
        ),
        _x_center__px + _col_inside_border__px,
        _hap_chart_top_y__px,
        _x_chart_space__px,
        (1 - _diversity_chart_y_axis_fraction) * _chart_y_space__px
    );
}

unique_ptr<GrRunsChart> Printer_Graphic::createRunsChart (int numOfRuns)
{
    return make_unique<GrRunsChart> (
        _side_borders__px, 
        _runs_chart_top_y__px,
        _screen_width__px - (2 * _side_borders__px),
        _chart_title_letter.getHeightIncLSpace(),
        _chart_title_letter,
        numOfRuns
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
