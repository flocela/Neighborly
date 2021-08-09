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

std::set<House*> City_Grid::getNearHouses (House* house, double allowableDist) const
{ 
	std::set<House*> nearHouses;

	// create box area around @house. Width and height are 2 x allowableDist
	// and @house is at center.
	int origAddress = house->_address;
	int minX = getMinXLine(get_x(origAddress), allowableDist);
	int maxX = getMaxXLine(get_x(origAddress), allowableDist);
	int minY = getMinYLine(get_y(origAddress), allowableDist);
	int maxY = getMaxYLine(get_y(origAddress), allowableDist);
	
	int topLeftAddress = minX * _width + minY;
	int yDiff = maxY - minY;
	for (int ii=topLeftAddress; ii<=maxX*_width; ii+=_width)
	{	
		for (int jj=0; jj<=yDiff; jj++)
		{	
			int otherAddress = ii + jj;
			if ( otherAddress != origAddress && 
				 dist(origAddress, otherAddress) <= allowableDist )
			{
				nearHouses.insert(_addrToHouseMap.at(otherAddress));
			}
		}
	}
	return nearHouses;
}

int City_Grid::getAddress (int x, int y) const
{
	int address = x * _width + y;
	return address;
}

// May give less than count number of addresses. Maybe area within
// allowableDistance doesn't hold that many addresses.
// Resulting set<int> does not include @address.
std::set<House*> City_Grid::getSomeNearHouses (
        House* house,
        double allowableDistance,
        std::set<House*> occupied,
        int count
    ) const
{	
	// Try to get houses quickly. May not be possible if a larger
	// percentage of houses are occuplied.
	std::set<House*> fastHouses = getSomeNearHousesFastAndRandom(
		house,
		allowableDistance,
		occupied,
		count
	);

	if ( (int)fastHouses.size() > 0)
		return fastHouses;

	return getSomeNearHousesSlowerAndRandom(
		house,
		allowableDistance,
		occupied,
		count
	);
}

std::set<House*> City_Grid::getSomeNearHousesFastAndRandom (
    House* house,
    double allowableDist,
    std::set<House*> occupied,
    int count
) const
{
	std::set<House*> returnedHouses;

	// Houses that are within boxed area around @house.
	std::set<House*> boxedHouses;

	// Width and height of box are 2 x allowableDist and @house is at center.
	int origAddress = house->_address;
	int minX = getMinXLine(get_x(origAddress), allowableDist);
	int maxX = getMaxXLine(get_x(origAddress), allowableDist);
	int minY = getMinYLine(get_y(origAddress), allowableDist);
	int maxY = getMaxYLine(get_y(origAddress), allowableDist);
	int topLeftAddress = minX * _width + minY;
	int yDiff = maxY - minY;
	for (int ii=topLeftAddress; ii<=maxX*_width; ii+=_width)
	{	
		for (int jj=0; jj<=yDiff; jj++)
		{	
			int otherAddress = ii + jj;
			if ( otherAddress != origAddress )
			{
				boxedHouses.insert(_houses[otherAddress].get());
			}
		}
	}

	// Randomly select houses, then check if they are unoccupied and
	// within allowableDist from @house.
	int tries = 0;
	while (true)
	{
		if ( (int)returnedHouses.size() == count || boxedHouses.empty() )
			return returnedHouses;
		
		// If we're not getting an unoccupied house about a third of the time,
		// then a lot of houses are occupied. Do other method.
		if (tries/4 > (int)returnedHouses.size() && tries > 5)
		{
			returnedHouses = {};
			break;
		}
		House* currHouse = selectRandom(boxedHouses);
		if ( occupied.count(currHouse) == 0 &&
			 dist(origAddress, currHouse->_address) <= allowableDist
		)
		{	
			returnedHouses.insert(currHouse);
		}
		boxedHouses.erase(currHouse);
		
		tries++;	
	}

	return returnedHouses;
}

