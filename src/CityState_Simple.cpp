#include "CityState_Simple.h"

#include <algorithm>
#include "Coordinate.h"

using namespace std;

CityState_Simple::CityState_Simple (
    const City* city
): _city{city},
    _open_houses_per_y_x(_city->getHeight(),
                        vector<unordered_set<const House*>>( ((_city->getWidth()-1)/10)+1 ))
{
    //TODO reserve space for _open_houses
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {
        Coordinate xy = _city->getCoordinate(house->getAddress());
        int x = xy.getX();
        int y = xy.getY();
        _open_houses_per_y_x[y][x/10].insert(house);
    }
}

void CityState_Simple::moveOut (Resident* resident)
{
    if (_house_per_resident.find(resident) != _house_per_resident.end())
    {   
        const House* oldHouse = _house_per_resident[resident];

        _house_per_resident.erase(resident);
        _resident_per_house.erase(oldHouse);
        Coordinate co = _city->getCoordinate(oldHouse->getAddress());
        _open_houses_per_y_x[co.getY()][co.getX()/10].insert(oldHouse);
    }
}

void CityState_Simple::moveIn (Resident* resident, const House* newHouse)
{   
    if (_resident_per_house.find(newHouse) == _resident_per_house.end() ||
        _house_per_resident.find(resident) == _house_per_resident.end())
    {
        _resident_per_house.insert({newHouse, resident});
        _house_per_resident.insert({resident, newHouse});

        Coordinate co = _city->getCoordinate(newHouse->getAddress());

        if (_open_houses_per_y_x[co.getY()][co.getX()/10].find(newHouse) !=
            _open_houses_per_y_x[co.getY()][co.getX()/10].end())
        {
            _open_houses_per_y_x[co.getY()][co.getX()/10].erase(newHouse);
        }
    }
}

void CityState_Simple::moveInAndOutOfHouse (Resident* resident, const House* newHouse)
{
    if (_house_per_resident.find(resident) != _house_per_resident.end() &&
        _resident_per_house.find(newHouse) == _resident_per_house.end() )
    {
        moveOut(resident);
        moveIn(resident, newHouse);
    }
}

vector<const House*> CityState_Simple::getOpenHousesWithinRange (
    double centerX,
    double centerY,
    double allowableDistance)const
{   
    // TODO ask city for minimum x and minimum y instead of getWidth and getHeight
    double minX = std::max(centerX - allowableDistance, 0.0);
    double maxX = std::min(centerX + allowableDistance, (double)_city->getWidth() - 1);
    double minY = std::max(centerY - allowableDistance, 0.0);
    double maxY = std::min(centerY + allowableDistance, (double)_city->getHeight() - 1);

    vector<const House*> openHousesInRange{};
    
    for (int y=minY; y<=maxY; ++y)
    {
        for (int x=minX/10; x<=maxX/10; ++x)
        {
            for (const House* house : _open_houses_per_y_x[y][x])
            {  
                Coordinate houseCoord = _city->getCoordinate(house->getAddress());
                if (_city->getDist(houseCoord.getX(), houseCoord.getY(), centerX, centerY) <=
                    allowableDistance)
                {
                    openHousesInRange.push_back(house);
                }
            }
        }
    }
    return openHousesInRange;
}

unordered_set<const House*> CityState_Simple::getOpenHouses() const
{
    unordered_set<const House*> allOpenHouses{};
    for (auto v : _open_houses_per_y_x)
    {
        for (unordered_set<const House*> sh : v)
        {
            for (const House* h : sh)
            {
                allOpenHouses.insert(h);
            }
        }
    }
    return allOpenHouses;
}

unordered_map<const House*, Resident*> CityState_Simple::getResidentsPerHouse () const
{
    return _resident_per_house;
}

const House* CityState_Simple::getHousePerResident(Resident* resident) const
{
    if (_house_per_resident.find(resident) != _house_per_resident.end())
    {
        return _house_per_resident.at(resident);
    }
    return nullptr;
}

Resident* CityState_Simple::getResidentPerHouse(const House* house) const
{
    if (_resident_per_house.find(house) != _resident_per_house.end())
    {
        return _resident_per_house.at(house);
    }
    return nullptr;
}


