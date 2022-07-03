#include "City_Grid.h"
#include <iostream>
#include <math.h>


City_Grid::City_Grid (int width):
	City(),
	_width{width},
	_maxX{_width },
	_maxY{_width }
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

double City_Grid::dist (const int& fromAddress, const int& toAddress) const
{
	double x_dist = fabs( get_x(fromAddress) - get_x(toAddress) );
	double y_dist = fabs( get_y(fromAddress) - get_y(toAddress));
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}

std::set<House*> City_Grid::getAdjacentHouses (House* house) const
{
	int address = house->getAddress();
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



std::set<House*> City_Grid::getHousesWithinDistance (
	House* house, 
	double allowableDist
) const
{ 
	std::set<House*> nearHouses;

	// create box area around @house. Width and height are 2 x allowableDist
	// and @house is at center.
	int origAddress = house->getAddress();
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

std::set<House*> City_Grid::getHousesWithinBoxedDistance (
            House* house,
            double allowableDist
) const
{
	std::set<House*> boxedHouses;
	int origAddress = house->getAddress();
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
	return boxedHouses;
}

std::set<House*> City_Grid::getNumberOfUnoccupiedNearHouses (
	House* origHouse,
	double allowableDistance,
	std::set<House*> notOccupied,
	int count
) const
{	
	std::set<House*> returnedHouses;

	if (count == 0)
		return returnedHouses;
	
	// First possibleHouses consists of houses within a boxed distance from
	// @origHouse.
	std::set<House*> possibleHouses = getHousesWithinBoxedDistance (
		origHouse,
		allowableDistance
	);

	int tries = 0;
	while (true)
	{
		if ( (int)returnedHouses.size() == count || possibleHouses.empty() )
			return returnedHouses;
		
		// If we're not getting an unoccupied house within the allowable distance 
		// about a quarter of the time, then most boxed houses are occupied or
		// are not within the allowable distance. 
		// Break, then remove occupied houses and houses farther than allowable distance
		// from boxedHouses, then continue.
		int houseAddress = origHouse->getAddress();
		if ( tries/4 > (int)returnedHouses.size() && tries > 5 )
		{
			break;
		}
		House* currHouse = selectRandom(possibleHouses);
		if ( notOccupied.count(currHouse) > 0 &&
			 dist(currHouse->getAddress(), houseAddress) <= allowableDistance )
		{
			returnedHouses.insert(currHouse);
			possibleHouses.erase(currHouse);
		}
		++tries;
	}

	// This is a continuation from the break caused by not selecting unoccupied houses
	// with allowable distance often enough. Go through possibleHouses and remove
	// occupied houses and houses farther than allowable distance from origHouse.
	std::set<House*> decreasedPossibleHouses;
	int origHouseAddress = origHouse->getAddress();
	for ( House* boxedHouse : possibleHouses )
	{
		if ( notOccupied.count(boxedHouse) > 0 &&
			 dist(boxedHouse->getAddress(), origHouseAddress) <= allowableDistance )
		{
			decreasedPossibleHouses.insert(boxedHouse);
		}
	}
	possibleHouses = decreasedPossibleHouses;
	while (true) // TODO these while(trues) seem unsafe.
	{
		if ( (int)returnedHouses.size() == count || possibleHouses.empty() )
			return returnedHouses;
		House* currHouse = selectRandom(possibleHouses);
		returnedHouses.insert(currHouse);
		possibleHouses.erase(currHouse);
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

