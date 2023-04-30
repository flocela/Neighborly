#include "CityState_Simple.h"

#include "Coordinate.h"

using namespace std;

CityState_Simple::CityState_Simple (
    const City* city
): _city{city},
    _open_houses_per_y_x(_city->getHeight()+1,
                        vector<unordered_set<const House*>>( ((_city->getWidth()-1)/10)+1 ))
{
    //TODO reserve space for _open_houses
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {
        Coordinate xy = _city->getCoordinate(house->getAddress());
        int x = xy.getX();
        int y = xy.getY();
        //cout <<"CityState_Simple DD" << endl;
        _open_houses_per_y_x[y][x/10].insert(house);
    }
    //cout <<"CityState_Simple EE" << endl;
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

unordered_set<const House*> CityState_Simple::getOpenHousesWithinRange (
        double minX,
        double maxX,
        double minY,
        double maxY)const
{   
    unordered_set<const House*> openHousesInRange{};
    for (int y=minY; y<=maxY; ++y)
    {
        for (int x=minX/10; x<=maxX/10; ++x)
        {
            for (const House* house : _open_houses_per_y_x[y][x])
            {  
                Coordinate coord = _city->getCoordinate(house->getAddress());
                if (coord.getX() >= minX && coord.getX() <= maxX &&
                    coord.getY() >= minY && coord.getY() <= maxY)
                {
                    openHousesInRange.insert(house);
                }
            }
        }
    }
    return openHousesInRange;
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


