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
	_maxX{_width - 1},
	_maxY{_width - 1}
{	
	_houses.reserve(_width * _width);
  	for (int ii=0; ii<width; ++ii)
  	{
  		for (int jj=0; jj<width; ++jj)
        { 
		  int addr = (ii*width) + jj;
          _houses.push_back(std::make_unique<House>(addr));
		  _addrToHouseMap[addr] = (_houses[addr]).get();
        }
  	}
}

int City_Grid::getSize() const
{
	return _houses.size();
}

std::vector<House*> City_Grid::getHouses () const
{	std::vector<House*> houses;
	for (auto& house : _houses) // TODO maybe const auto&
	{	
		houses.push_back(house.get());
	}
	return houses;
}

std::set<House*> City_Grid::getAdjacentHouses (House* house) const
{
	std::cout<< "City_Grid 48 house is nullptr " << (house == nullptr) << std::endl;
	int address = house->_address;
	int x = get_x(address);
	int y = get_y(address);
	int lastIdx_x = _width - 1;
	int lastIdx_y = _width - 1;
	
	std::set<House*> adjacentHouses = {};
	if (x != 0)
	{
		adjacentHouses.insert(_addrToHouseMap.at(address - _width));
		if (y != 0)
			adjacentHouses.insert(_addrToHouseMap.at(address - _width - 1));
		if (y != lastIdx_y)
			adjacentHouses.insert(_addrToHouseMap.at(address - _width + 1));
	}
	if (x != lastIdx_x)
	{
		adjacentHouses.insert(_addrToHouseMap.at(address + _width));
		if (y != 0)
			adjacentHouses.insert(_addrToHouseMap.at(address + _width - 1));
		if (y != lastIdx_y)
			adjacentHouses.insert(_addrToHouseMap.at(address + _width + 1));
	}
	if (y != 0)
		adjacentHouses.insert(_addrToHouseMap.at(address - 1));
	if (y != lastIdx_y)
		adjacentHouses.insert(_addrToHouseMap.at(address + 1));
	return adjacentHouses;
}

// Resulting set<int> does not include @address.
std::set<House*> City_Grid::getNearHouses (House* house, double distance) const
{ 
	int origAddress = house->_address;
	std::set<House*> closeAddresses;
	int x = get_x(origAddress);
	int y = get_y(origAddress);
	int calculatedMinX = x - std::floor(distance);
	int calculatedMaxX = x + std::floor(distance);
	int calculatedMinY = y - std::floor(distance);
	int calculatedMaxY = y + std::floor(distance);
	int minX = calculatedMinX < _minX ? _minX : calculatedMinX;
	int maxX = calculatedMaxX > _maxX ? _maxX : calculatedMaxX;
	int minY = calculatedMinY < _minY ? _minY : calculatedMinY;
	int maxY = calculatedMaxY > _maxY ? _maxY : calculatedMaxY;
	int topLeftAddress = minX * _width + minY;
	int yDiff = maxY - minY;
	for (int ii=topLeftAddress; ii<=maxX; ii++)
	{
		for (int jj=0; jj<yDiff; jj++)
		{	
			int otherAddress = ii + jj;
			double farAway = dist(origAddress, otherAddress);
			if (farAway <= distance && otherAddress != origAddress)
			{
				closeAddresses.insert(_addrToHouseMap.at(otherAddress));
			}
		}
	}
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

// May give less than count number of addresses. Maybe area within
// allowableDistance doesn't hold that many addresses.
// Resulting set<int> does not include @address.
std::set<House*> City_Grid::getNearHouses (
        House* house,
        double distance,
        std::set<House*> occupied,
        int count
    ) const
{	
	int origAddress = house->_address;
	std::set<House*> returnHouses;
	int x = get_x(origAddress);
	int y = get_y(origAddress);
	int calculatedMinX = x - std::floor(distance);
	int calculatedMaxX = x + std::floor(distance);
	int calculatedMinY = y - std::floor(distance);
	int calculatedMaxY = y + std::floor(distance);
	int minX = calculatedMinX < _minX ? _minX : calculatedMinX;
	int maxX = calculatedMaxX > _maxX ? _maxX : calculatedMaxX;
	int minY = calculatedMinY < _minY ? _minY : calculatedMinY;
	int maxY = calculatedMaxY > _maxY ? _maxY : calculatedMaxY;
	 
	std::set<House*> subsetOfHouses = getEncompassedHouses(minX, maxX, minY, maxY);
	while (count != 0)
	{
		if (subsetOfHouses.size() == 0)
			break;
		House* currHouse = selectRandom(subsetOfHouses);
		int currAddress = house->_address;
		double distFromAddress = dist(origAddress, currAddress);
		if (distFromAddress < distance && 
			occupied.count(currHouse) == 0 &&
			currAddress != origAddress
		)
		{
			occupied.insert(currHouse); // TODO not really necessary
			returnHouses.insert(currHouse);
			--count;
		}
		count--;
	}
	return returnHouses;
}

House* City_Grid::selectRandom (std::set<House*>& setOfHouses) const
{
	int size = setOfHouses.size();
    int r = rand() % size;
    std::set<House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    setOfHouses.erase(*it);
    return *it; // TODO this isn't going to work because I erase it first!!
}

std::set<House*> City_Grid::getEncompassedHouses (
    int minX,
    int maxX,
    int minY,
    int maxY
) const
{	
	std::set<House*> houses;
	for (int xx=minX; xx<=maxX; ++xx)
	{
		for (int yy=minY; yy<=maxY; ++yy)
		{	
			houses.insert(_addrToHouseMap.at(getAddress(xx, yy)));
		}
	}
	return houses;
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

// TODO is this ever used.
bool City_Grid::equals (const City_Grid& other) const{
  	if ( other._houses.size() == this->_houses.size() )
      return true;
	return false;
}

Coordinate City_Grid::getCoordinate(const int& address) const
{
	return Coordinate{get_x(address), get_y(address)};
}