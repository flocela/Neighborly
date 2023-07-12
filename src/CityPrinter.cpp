#include <math.h>

#include "CityPrinter.h"
#include "Coordinate.h"
using namespace std;

CityPrinter::CityPrinter (const City* city)
: _city{city}
{}

string CityPrinter::print (unordered_map<int, char> characterPerAddress) const
{
    int width = _city->getWidth();
    int height = _city->getHeight();

	// Create map of houses per coordinate
	unordered_map<Coordinate, const House*> housesPerCoordinate{};
	unordered_map<const House*, Coordinate> coordinatesPerHouse = _city->getCoordinatesPerHouse();
	for (auto houseAndCoord : coordinatesPerHouse)
	{
		housesPerCoordinate.insert({houseAndCoord.second, houseAndCoord.first});
	}

	// Create resultant string
    string result = "";
	
    // Append x-axis labels. The labels are every 5 spaces. Only 3 digits long.
	for (int ii=0; ii<3; ++ii)
	{	
        result.append("    "); // four spaces makes room for y-axis labels

        // when ii is 0, divisor is 100. corresponds to top row.
        // when ii is 1, divisor is 10. corresponds to middle row.
        // when ii is 2, divisor is 1. corresponds to bottom row.i
		int divisor = pow(10, (2-ii));

        // For each value on x-axis
		for (int val=0; val <width; ++val)
		{
            // if on third row, and value is zero, then append 0
			if (ii == 2 && val == 0)
			{
				result.push_back(48);
			}
            // if value is divisible by 5 (so ends in 0 or 5), then append digit
			else if (val/divisor != 0 && val%5 == 0)
			{
				result.push_back(48+(val/divisor)%10);
			}
			else
			{
				result.push_back(' ');
			}
			result.push_back(' ');
		}
		result.push_back('\n');
	}
    
    // For each row (y-axis value): append y-axis label and address characters for that row
    // Only apply y-axis label if y-value is a multiple of 5 (ends in 0 or 5)
    for (int yVal = 0; yVal<height; ++yVal)
	{
        // If yVal is divisible by 5 (ends in 0 or 5), then add label.
		if (yVal%5 == 0)
		{
            // If yVal has three digits, do not prepend spaces
			if (yVal/100 != 0)
			{
			}
            // If yVal has two digits, prepend one space
			else if (yVal/10 != 0)
			{
				result.push_back(' ');
			}
            // Else prepend two spaces
			else
			{
				result.append("  ");
			}
			result.append(to_string(yVal));
			result.push_back(' ');
		}
        // If yVal is not divisible by 5, do not add a label.
		else
		{
			result.append("    ");
		}
		
        // Add character for each coordinate, if a character is given for that house.
		for (int xVal=0; xVal<width; ++xVal)
		{
			Coordinate coord = Coordinate{xVal, yVal};

			// if house exists at coordinate
			if (housesPerCoordinate.find(coord) != housesPerCoordinate.end())
			{
				const House* house = housesPerCoordinate.at(coord);
				int address = house->getAddress();
				if (characterPerAddress.find(address) == characterPerAddress.end())
				{
					result.push_back('-');
				}
				else
				{
					result.push_back(characterPerAddress.at(address));
				}
			}
			// if house does not exist at coordinate
			else
			{
				result.push_back(' ');
			}
			
			result.push_back(' ');
		}
		result.push_back('\n');
	}

	return result;
}