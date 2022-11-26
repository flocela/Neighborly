#include "City_Grid.h"
#include <iostream>
#include <math.h>

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
          _houses.emplace_back(std::make_unique<House>(addr));
		  _house_per_address[addr] = (_houses[addr]).get();
        }
  	}
}

int City_Grid::getNumOfHouses() const
{
	return _houses.size();
}

Coordinate City_Grid::getCoordinate(const int& address) const
{
	return Coordinate{get_x(address), get_y(address)};
}

double City_Grid::getDist (const int& fromAddress, const int& toAddress) const
{
	double x_dist = fabs( get_x(fromAddress) - get_x(toAddress) );
	double y_dist = fabs( get_y(fromAddress) - get_y(toAddress) );
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}

std::vector<const House*> City_Grid::getHouses () const
{	
	std::vector<const House*> houses;
	for (auto& house : _houses)
	{	
		houses.push_back(house.get());
	}
	return houses;
}

std::set<const House*> City_Grid::getAdjacentHouses (int address) const
{
	int largestAddress = getNumOfHouses() - 1;
	
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

void City_Grid::findHousesWithinDistance (
        const House* house,
        double allowableDist,
        std::unordered_set<const House*>& nearHouses
    ) const
{	
	int origAddress = house->getAddress();
	int origX = get_x(origAddress);
	int origY = get_y(origAddress);
	int minX = std::max(origX - (int)std::floor(allowableDist), _minX);
	int maxX = std::min(origX + (int)std::floor(allowableDist), _maxX);
	int minY = std::max(origY - (int)std::floor(allowableDist), _minY);
	int maxY = std::min(origY + (int)std::floor(allowableDist), _maxY);

	// houses within allowableDistance trace out a circle. 

	// for each yy less than or equal to the orig house's yy, find houses within allowableDistance.
	// for each yy, find the minimum LeftX and the maximum RightX
	// houses need to be within the allowableDistance and still on the grid.
	int yy = minY;
	int curLeftX = origX;
	int curRightX = origX;
	for (; yy<=origY; ++yy)
	{
		int curLeftAddress = (yy*_width + curLeftX);
		while ( curLeftX >= minX && getDist(origAddress, curLeftAddress) <= allowableDist )
		{
			curLeftAddress = (yy*_width) + curLeftX;
			--curLeftX;
		}
		++curLeftX;

		int curRightAddress = (yy*_width) + curRightX;
		
		while ( curRightX <= maxX && getDist(origAddress, curRightAddress) <= allowableDist )
		{
			curRightAddress = (yy*_width + curRightX);
			++curRightX;
		}
		--curRightX; 

		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{
			House* house = _house_per_address.at((yy * _width) + xx);
			nearHouses.insert(house);
		}
	}

	// for each yy less than or equal to the orig house's yy, find houses within allowableDistance.
	// for each yy, find the minimum LeftX and the maximum RightX
	// houses need to be within the allowableDistance and still on the grid.
	yy = maxY;
	curLeftX = origX;
	curRightX = origX;
	for (; yy>origY; --yy)
	{
		int curLeftAddress = (yy*_width + curLeftX);
		while (curLeftX >= minX && getDist(origAddress, curLeftAddress) <= allowableDist)
		{
			curLeftAddress = (yy*_width) + curLeftX;
			--curLeftX;
		}
		++curLeftX;

		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX <= maxX && getDist(origAddress, curRightAddress) <= allowableDist )
		{
			curRightAddress = (yy*_width) + curRightX;
			++curRightX;
		}
		--curRightX;

		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{	
			House* house = _house_per_address.at((yy * _width) + xx);
			nearHouses.insert(house);
		}
	}
}

// TODO, this method needs to be properly tested.
// Does not include @house in returned set.
// TODO what if allowableDist == 0?
std::unordered_set<const House*> City_Grid::getHousesWithinDistance (
	const House* house, 
	double allowableDist,
	std::unordered_set<House*>& nearHouses,
	std::set<const House*> notOccupied
) const
{ 	//std::set<House*> nearHouses;
	int origAddress = house->getAddress();
	int origX = get_x(origAddress);
	int origY = get_y(origAddress);
	int minX = std::max(origX - (int)std::ceil(allowableDist), _minX);
	int maxX = std::min(origX + (int)std::ceil(allowableDist), _maxX);
	int minY = std::max(origY - (int)std::ceil(allowableDist), _minY);
	int maxY = std::min(origY + (int)std::ceil(allowableDist), _maxY);

	// houses within allowableDistance trace out a circle. 
	// find houses within allowableDistance above or equal original house.
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
			--curLeftX;
			curLeftAddress = (yy*_width) + curLeftX;
		}

		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX + 1 <= maxX && getDist(origAddress, curRightAddress + 1) <= allowableDist )
		{
			++curRightX;
			curRightAddress = (yy*_width + curRightX);
		}
		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{
			//int address = (yy * _width) + xx;
			House* house = _house_per_address.at((yy * _width) + xx);
			if (notOccupied.find(house) != notOccupied.end())
			{
				nearHouses.insert(house);
			}
		}
	}
	// find houses within allowableDistance below original house
	yy = maxY;
	for (; yy>origY; --yy)
	{
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
			--curLeftX;
			curLeftAddress = (yy*_width) + curLeftX;
		}
		int curRightAddress = (yy*_width) + curRightX;
		while ( curRightX+1 <= maxX && getDist(origAddress, curRightAddress+1) <= allowableDist )
		{
			++curRightX;
			curRightAddress = (yy*_width) + curRightX;
		}

		for (int xx=curLeftX; xx<=curRightX; ++xx)
		{	
			House* house = _house_per_address.at((yy * _width) + xx);
			if (notOccupied.find(house) != notOccupied.end())
			{
				nearHouses.insert(house);
			}
		}
	}

	unsigned int count = 1;
	std::unordered_set<const House*> returnedHouses;
	if (returnedHouses.size() >= count || nearHouses.empty())
	{
		return returnedHouses;
	}

	std::unordered_set<House*>::iterator itr;
	
	//House* currHouse = selectRandom(unoccupiedAndCloseHouses);
	for ( itr = nearHouses.begin(); itr != nearHouses.end(); itr++)
	{
		if (returnedHouses.size() >= count)
		{
			break;
		}
		returnedHouses.insert(*itr);
		//unoccupiedAndCloseHouses.erase(currHouse);
	}

	return returnedHouses;
	// TODO don't erase @house from set.
	//return nearHouses;
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

const House* City_Grid::selectRandom (std::unordered_set<const House*>& setOfHouses) const
{
	int size = setOfHouses.size();
    int r = rand() % size;
    std::unordered_set<const House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
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