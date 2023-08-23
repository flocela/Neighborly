#include "City_Grid.h"

#include <iostream>
#include <cmath>

using namespace std;

City_Grid::City_Grid (int width)
:
	City(),
	_width{width},
	_maxX{_width - 1},
	_maxY{_width - 1}
{	
	_houses.reserve(_width * _width);
	_house_per_address.reserve(_houses.size());
	_coordinates_per_house.reserve(_houses.size());
  	for (int ii=0; ii<width; ++ii)
  	{
  		for (int jj=0; jj<width; ++jj)
        { 
		  int addr = (ii*width) + jj;
          _houses.emplace_back(make_unique<House>(addr));
		  _house_per_address.insert({addr, _houses[addr].get()});
		  _coordinates_per_house.insert({_houses[addr].get(), Coordinate(ii, jj)});
        }
  	}

	_adjacent_houses_per_house.reserve(_houses.size());
	for (auto& house : _houses)
	{
		_adjacent_houses_per_house.insert(house.get(), move(getHousesAdjacent(house->getAddress())));
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

const unordered_map<const House*, Coordinate>* City_Grid::getCoordinatesPerHouse() const
{
	return &_coordinates_per_house;
}

double City_Grid::getDist (const int& fromAddress, const int& toAddress) const
{
	double x_dist = fabs( get_x(fromAddress) - get_x(toAddress) );
	double y_dist = fabs( get_y(fromAddress) - get_y(toAddress) );
  	return sqrt( (x_dist * x_dist) + (y_dist * y_dist));
}

unordered_set<const House*> City_Grid::getHousesWithinDistance (
        const House* centralHouse,
        double allowableDist
    ) const
{	
	int centralAddress = centralHouse->getAddress();

	// If houses within allowable distance have already been recorded, then return them.
	if (_houses_within_distance.find({allowableDist, centralAddress}) !=
		_houses_within_distance.end())
	{
		return _houses_within_distance[{allowableDist, centralAddress}];
	}
	
	// Else determine set of houses within allowable distance of the central house.
	// Save them in _houses_within_distance.
	_houses_within_distance[{allowableDist, centralAddress}] = unordered_set<const House*>{};
	
	int central_address_x = get_x(centralAddress);
	int central_address_y = get_y(centralAddress);

	double allowableDistSquared = allowableDist * allowableDist;

	// Start at central row. Then travel one row in the positive and negative y directions.
	// (So examine one row above and one row below the central row.) Then iterate, always
	// traveling one row in the positive and negative y directions, examining two rows each time.
	// For each row, find the farthest x-distances from the central x, where the resulting radius 
	// is still within the allowable distance. The two x-distances are to the left and right of 
	// the central x, where the central house is.

	// Difference from central row in the y directions.
	int diffFromCenterRowY = 0;

	// Difference from central column in the left and right directions. This starts at the
	// edges and moves in until the resultant rSquared distance is equal or less than the
	// allowable distance.
	int diffFromCenterColX = allowableDist;

	// Continue to increase diffFromCentralRowY until it is larger than the allowable distance. 
	while (diffFromCenterRowY <= allowableDist)
	{
		// current distance squared = (x * x) + (y * y)
		double rSquared = (diffFromCenterColX * diffFromCenterColX) +
			    		  (diffFromCenterRowY * diffFromCenterRowY);

		// Continue to decrease diffFromCenterColX until rSquared <= allableDistSquared
		while ( rSquared > allowableDistSquared )
		{
			--diffFromCenterColX;
			rSquared = (diffFromCenterColX * diffFromCenterColX) +
				(diffFromCenterRowY * diffFromCenterRowY);
		}

		// Left most house should be diffFromCenterColX from the central address in the
		// x-direction, but diffFromCenterColX from the central address may be off the grid.
		int left = central_address_x - diffFromCenterColX;
		left = (left < _minX)? _minX : left;

		int right = central_address_x + diffFromCenterColX;
		right = (right > _maxX)? _maxX : right;

		if (diffFromCenterRowY == 0)// add only one row of houses
		{
			for (int x = left; x <= right; ++x)
			{
				const House* h = _house_per_address.at(central_address_y * _width + x);
				_houses_within_distance[{allowableDist,centralHouse->getAddress()}].insert(h);
			}
		}
		else
		{
			// Row above
			// The central_address_y minus diffFromCenterRowY may be off the top of the grid.
			if (central_address_y - diffFromCenterRowY >= _minY)
			{
				for (int x = left; x <= right; ++x)
				{
					const House* h = _house_per_address.
						at(((central_address_y - diffFromCenterRowY) * _width ) + x);
					_houses_within_distance[{allowableDist,centralHouse->getAddress()}].insert(h);
				}
			}
			
			// Row below
			if (central_address_y + diffFromCenterRowY <= _maxY)
			{
				for (int x = left; x <= right; ++x)
				{
					const House* h = _house_per_address.
						at(((central_address_y + diffFromCenterRowY) * _width ) + x);
					_houses_within_distance[{allowableDist,centralHouse->getAddress()}].insert(h);
				}
			}
		}

		++ diffFromCenterRowY;
	}

	// Don't include central house as a neighbor. We only want the neighbors of central house.
	if (_houses_within_distance.find({allowableDist, centralHouse->getAddress()}) != 
		_houses_within_distance.end())
	{
		_houses_within_distance[{allowableDist, centralHouse->getAddress()}].erase(centralHouse);
	}

	return _houses_within_distance[{allowableDist,centralHouse->getAddress()}];
}

size_t City_Grid::getNumOfHouses() const
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
	unordered_set<const House*> adjacentHouses = {};

	Coordinate coord = getCoordinate(address);
	int addr_x = coord.getX();
	int addr_y = coord.getY();
	
	// If address is not in top row of grid.
	if (addr_y > 0)
	{
		if (addr_x > 0)
		{
			adjacentHouses.insert(_houses[address - _width - 1].get());
		}

		adjacentHouses.insert(_houses[address-_width].get());

		if (addr_x < _width-1)
		{
			adjacentHouses.insert(_houses[address - _width + 1].get());
		}
	}

	// If address is not in bottom most row of grid.
	if (addr_y < _width-1)
	{
		if (addr_x > 0)
		{
			adjacentHouses.insert(_houses[address + _width - 1].get());
		}

		adjacentHouses.insert(_houses[address +_width].get());

		if (addr_x < _width-1)
		{
			adjacentHouses.insert(_houses[address + _width + 1].get());
		}
	}
	
	// If address is not in left most column of grid.
	if (addr_x > 0)
	{
		adjacentHouses.insert(_houses[address - 1].get());
	}

	// If address is not in right most column of grid.
	if (addr_x < _width-1)
	{
		adjacentHouses.insert(_houses[address + 1].get());
	}

	return adjacentHouses;
}

const SetOfHousesPerHouse* City_Grid::getAdjacentHousesPerHouse () const
{
	return &_adjacent_houses_per_house;
}

int City_Grid::get_x (const int& address) const
{
	return (address%_width);
}

int City_Grid::get_y (const int& address) const
{
	return (address/_width);
}