#include "City_Grid.h"
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>

// This class has to be tested.
City_Grid::City_Grid (int width):
	City(),
	_width{width},
	_maxX{_width - 1 },
	_maxY{_width  - 1}
{	
	_houses.reserve(_width * _width);
	std::cout << "width: " << _width << std::endl;
  	for (int ii=0; ii<width; ++ii)
  	{
  		for (int jj=0; jj<width; ++jj)
        { 
		  int addr = (ii*width) + jj;
          _houses.emplace_back(std::make_unique<House>(addr));
		  _house_per_address[addr] = (_houses[addr]).get();
        }
  	}
}

int City_Grid::getNumOfHouses() const
{
	return _houses.size();
}

std::vector<const House*> City_Grid::getHouses () const
{	std::vector<const House*> houses;
	for (auto& house : _houses)
	{	
		houses.push_back(house.get());
	}
	return houses;
}

double City_Grid::getDist (const int& fromAddress, const int& toAddress) const
{
	double x_dist = fabs( get_x(fromAddress) - get_x(toAddress) );
	double y_dist = fabs( get_y(fromAddress) - get_y(toAddress) );
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}

std::set<const House*> City_Grid::getAdjacentHouses (const House* house) const
{
	int largestAddress = getNumOfHouses() - 1;
	int address = house->getAddress();
	
	std::set<const House*> adjacentHouses = {};

	int topLeft = address - _width - 1;

	for (int ii=0; ii<=2; ++ii)
	{
		// add neighbors from row above.
		int neighbor = topLeft + ii;
		if (neighbor >= 0 && neighbor <= largestAddress)
		{
			adjacentHouses.insert(_houses[neighbor].get());
		}

		// add neighbors from left and right
		neighbor = topLeft + _width + ii;
		if (neighbor >= 0 && neighbor <= largestAddress && neighbor != address)
		{
			adjacentHouses.insert(_houses[neighbor].get());
		}

		// add neighbors from row below.
		neighbor = topLeft + 2 * _width + ii;
		if (neighbor >= 0 && neighbor <= largestAddress)
		{
			adjacentHouses.insert(_houses[neighbor].get());
		}
	}

	return adjacentHouses;
}

// TODO, this method needs to be properly tested.
// Does not include @house in returned set.
std::set<House*> City_Grid::getHousesWithinDistance (
	const House* house, 
	double allowableDist
) const
{ 	auto start = std::chrono::system_clock::now();
	std::set<House*> nearHouses;
	// create a box area around @house, and only check houses inside box.
	// box area's width and height are 2 x allowableDist rounded up,
	// and @house is at center.
	int origAddress = house->getAddress();
	int origX = get_x(origAddress);
	int origY = get_y(origAddress);
	int minX = std::max(origX - (int)std::ceil(allowableDist), _minX);
	int maxX = std::min(origX + (int)std::ceil(allowableDist), _maxX);
	int minY = std::max(origY - (int)std::ceil(allowableDist), _minY);
	int maxY = std::min(origY + (int)std::ceil(allowableDist), _maxY);

	// y values less than and equal to origY
	int yy = minY;
	for (; yy<=origY; ++yy)
	{	
		// above origAddress
		int curAddress = (yy*_width + origX);

		if ( getDist(origAddress, curAddress) <= allowableDist )
			break;
	} 
	int curLeftX = origX;
	int curRightX = origX;
	for (; yy<=origY; ++yy)
	{

		int curLeftAddress = (yy*_width + curLeftX);
		while ( curLeftX-1 >= minX && getDist(origAddress, curLeftAddress -1) <= allowableDist )
		{
			curLeftX--;
			curLeftAddress = (yy*_width) + curLeftX;
		}

		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX + 1 <= maxX && getDist(origAddress, curRightAddress + 1) <= allowableDist )
		{
			curRightX++;
			curRightAddress = (yy*_width + curRightX);
		}
		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{
			int address = (yy * _width) + xx;
			nearHouses.insert(_house_per_address.at(address));
		}
	}
	// y values greater than origY
	yy = maxY;
	for (; yy>origY; --yy)
	{
		// below origAddress
		int curAddress = (yy*_width + origX);
		if (getDist(origAddress, curAddress) <= allowableDist)
		{
			break;
		}
	}

	curLeftX = origX;
	curRightX = origX;
	for (; yy>origY; --yy)
	{
		int curLeftAddress = (yy*_width + curLeftX);
		while (curLeftX-1 >= minX && getDist(origAddress, curLeftAddress - 1) <= allowableDist)
		{
			curLeftX--;
			curLeftAddress = (yy*_width) + curLeftX;
		}
		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX+1 <= maxX && getDist(origAddress, curRightAddress+1) <= allowableDist )
		{
			curRightX++;
			curRightAddress = (yy*_width) + curRightX;
		}

		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{	
			int address = (yy * _width) + xx;
			nearHouses.insert(_house_per_address.at(address));
		}
	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_sec = end - start;

	std::cout << "elapsed time: " << elapsed_sec.count() << "s" << std::endl;

	return nearHouses;
}

std::set<const House*> City_Grid::getANumberOfUnoccupiedNearHouses (
	const House* origHouse,
	double allowableDistance,
	std::set<const House*> notOccupied,
	size_t count
) const
{	
	std::set<const House*> returnedHouses;

	if (count == 0)
		return returnedHouses;
	
	std::set<House*> closeHouses = getHousesWithinDistance (
		origHouse,
		allowableDistance
	);

	std::set<House*> unoccupiedAndCloseHouses;
	for (House* house : closeHouses)
	{
		if (notOccupied.find(house) != notOccupied.end())
		{
			unoccupiedAndCloseHouses.insert(house);
		}
	}

	while (true)
	{
		if (returnedHouses.size() >= count || unoccupiedAndCloseHouses.empty())
		{
			return returnedHouses;
		}

		House* currHouse = selectRandom(unoccupiedAndCloseHouses);
		returnedHouses.insert(currHouse);
		unoccupiedAndCloseHouses.erase(currHouse);
	}

}

int City_Grid::get_x (const int& address) const
{
	return (address/_width);

}

int City_Grid::get_y (const int& address) const
{
	return (address%_width);
}

Coordinate City_Grid::getCoordinate(const int& address) const
{
	return Coordinate{get_x(address), get_y(address)};
}


House* City_Grid::selectRandom (std::set<House*>& setOfHouses) const
{
	int size = setOfHouses.size();
    int r = rand() % size;
    std::set<House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    return *it;
}

std::unordered_map<const House*, Coordinate> City_Grid::getCoordinatesPerHouse()
{
	
	std::unordered_map<const House*, Coordinate> coordinatesPerHouse{};
	for (auto& pair : _house_per_address)
	{
		Coordinate coord = getCoordinate(pair.first);
		coordinatesPerHouse.emplace(std::pair<House*, Coordinate>{pair.second, coord});
	}
	return coordinatesPerHouse;
}

