#include "Printer_Graphic.h"

#include <iostream>
#include "Axis_Basic.h"
#include "GrAxisHorizontalSimple.h"
#include "GrAxisVerticalSimple.h"
#include "PlotA.h"
#include "PlotB.h"

using namespace std;

Printer_Graphic::Printer_Graphic (
    std::unique_ptr<Renderer> renderer,
    const unordered_map<int, BaseColor>& colors,
    const unordered_map<const House*, Coordinate>& coordinatesPerHouse,
    const SetOfHousesPerHouse& adjacentHousesPerHouse,
    string title,
    int numOfRuns
): _renderer{move(renderer)},
   _colors{colors},
   _coordinates_per_house{coordinatesPerHouse},
   _window_title{make_unique<Title_Basic>(
    _window_title_letter,
    _x_center__px,
    _top_border__px,
    title)},
   _num_of_runs{numOfRuns},
   _runs_chart_top_y__px{_top_border__px + _window_title->sizeYPx()},
   _runs_chart{make_unique<GrRunsChart>(
    _side_borders__px,
    _runs_chart_top_y__px,
    _screen_width__px - (2 * _side_borders__px),
    _chart_title_letter.getHeightIncLSpace(),
    _chart_title_letter,
    _num_of_runs)}
{  
    _window_title->setTextColor(_title_text_color);

    // Set vertical column space for left and right columns. Columns sit below the runs chart.
    // Left column holds city chart. Right column holds diversity and happiness charts.
    int colSpaceYPx = 
        _screen_height__px -
        _top_border__px -
        _window_title->sizeYPx() -
        _runs_chart->sizeYPx() -
        _bottom_border__px;

    // Set the y value for the top left corner of the city and diversity charts.
    // They sit below the runs chart.
    int chartsTopLeftYPx = _runs_chart_top_y__px + _runs_chart->sizeYPx();

    // For the city chart, ascertain the minimum and maximum required coordinates. These are
    // found from the given house coordinates.
    vector<int> minsAndMaxCoords = ascertainMinMaxHouseCoords(_coordinates_per_house);

    _city_chart =  createCityChart(
        minsAndMaxCoords[0],
        minsAndMaxCoords[1],
        minsAndMaxCoords[2],
        minsAndMaxCoords[3],
        chartsTopLeftYPx,
        colSpaceYPx // city chart takes up the whole left column (vertically).
    );

    // Determine the available space for the diversity chart.
    int divChartAvailSpaceYPx = _div_chart_y_axis_fraction * colSpaceYPx;

    int largestNumOfAdjHouses = ascertainLargestNumberOfAdjHouses(adjacentHousesPerHouse);

    _div_chart = createDvstyChart(
        largestNumOfAdjHouses,
        _num_of_runs,
        chartsTopLeftYPx,
        divChartAvailSpaceYPx
    );

    // Happiness chart sits below diversity chart. There's a vertical space between the 
    // diversity chart and the happiness chart. See _space_below_div_chart_y_axis_fraction.
    // Determine the y value of the top left corner of the happiness chart.
    int hapChartTopLeftYPx = 
        chartsTopLeftYPx +
        colSpaceYPx * (_div_chart_y_axis_fraction + _space_below_div_chart_y_axis_fraction);

    int hapChartAvailSpaceYPx = 
        (1 - _div_chart_y_axis_fraction - _space_below_div_chart_y_axis_fraction) * colSpaceYPx;

    _happiness_chart = createHapChart(_num_of_runs, hapChartTopLeftYPx, hapChartAvailSpaceYPx);
}

void Printer_Graphic::print (const RunMetrics* runMetrics) const
{   
    int run = runMetrics->getRunNumber();

    // Get residents per house from runMetrics information.
    const ResPerHouse& residentPerHouse = runMetrics->getResidentsPerHouse();

    // Printing is from top to bottom, left to right.
    _window_title->print(_renderer.get());
    _runs_chart->print(run, _renderer.get());
    _city_chart->print(residentPerHouse, _renderer.get());
    _div_chart->print(
        runMetrics->getNumOfResidentsPerGroupId(),
        runMetrics->getNumOfDiffNeighborsPerGroupId(),
        run,
        _renderer.get()
    );
    _happiness_chart->print(
        runMetrics->getNumOfResidentsPerGroupId(),
        runMetrics->getHappinessSumPerGroupId(),
        run,
        _renderer.get());
    _renderer->endFrame();
}

// After last print. Printer_Graphic keeps window open until user clicks x.
void Printer_Graphic::lastPrint ()
{
    _renderer->keepScreen();
}

