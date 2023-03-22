#include "City_Grid.h"
#include <iostream>
#include <math.h>

using namespace std;

// This class has to be tested.
City_Grid::City_Grid (int width):
	City(),
	_width{width},
	_maxX{_width - 1 },
	_maxY{_width  - 1}
{	
	_houses.reserve(_width * _width);
  	for (int ii=0; ii<width; ++ii)
  	{
  		for (int jj=0; jj<width; ++jj)
        { 
		  int addr = (ii*width) + jj;
          _houses.emplace_back(make_unique<House>(addr));
		  _house_per_address[addr] = (_houses[addr]).get();
        }
  	}
}

double City_Grid::getHeight() const
{
	return _width;
}

double City_Grid::getWidth() const
{
	return _width;
}

Coordinate City_Grid::getCoordinate(const int& address) const
{
	return Coordinate{get_x(address), get_y(address)};
}

unordered_map<const House*, Coordinate> City_Grid::getCoordinatesPerHouse()
{
	unordered_map<const House*, Coordinate> coordinatesPerHouse{};
	for (auto& pair : _house_per_address)
	{
		coordinatesPerHouse.emplace(pair.second, getCoordinate(pair.first));
	}

	return coordinatesPerHouse;
}

double City_Grid::getDist (const int& fromAddress, const int& toAddress) const
{
	double x_dist = fabs( get_x(fromAddress) - get_x(toAddress) );
	double y_dist = fabs( get_y(fromAddress) - get_y(toAddress) );
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}


unordered_set<const House*> City_Grid::getHousesWithinDistance (
        const House* house,
        double allowableDist
    ) const
{	
	unordered_set<const House*> housesWithinDistance{};

	int central_address = house->getAddress();
	int central_address_x = get_x(central_address);
	int central_address_y = get_y(central_address);
	int minX = max(central_address_x - (int)floor(allowableDist), _minX);
	int maxX = min(central_address_x + (int)floor(allowableDist), _maxX);
	int minY = max(central_address_y - (int)floor(allowableDist), _minY);
	int maxY = min(central_address_y + (int)floor(allowableDist), _maxY);

	// houses within allowableDistance trace out a circle. 

	// First trace out the top half of the circle.
	// yy is from the top of the circle to the the central house's y (inclusive).
	// for each yy less than or equal to the central house's yy, find houses within allowableDistance.
	// for each yy row, find the minimum LeftX and the maximum RightX
	// houses need to be within the allowableDistance and still on the grid.
	// grid could cut-off circle.
	int yy = minY;
	int curLeftX = central_address_x;
	int curRightX = central_address_x;
	for (; yy<=central_address_y; ++yy)
	{
		int curLeftAddress = (yy*_width + curLeftX);
		while ( curLeftX >= minX && getDist(central_address, curLeftAddress) <= allowableDist )
		{
			housesWithinDistance.insert(_house_per_address.at(curLeftAddress));
			--curLeftX;
			curLeftAddress = (yy*_width) + curLeftX;
		}

		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX <= maxX && getDist(central_address, curRightAddress) <= allowableDist )
		{
			housesWithinDistance.insert(_house_per_address.at(curRightAddress));
			++curRightX;
			curRightAddress = (yy*_width + curRightX);
		}
	}

	// Next trace out the bottom half of the circle.
	// yy is from the bottom of the circle to one row less than the central house's y.
	// for each yy greater than the central house's yy, find houses within allowableDistance.
	// for each yy, find the minimum LeftX and the maximum RightX
	// houses need to be within the allowableDistance and still on the grid.
	yy = maxY;
	curLeftX = central_address_x;
	curRightX = central_address_x;
	for (; yy>central_address_y; --yy)
	{
		int curLeftAddress = (yy*_width + curLeftX);
		while (curLeftX >= minX && getDist(central_address, curLeftAddress) <= allowableDist)
		{
			housesWithinDistance.insert(_house_per_address.at(curLeftAddress));
			--curLeftX;
			curLeftAddress = (yy*_width) + curLeftX;
		}

		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX <= maxX && getDist(central_address, curRightAddress) <= allowableDist )
		{
			housesWithinDistance.insert(_house_per_address.at(curRightAddress));
			++curRightX;
			curRightAddress = (yy*_width) + curRightX;
		}

		// don't include central house as a neighbor. We only want the neighbors of central house.
		if (housesWithinDistance.find(house) != housesWithinDistance.end())
		{
			housesWithinDistance.erase(house);
		}
	}
	return housesWithinDistance;
}


int City_Grid::getNumOfHouses() const
{
	return _houses.size();
}

vector<const House*> City_Grid::getHouses () const
{	
	vector<const House*> houses;
	for (auto& house : _houses)
	{	
		houses.push_back(house.get());
	}
	return houses;
}

// TODO just keep a map of house to set of adjacent houses
set<const House*> City_Grid::getHousesAdjacent (int address) const
{
	int largestAddress = getNumOfHouses() - 1;
	
	set<const House*> adjacentHouses = {};

	int topLeft = address - _width - 1;

	for (int ii=0; ii<=2; ++ii)
	{
		// add neighbors from row above.
		int neighborAddress = topLeft + ii;
		if (neighborAddress >= 0 && neighborAddress <= largestAddress)
		{
			adjacentHouses.insert(_houses[neighborAddress].get());
		}

		// add neighbors from left and right
		neighborAddress = topLeft + _width + ii;
		if (neighborAddress >= 0 && neighborAddress <= largestAddress && neighborAddress != address)
		{
			adjacentHouses.insert(_houses[neighborAddress].get());
		}

		// add neighbors from row below.
		neighborAddress = topLeft + 2 * _width + ii;
		if (neighborAddress >= 0 && neighborAddress <= largestAddress)
		{
			adjacentHouses.insert(_houses[neighborAddress].get());
		}
	}

	return adjacentHouses;
}

std::string City_Grid::toString (const std::unordered_map<int, char>& characterPerAddress)
{	
	
	string result = "";
	for (int ii = 0; ii<_width; ++ii)
	{
		for (int jj=0; jj<_width; ++jj)
		{
			const int address = ii * _width + jj;
			if (characterPerAddress.find(address) == characterPerAddress.end())
			{
				result.push_back(' ');
			}
			else
			{
				result.push_back(characterPerAddress.at(address));
			}
			result.push_back(' ');
		}
		result.push_back('\n');
	}

	return result;
}

const House* City_Grid::selectRandom (unordered_set<const House*>& setOfHouses) const
{
	int size = setOfHouses.size();
    int r = rand() % size;
    unordered_set<const House*>::iterator it = begin(setOfHouses);
    advance(it, r);
    return *it;
}

int City_Grid::get_x (const int& address) const
{
	return (address%_width);
}

int City_Grid::get_y (const int& address) const
{
	return (address/_width);
}