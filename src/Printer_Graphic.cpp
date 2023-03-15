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
    std::unique_ptr<Renderer> renderer,
    unordered_map<int, BaseColor> colors,
    unordered_map<const House*, Coordinate > coordinatesPerHouse,
    unordered_map<const House*, set<const House*>> neighborHousesPerHouse,
    string title,
    int numOfRuns
): _renderer{move(renderer)},
   _colors{colors},
   _coordinates_per_house{coordinatesPerHouse},
   _window_title{make_unique<TitleA>(_window_title_letter, _x_center__px, _top_border__px, title)},
   _num_of_runs{numOfRuns},
   _runs_chart_top_y__px{_top_border__px + _window_title->sizeYPx()},
   _runs_chart{make_unique<GrRunsChart>(
       _side_borders__px,
       _runs_chart_top_y__px,
       _screen_width__px - (2 * _side_borders__px),
       _chart_title_letter.getHeightIncLSpace(),
       _chart_title_letter,
       _num_of_runs)}
{   (void)neighborHousesPerHouse;
    _window_title->setTextColor(_title_text_color);
    // column space for left and right columns. Columns sit below the runs chart.
    // left column holds city chart, right column holds diversity chart and happiness chart
    int colSpaceYPx = 
        _screen_height__px -
        _top_border__px -
        _window_title->sizeYPx() -
        _runs_chart->sizeYPx() -
        _bottom_border__px;
    // diversity chart and city chart have the same y-value for their top left corners.
    // they sit below the runs chart.
    int chartsTopLeftYPx = _runs_chart_top_y__px + _runs_chart->sizeYPx();

    vector<int> minsAndMaxCoords = determineMinMaxHouseCoords(_coordinates_per_house);

    _city_chart =  createCityChart(
        minsAndMaxCoords[0],
        minsAndMaxCoords[1],
        minsAndMaxCoords[2],
        minsAndMaxCoords[3],
        chartsTopLeftYPx,
        colSpaceYPx // city chart takes up the whole left column (vertically).
    );

    // right column holds diversity chart and happiness chart below it
    int divChartAvailSpaceYPx = _div_chart_y_axis_fraction * colSpaceYPx;

    int maxNumOfNeighbors = determineMaxNumberOfNeighbors(neighborHousesPerHouse);

    _div_chart = createDvstyChart(
        neighborHousesPerHouse,
        maxNumOfNeighbors,
        _num_of_runs,
        chartsTopLeftYPx,
        divChartAvailSpaceYPx
    );

    // happiness chart sits below diversity chart. There's a vertical space between the 
    // diversity chart and the happiness chart, see _space_below_div_chart_y_axis_fraction.
    int hapChartTopLeftYPx = 
        chartsTopLeftYPx +
        colSpaceYPx * (_div_chart_y_axis_fraction + _space_below_div_chart_y_axis_fraction);

    int hapChartAvailSpaceYPx = 
        (1 - _div_chart_y_axis_fraction - _space_below_div_chart_y_axis_fraction) * colSpaceYPx;

    _happiness_chart = createHapChart(_num_of_runs, hapChartTopLeftYPx, hapChartAvailSpaceYPx);
}

void Printer_Graphic::print (
    unordered_map<const House*, const Resident*> residentPerHouse,
    int run
) const
{   
    // TODO take out this rect and renderer is just for testing.
    Rect rect {
        0,
        10,
        600,
        1
    };
    _renderer->fillBlock(rect, _the_color_rgba[Color::red_happy]);

    // given residentPerHouse, need housePerResident and vector of residents
    unordered_map<const Resident*, const House*> housePerResident;
    vector<const Resident*> residents;
    for (auto resAndHouse : residentPerHouse)
    {
        if (resAndHouse.second != nullptr) // resident is not nullptr
        {
        housePerResident[resAndHouse.second] = resAndHouse.first;
        residents.push_back(resAndHouse.second);
        }
    }
    _window_title->print(_renderer.get());
    _runs_chart->print(run, _renderer.get());
    _city_chart->print(residentPerHouse, _renderer.get());
    _div_chart->print(housePerResident, residentPerHouse, run, _renderer.get());
    _happiness_chart->print(housePerResident, run, _renderer.get());
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

    for (auto& houseAndNeighbors : neighbors)
    {
        if ((int)(houseAndNeighbors.second.size()) > max)
            max = houseAndNeighbors.second.size();
    }

    return max;
}

unique_ptr<GrCityChart> Printer_Graphic::createCityChart (
    int minXCoord, 
    int maxXCoord, 
    int minYCoord, 
    int maxYCoord,
    int topLeftYPx,
    int availSpaceYPx
)
{   
    PlotFormat cityPlotFormat{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier
    };

    set<Mood> moods{Mood::happy, Mood::unhappy};

    return make_unique<GrCityChart>(
        _coordinates_per_house,
        _colors,
        make_unique<TitleA>(
            _chart_title_letter,
            _city_chart_title),
        make_unique<GrColorKey>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotB>(
            cityPlotFormat,
            minXCoord, 
            maxXCoord,
            minYCoord, 
            maxYCoord),
        _side_borders__px,
        topLeftYPx,
        _chart_space_x__px,
        availSpaceYPx
    );
}

unique_ptr<GrDvstyChart> Printer_Graphic::createDvstyChart (
    unordered_map<const House*, set<const House*>> neighbors,
    int maxNumOfNeighbors,
    int maxNumOfRuns,
    int topLeftYPx,
    int availSpaceYPx
)
{
    AxisFormat axisYFormatForDivChart = _axis_format_Y;
    axisYFormatForDivChart.setBackgroundTickLines(true);
    PlotFormat rightColFormat{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier
    };

    set<Mood> moods{Mood::neutral};
    return make_unique<GrDvstyChart> (
        _colors,
        moods,
        neighbors,
        make_unique<TitleA>(
            _chart_title_letter,
            _div_chart_title),
        make_unique<GrColorKey>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotA>(
            rightColFormat,
            0, // min number of runs
            maxNumOfRuns - 1,
            0, // min number of neighbors
            maxNumOfNeighbors
        ),
        _x_center__px + _col_inside_border__px,
        topLeftYPx,
        _chart_space_x__px,
        availSpaceYPx
    );
}

unique_ptr<GrHapChart>  Printer_Graphic::createHapChart (
    int numberOfRuns,
    int topLeftYPx,
    int availSpaceYPx
)
{  
    AxisFormat axisYFormatForHapChart = _axis_format_Y;
    axisYFormatForHapChart.setBackgroundTickLines(true);
    PlotFormat rightColFormat{
        _axis_format_X,
        axisYFormatForHapChart,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier
    };

    set<Mood> moods{Mood::neutral};

    return make_unique<GrHapChart> (
        _colors,
        make_unique<TitleA>(
            _chart_title_letter,
            _hap_chart_title),
        make_unique<GrColorKey>(
            _chart_key_letter,
            _colors,
            moods),
        make_unique<PlotA>(
            rightColFormat,
            0, // starting run number
            numberOfRuns -1,
            0, // minimum resident happiness
            100 // resident happiness range is from 0 to 100.
        ),
        _x_center__px + _col_inside_border__px,
        topLeftYPx,
        _chart_space_x__px,
        availSpaceYPx
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