vector<int> Printer_Graphic::ascertainMinMaxHouseCoords(
    unordered_map<const House*, Coordinate > coordPerHouse
)
{
    if (coordPerHouse.size() == 0)
    {
        return vector<int>{0, 0, 0, 0};
    }
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

int Printer_Graphic::ascertainLargestNumberOfAdjHouses (const SetOfHousesPerHouse& neighbors)
{
    size_t max = 0;

    for (auto& houseAndNeighbors : neighbors)
    {
        if (houseAndNeighbors.second.size() > max)
            max = houseAndNeighbors.second.size();
    }

    return static_cast<int>(max);
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
        make_unique<Title_Basic>(_chart_title_letter,_city_chart_title),
        make_unique<GrColorKey_Basic>(_chart_key_letter, _colors, moods),
        make_unique<PlotB>(
            cityPlotFormat,
            make_unique<GrAxisHorizontalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates increase, set as true.
                    // PlotB's constructor sets the x-axis as a forward axis.
                    true,                   
                    0,                      // starting pixel for x-axis, use zero for now
                    minXCoord,              // smallest coordinate in the x-direction             
                    maxXCoord,              // largest coordinate in the x-direction
                    0,                      // pixels per unit, use zero for now
                    _x_offset_multiplier,
                    _x_offset_multiplier
                ),
                _axis_format_X,
                0,                          // y-coordinate for x-axis, use zero for now.
                true
            ),
            make_unique<GrAxisVerticalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates increase, set as true.
                    // PlotB's constructor sets the y-axis as a forward axis.
                    true,
                    0,                      // starting pixel for y-axis, use zero for now
                    minYCoord,              // smallest coordinate in y-direction
                    maxYCoord,              // largest coordinate in y-direction
                    0,                      // pixels per unit, use zero for now
                    _y_offset_multiplier,
                    _y_offset_multiplier
                ),
                _axis_format_Y,
                0                           // y-axis's x-coordinate (pixel), use zero for now
            )
        ),
        _side_borders__px,  // top left corner of chart, x-value
        topLeftYPx,         // top left corner of chart, y-value
        _chart_space_x__px, // space available, x-direction
        availSpaceYPx       // space available, y-direction
    );
}

unique_ptr<GrDvstyChart> Printer_Graphic::createDvstyChart (
    int maxNumOfNeighbors,
    int maxNumOfRuns,
    int topLeftYPx,
    int availSpaceYPx
)
{
    AxisFormat axisFormatForDivChartY = _axis_format_Y;
    axisFormatForDivChartY.setBackgroundTickLines(true);

    // the plot format used for charts, modified to show background tick lines
    PlotFormat rightColFormat{
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
        make_unique<Title_Basic>(_chart_title_letter, _div_chart_title),
        make_unique<GrColorKey_Basic>(_chart_key_letter, _colors, moods),
        make_unique<PlotA>(
            rightColFormat,                   
            make_unique<GrAxisHorizontalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates increase, set as true.
                    // PlotA's constructor sets the x-axis as a forward axis.
                    true,                      
                    0,                         // starting pixel for x-axis, use zero for now
                    0,                         // The first run number is zero.
                    max(0, maxNumOfRuns-1),    // the last run number TODO why do I check for max??
                    0,                         // pixels per unit, use zero for now
                    _x_offset_multiplier,
                    _x_offset_multiplier
                ),
                _axis_format_X,
                0,                             // y-coordinate for x-axis, use zero for now.
                false
            ),
            make_unique<GrAxisVerticalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates decrease, set as false.
                    // PlotA's constructor sets the y-axis as reverse axis.
                    false,                     
                    0,                         // starting pixel for y-axis, use zero for now
                    0,                         // smallest number of neighbors for a resident is 0
                    maxNumOfNeighbors,         // largest number of neighbors for a resident
                    0,                         // pixels per unit, use zero for now
                    _y_offset_multiplier,
                    _y_offset_multiplier
                ),
                axisFormatForDivChartY,
                0                              // x-coordinate for y-axis, use zero for now
            )
        ),                                      
        _x_center__px + _col_inside_border__px, // top left corner of chart, x-coordinate
        topLeftYPx,                             // top left corner of chart, y-coordinate
        _chart_space_x__px,                     // space available, x-direction
        availSpaceYPx                           // space available, y-direction
    );
}

unique_ptr<GrHapChart>  Printer_Graphic::createHapChart (
    int numberOfRuns,
    int topLeftYPx,
    int availSpaceYPx
)
{  
    AxisFormat axisFormatForHapChartY = _axis_format_Y;
    axisFormatForHapChartY.setBackgroundTickLines(true);

    PlotFormat rightColFormat{
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier
    };

    set<Mood> moods{Mood::neutral};

    return make_unique<GrHapChart> (
        _colors,
        make_unique<Title_Basic>( _chart_title_letter, _hap_chart_title),
        make_unique<GrColorKey_Basic>( _chart_key_letter, _colors, moods),
        make_unique<PlotA>(
            rightColFormat,                   // plot format for charts on right column
            make_unique<GrAxisHorizontalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates increase, set as true.
                    // PlotA's constructor sets the x-axis as a forward axis also.
                    true,                      
                    0,                         // starting pixel for x-axis, use zero for now
                    0,                         // Zero is the starting run number.
                    max(0, numberOfRuns-1),    // index of the last run TODO why do I check for max??
                    0,                         // pixels per unit, use zero for now
                    _x_offset_multiplier,
                    _x_offset_multiplier
                ),
                _axis_format_X,
                0,                             // x-axis's x-coordinate (pixel) // TODO better note
                false
            ),
            make_unique<GrAxisVerticalSimple>(
                make_unique<Axis_Basic>(
                    // axis values increase as window's coordinates decrease, set as false.
                    // PlotA's constructor sets the y-axis as reverse axis.
                    false,                     
                    0,                         // starting pixel for y-axis, use zero for now
                    0,                         // least possible happiness for a resident
                    100,                       // largest possible happiness for a resident
                    0,                         // pixels per unit, use zero for now
                    _y_offset_multiplier,
                    _y_offset_multiplier
                ),
                axisFormatForHapChartY,
                0                              // y-axis's x-coordinate (pixel)
            )
        ),
        _x_center__px + _col_inside_border__px, // top left corner of chart, x-value
        topLeftYPx,                             // top left corner of chart, y-value
        _chart_space_x__px,                     // space available, x-direction
        availSpaceYPx                           // space available, y-direction
    );
}
