#include "SetOfHousesPerHouse.h"

using namespace std;

void SetOfHousesPerHouse::insert(const House* house, const House* houseInSet)
{
    if (_set_of_houses_per_house.find(house) == _set_of_houses_per_house.end())
    {
        _set_of_houses_per_house.insert({house, unordered_set<const House*>{}});
    }
    _set_of_houses_per_house[house].insert(houseInSet);
}

bool SetOfHousesPerHouse::containsKey (const House* house) const
{
    return _set_of_houses_per_house.find(house) != _set_of_houses_per_house.end();
}

const unordered_set<const House*>* SetOfHousesPerHouse::at(const House* house) const
{
    return &(_set_of_houses_per_house.at(house));
}

sohph::const_iterator SetOfHousesPerHouse::cbegin() const noexcept
{
    return _set_of_houses_per_house.cbegin();
}

sohph::const_iterator SetOfHousesPerHouse::cend() const noexcept
{
    return _set_of_houses_per_house.cend();
}

sohph::const_iterator SetOfHousesPerHouse::begin() const noexcept
{
    return _set_of_houses_per_house.begin();
}

sohph::const_iterator SetOfHousesPerHouse::end() const noexcept
{
    return _set_of_houses_per_house.end();
}

void SetOfHousesPerHouse::reserve (int size)
{
    _set_of_houses_per_house.reserve(size);
}

bool SetOfHousesPerHouse::operator== (const SetOfHousesPerHouse& o) const
{
    return _set_of_houses_per_house == o._set_of_houses_per_house;
}
