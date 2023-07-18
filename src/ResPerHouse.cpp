#include "ResPerHouse.h"

using namespace std;

void ResPerHouse::insert(pair<const House*, const Resident*> houseAndResident)
{
    _res_per_house.insert(houseAndResident);
}

bool ResPerHouse::contains (const House* house) const
{
    return _res_per_house.find(house) != _res_per_house.end();
}

const Resident* ResPerHouse::at(const House* house) const
{
    return _res_per_house.at(house);
}

std::unordered_map<const House*, const Resident*>::const_iterator ResPerHouse::cbegin() const noexcept
{
    return _res_per_house.cbegin();
}

std::unordered_map<const House*, const Resident*>::const_iterator ResPerHouse::cend() const noexcept
{
    return _res_per_house.cend();
}

std::unordered_map<const House*, const Resident*>::const_iterator ResPerHouse::begin() const noexcept
{
    return _res_per_house.begin();
}

std::unordered_map<const House*, const Resident*>::const_iterator ResPerHouse::end() const noexcept
{
    return _res_per_house.end();
}

void ResPerHouse::reserve (int size)
{
    _res_per_house.reserve(size);
}

bool ResPerHouse::operator== (const ResPerHouse& o) const
{
    return _res_per_house == o._res_per_house;
}
