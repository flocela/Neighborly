#include "City_Grid.h"

//TODO delete chrono, only here for testing

#include <chrono>
#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

// This class has to be tested.
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

double City_Grid::getDist (
        const double firstX,
        const double firstY,
        const double secondX,
        const double secondY) const 
	{
		double x_dist = fabs(firstX - secondX);
		double y_dist = fabs(firstY - secondY);
		return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
	}

// TODO does this work with allowable distance == 0?
unordered_set<const House*> City_Grid::getHousesWithinDistance (
        const House* house,
        double allowableDist,
		int run
    ) const
{	(void)run;
	int central_address = house->getAddress();

	int central_address_x = get_x(central_address);
	int central_address_y = get_y(central_address);

	double rAllowableSquared = allowableDist * allowableDist;
	// start at center row and increase the abs distance in the y direction.
	int diffFromCenterRowY = 0;

	// from central column of circle, x absolute distance to edge of circle.
	int diffToEdgeX = (int)floor(allowableDist);

	_houses_within_distance[{allowableDist, central_address}] = unordered_set<const House*>{};

	while (diffFromCenterRowY <= allowableDist)
	{
		double rSquared = (diffToEdgeX * diffToEdgeX) + (diffFromCenterRowY * diffFromCenterRowY);
		while ( rSquared > rAllowableSquared )
		{
			--diffToEdgeX;
			rSquared = (diffToEdgeX * diffToEdgeX) + (diffFromCenterRowY * diffFromCenterRowY);
		}

		int left = (central_address_x - diffToEdgeX < _minX)?
				_minX : central_address_x - diffToEdgeX;

		int right = (central_address_x + diffToEdgeX > _maxX)?
				_maxX : central_address_x + diffToEdgeX;

		if (diffFromCenterRowY == 0)// add only one row of houses
		{
			for (int x = left; x <= right; ++x)
			{
				const House* h = _house_per_address.at(central_address_y * _width + x);
				_houses_within_distance[{allowableDist,house->getAddress()}].insert(h);
			}
		}
		else
		{
			// row above
			if (central_address_y - diffFromCenterRowY >= _minY)
			{
				for (int x = left; x <= right; ++x)
				{
					const House* h = _house_per_address.
						at(((central_address_y - diffFromCenterRowY) * _width ) + x);
					_houses_within_distance[{allowableDist,house->getAddress()}].insert(h);
				}
			}
			
			// row below
			if (central_address_y + diffFromCenterRowY <= _maxY)
			{
				for (int x = left; x <= right; ++x)
				{
					const House* h = _house_per_address.
						at(((central_address_y + diffFromCenterRowY) * _width ) + x);
					_houses_within_distance[{allowableDist,house->getAddress()}].insert(h);
				}
			}
		}

		++ diffFromCenterRowY;
	}

	// don't include central house as a neighbor. We only want the neighbors of central house.
	if (_houses_within_distance.find({allowableDist, house->getAddress()}) != 
		_houses_within_distance.end())
	{
		_houses_within_distance[{allowableDist, house->getAddress()}].erase(house);
	}

	return _houses_within_distance[{allowableDist,house->getAddress()}];
}

pair<int, int> City_Grid::getXRangeForAllowableDistanceToHouse (
    const House* house,
    double allowableDist
) const
{
	int central_address = house->getAddress();
	int central_address_x = get_x(central_address);
	int minX = max(central_address_x - (int)floor(allowableDist), _minX);
	int maxX = min(central_address_x + (int)floor(allowableDist), _maxX);
	return pair<int, int> {minX, maxX};
}

pair<int, int> City_Grid::getYRangeForAllowableDistanceToHouse (
    const House* house,
    double allowableDist
) const
{
	int central_address = house->getAddress();
	int central_address_y = get_y(central_address);
	int minY = max(central_address_y - (int)floor(allowableDist), _minY);
	int maxY = min(central_address_y + (int)floor(allowableDist), _maxY);
	return pair<int, int> {minY, maxY};
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

unordered_set<const House*> City_Grid::getHousesAdjacent (int address) const
{	
	if ( _adjacent_houses_per_house_address.find(address) != _adjacent_houses_per_house_address.end())
	{
		return _adjacent_houses_per_house_address[address];
	}
	
	unordered_set<const House*> adjacentHouses = {};

	Coordinate coord = getCoordinate(address);
	int addr_x = coord.getX();
	int addr_y = coord.getY();
	
	if (addr_y > 0)
	{
		if (addr_x > 0)
		{
			adjacentHouses.insert(_houses[address - _width - 1].get());
		}

		adjacentHouses.insert(_houses[address-_width].get());

		if (addr_x <= _width-1)
		{
			adjacentHouses.insert(_houses[address - _width + 1].get());
		}
	}

	if (addr_x > 0)
	{
		adjacentHouses.insert(_houses[address - 1].get());
	}

	if (addr_x <= _width-1)
	{
		adjacentHouses.insert(_houses[address + 1].get());
	}

	if (addr_y <= _width-1)
	{
		if (addr_x > 0)
		{
			adjacentHouses.insert(_houses[address + _width - 1].get());
		}

		adjacentHouses.insert(_houses[address +_width].get());

		if (addr_x <= _width-1)
		{
			adjacentHouses.insert(_houses[address + _width + 1].get());
		}
	}

	_adjacent_houses_per_house_address[address] = adjacentHouses;

	return adjacentHouses;
}

std::string City_Grid::toString (const std::unordered_map<int, char>& characterPerAddress) const
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