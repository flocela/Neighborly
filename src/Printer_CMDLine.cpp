#include "Printer_CMDLine.h"

#include <vector>
#include <algorithm>

void Printer_CMDLine::print(std::map<int, Resident*> residentPerHouse, 
                            std::map<Coordinate, int> housePerCoordinate,
                            int run,
                            int totRuns,
                           	std::string title)
{
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
        int currX = 0;
        for (int ii=0; ii< coordinates.size(); ii++)
        {
            int diffY = coordinates[ii].getY() - currY;
            if (diffY != 0)
            {
                currX = 0;
                for (int ss=0; ss<diffY; ++ss)
                {
                    std::cout << "\n";
                }
            }
            int diffX = coordinates[ii].getX();
            for (int hh=0; hh<diffX; ++hh)
            {
                std::cout << " ";
            }
            std::cout << "o";
        }
    }

} 
void Printer_CMDLine::printResidents(std::map<int, Resident*> housePerResident,
                                     std::map<int, Coordinate> coordinatePerHouse,
                                     int run,
                                     int totRuns,
                           			 std::string title)
{
}
