#include "City_Grid.h"
#include <iostream>
#include <math.h>

// _width is the width of the grid.
// The x axis goes from left to right.
// The y axis goes from top to bottom.
// A _width of 3 would result in
// 0  3  6
// 1  4  7
// 2  5  8
// Address 3 is 2 units away from address 5 in the y direction.
// Address 1 is 2 units away from address 7 in the x direction.
City_Grid::City_Grid (int width):
	City(),
	_width{width},
	_addresses(width*width)
{
  	for (int ii=0; ii<width; ++ii)
  	{
  		for (int jj=0; jj<width; ++jj)
        {
          _addresses[ (ii*width) + jj] = ii * width + jj;
        }
  	}
}

int City_Grid::getSize() const
{
	return _addresses.size();
}

std::vector<int> City_Grid::getAddresses () const
{
	return _addresses;
}

std::vector<int> City_Grid::getAdjacentAdresses (int address) const
{
	int x = get_x(address);
	int y = get_y(address);
	int lastIdx_x = _width - 1;
	int lastIdx_y = _width - 1;

	std::vector<int> adjacentAddresses = {};
	if (x != 0)
	{
		adjacentAddresses.push_back(address - _width);
		if (y != 0)
			adjacentAddresses.push_back(address - _width - 1);
		if (y != lastIdx_y)
			adjacentAddresses.push_back(address - _width + 1);
	}
	if (x != lastIdx_x)
	{
		adjacentAddresses.push_back(address + _width);
		if (y != 0)
			adjacentAddresses.push_back(address + _width - 1);
		if (y != lastIdx_y)
			adjacentAddresses.push_back(address + _width + 1);
	}
	if (y != 0)
		adjacentAddresses.push_back(address - 1);
	if (y != lastIdx_y)
		adjacentAddresses.push_back(address +1);
	return adjacentAddresses;
}

// Does not include @address that is given in result.
std::set<int> City_Grid::getCloseAddresses (int address, double distance) const
{  
	std::pair<int, double> addressAndDistance{address, distance};
	std::set<int> closeAddresses;
	int x = get_x(address);
	int y = get_y(address);
	int minX = x - std::floor(distance);
	int maxX = x + std::floor(distance);
	int minY = y - std::floor(distance);
	int maxY = y + std::floor(distance);
	int topLeftAddress = minX * _width + minY;
	int yDiff = maxY - minY;
	for (int ii=topLeftAddress; ii<=maxX; ii++)
	{
		for (int jj=0; jj<yDiff; jj++)
		{
			int otherAddress = ii + jj;
			double farAway = dist(address, otherAddress);
			if (farAway <= distance)
			{
				closeAddresses.insert(otherAddress);
			}
		}
	}
	closeAddresses.erase(address);
	return closeAddresses;
}

int City_Grid::getAddress (int x, int y) const
{
	int address = x * _width + y;
	return address;
}

std::set<std::pair<int, int>>::iterator City_Grid::selectRandom(
	const std::set<std::pair<int, int>> &s,
    size_t n
) const
{
    std::set<std::pair<int, int>>::iterator it = std::begin(s);
    std::advance(it, n);
    return it;
}

std::set<int> City_Grid::convertVectorToSet (std::vector<int> ints) const
{
	std::set<int> returnSet;
	for (int ii : ints)
	{
		returnSet.insert(ii);
	}
	return returnSet;
}

// May give less than count number of addresses. Maybe area within
// allowableDistance doesn't hold that many addresses.
// Does not include @address that is given in result.
std::set<int> City_Grid::getCloseAddresses (
    int address,
    double allowDistance,
    std::set<int> occupiedAddresses,
    int count
) const
{
	std::set<int> returnAddresses;
	int x = get_x(address);
	int y = get_y(address);
	int minX = x - std::floor(allowDistance);
	int maxX = x + std::floor(allowDistance);
	int minY = y - std::floor(allowDistance);
	int maxY = y + std::floor(allowDistance);
	std::set<std::pair<int, int>> gridAddresses =
		getSetAddresses(minX, maxX, minY, maxY);
	gridAddresses.erase(std::pair<int, int>(x, y));
	while (count != 0)
	{
		if (gridAddresses.size() == 0)
			break;
		std::set<std::pair<int, int>>::iterator itA = 
			selectRandom(gridAddresses, gridAddresses.size());
		std::pair<int, int> xyPair = *itA;
		int currAddress = getAddress(xyPair.first, xyPair.second);
		double distFromAddress = dist(address, currAddress);
		if (distFromAddress < allowDistance && 
			occupiedAddresses.count(currAddress) == 0
		)
		{
			occupiedAddresses.insert(currAddress); // TODO not really necessary
			returnAddresses.insert(currAddress);
			--count;
		}
		gridAddresses.erase(xyPair);
		count--;
	}
	return returnAddresses;
}

std::set<std::pair<int, int>> City_Grid::getSetAddresses (
    int minX,
    int maxX,
    int minY,
    int maxY
) const
{	
	std::set<std::pair<int, int>> addresses;
	for (int xx=minX; xx<=maxX; ++xx)
	{
		for (int yy=minY; yy<=maxY; ++yy)
		{
			addresses.insert(std::pair<int, int>(xx, yy));
		}
	}
	return addresses;
}

int City_Grid::get_x (const int& address) const
{
	return (address/_width);

}

int City_Grid::get_y (const int& address) const
{
	return (address%_width);
}

double City_Grid::dist (const int& from_address, const int& to_address) const
{
	double x_dist = fabs(get_x(from_address - to_address));
	double y_dist = fabs(get_y(from_address - to_address));
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}

bool City_Grid::equals (const City_Grid& other) const{
  	if ( other.getAddresses().size() == this->getAddresses().size() )
      return true;
	return false;
}

Coordinate City_Grid::getCoordinate(const int& address) const
{
	return Coordinate{get_x(address), get_y(address)};
}