#include "Printer_CMDLine.h"

#include <vector>
#include <algorithm>

void Printer_CMDLine::print(
    std::map<int, Resident*> residentPerHouse,
    int run,
    int totRuns,
    std::string title
)
{
    (void) residentPerHouse;
    (void) run;
    (void) totRuns;
    (void) title;
    /*
    run++; // TODO run is not used.
    totRuns++; // TODO totRuns not used.
    std::string x = title + "x"; // TODO title not used.
    std::vector<Coordinate> coordinates;
    for (auto const& element : housePerCoordinate)
    {
        coordinates.push_back(element.first);
    }
    std::sort(coordinates.begin(), coordinates.end());

    // Residents don't have houses yet, so just print o's for empty houses.
    if (residentPerHouse.size() == 0)
    {
        int currY = 0;
        for (Coordinate coord : coordinates)
        {
            int diffY = coord.getY() - currY;
            if (diffY != 0)
            {
                for (int ss=0; ss<diffY; ++ss)
                {
                    std::cout << "\n";
                }
            }
            int diffX = coord.getX();
            for (int hh=0; hh<diffX; ++hh)
            {
                std::cout << " ";
            }
            std::cout << "o";
        }
    }*/

} 