std::set<House*> City_Grid::getSomeNearHousesSlowerAndRandom (
    House* house,
    double allowableDist,
    std::set<House*> occupied,
    int count
) const
{	
	std::set<House*> returnedHouses;

	std::set<House*> unoccupiedNearHouses;
	std::set<House*> nearHouses = getNearHouses(house, allowableDist);
	for ( House* house : nearHouses )
	{	
		if (occupied.count(house) == 0)
			unoccupiedNearHouses.insert(house);
	}
	while ( ( (int)returnedHouses.size() < count ) && ( (int)unoccupiedNearHouses.size() > 0 ) )
	{	
		House* unoccupiedNearHouse = selectRandom(unoccupiedNearHouses);
		returnedHouses.insert(unoccupiedNearHouse);
		unoccupiedNearHouses.erase(unoccupiedNearHouse);
	}
	return returnedHouses;
}

std::set<House*> City_Grid::getEncompassedHouses (
	House* house,
	double allowableDist
) const
{
	std::set<House*> returnHouses;

	int origAddress = house->_address;
	int origX = get_x(origAddress);
	int origY = get_y(origAddress);
	
	// create a box around orig house. calculatedMin and calculatedMax
	// are the corners of box.
	int calculatedMinX = origX - std::floor(allowableDist);
	int calculatedMaxX = origX + std::floor(allowableDist);
	int calculatedMinY = origY - std::floor(allowableDist);
	int calculatedMaxY = origY + std::floor(allowableDist);
	int minX = calculatedMinX < _minX ? _minX : calculatedMinX;
	int maxX = calculatedMaxX > _maxX ? _maxX : calculatedMaxX;
	int minY = calculatedMinY < _minY ? _minY : calculatedMinY;
	int maxY = calculatedMaxY > _maxY ? _maxY : calculatedMaxY;
	
	int topLeftAddress = minX * _width + minY;
	int yDiff = maxY - minY;
	for (int ii=topLeftAddress; ii<=maxX*_width; ii+=_width)
	{	
		for (int jj=0; jj<=yDiff; jj++)
		{	
			int otherAddress = ii + jj;
			if ( otherAddress != origAddress )
			{
				returnHouses.insert(_addrToHouseMap.at(otherAddress));
			}
		}
	}
	return returnHouses;
}

int City_Grid::get_x (const int& address) const
{
	return (address/_width);

}

int City_Grid::get_y (const int& address) const
{
	return (address%_width);
}

int City_Grid::getLargestXCoord () const 
{
	return _maxX;
}
int City_Grid::getLargestYCoord () const
{
	return _maxY;
}
int City_Grid::getLargestHouse () const
{
	return _houses[_houses.size()-1]->_address;
}

double City_Grid::dist (const int& from_address, const int& to_address) const
{
	double x_dist = fabs( get_x(from_address) - get_x(to_address) );
	double y_dist = fabs( get_y(from_address) - get_y(to_address));
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
	std::cout << "CityGrid 308: " << address << " " << get_x(address) << " " << get_y(address) << std::endl;
	return Coordinate{get_x(address), get_y(address)};
}

int City_Grid::getMinXLine (int origX, int allowableDist) const
{
	int calculatedMinX = origX - std::floor(allowableDist);
	return calculatedMinX < _minX ? _minX : calculatedMinX;
}

int City_Grid::getMaxXLine (int origX, int allowableDist) const
{
	int calculatedMaxX = origX + std::floor(allowableDist);
	return calculatedMaxX > _maxX ? _maxX : calculatedMaxX;
}

int City_Grid::getMinYLine (int origY, int allowableDist) const
{
	int calculatedMinY = origY - std::floor(allowableDist);
	return calculatedMinY < _minY ? _minY : calculatedMinY;
}

int City_Grid::getMaxYLine (int origY, int allowableDist) const
{
	int calculatedMaxY = origY + std::floor(allowableDist);
	return calculatedMaxY > _maxY ? _maxY : calculatedMaxY;
}

House* City_Grid::selectRandom (std::set<House*>& setOfHouses) const
{
	int size = setOfHouses.size();
    int r = rand() % size;
    std::set<House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    return *it;
}

int City_Grid::selectRandom (std::set<int>& setOfInts) const
{
	int size = setOfInts.size();
    int r = rand() % size;
    std::set<int>::iterator it = std::begin(setOfInts);
    std::advance(it, r);
    return *it;
}
