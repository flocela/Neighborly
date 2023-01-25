#include "Simulator_Basic_A.h"
#include <iostream>

using namespace std;

Simulator_Basic_A::Simulator_Basic_A (City* city, set<Resident*> residents):
    _city{city}, _residents{residents}
{   
    for (const House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

unordered_map<const House*, Resident*> Simulator_Basic_A::simulate ()
{   
    if (!_first_simulation_done)
    {   
        firstSimulation();
        _first_simulation_done = true;
    }
    else
    {  
        int count  = 0;
        for (Resident* res : _residents)
        {   
            if ( calculateHappinessValueFor(res, _house_per_resident_map[res]->getAddress()) <
                res->getHappinessGoal() )
            {
                moveResident(res);
                ++count;
            }
        }
    }
    
    setHappinessValuesForAllResidents();

    return _res_per_house_map;
}

void Simulator_Basic_A::firstSimulation ()
{   
    for (Resident* res : _residents)
    {   
        const House* house = selectRandom(_open_houses);
        
        _res_per_house_map.insert(pair<const House*, Resident*>(house, res));
        
        _house_per_resident_map.insert(pair<Resident*, const House*>(res, house));
        
        _open_houses.erase(house);
        
    }

}

void Simulator_Basic_A::moveResident (Resident* res)
{  
    const House* currHouse = _house_per_resident_map[res];
    
    unordered_set<const House*> nearHouses = _city->findHousesWithinDistance
    (   
        currHouse,
        res->getAllowedMovementDistance()
    );
    
    if (nearHouses.size() == 0)
    {
        
        // no houses to move to.
        return;
    }
    else
    {  
        // remove houses in nearHouses set that are not open. 
        // res can't move into houses that are occupied even if they are near.
        unordered_set<const House*>::iterator iter = nearHouses.begin();
        while (iter != nearHouses.end())
        {   
            if (_open_houses.find(*iter) == _open_houses.end())
            {   
                unordered_set<const House*>::iterator copy = iter;
                ++iter;
                nearHouses.erase(*copy);
            }
            else
            {
                ++iter;
            }
        }
        int count = _count;
        while (count > 0)
        {  
            if (nearHouses.size() == 0)
            {
                break; // TODO maybe return;
            }
            const House* randomHouse = selectRandom(nearHouses);
            
            if (calculateHappinessValueFor(res, randomHouse->getAddress()) > res->getHappinessGoal() )
            {   
                moveResidentIntoHouse(res, randomHouse);
                break;
            }
            --count;
        }
    }
}

void Simulator_Basic_A::moveResidentIntoHouse (Resident* res, const House* newHouse)
{   
    if (hasHouse(res))
    {
        const House* oldHouse = _get_res_cur_house(res);
        _house_per_resident_map.erase(res);
        _res_per_house_map.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    _res_per_house_map.insert(pair<const House*, Resident*>(newHouse, res));
    _house_per_resident_map.insert(pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);
}

set<Resident*> Simulator_Basic_A::getResidentsInTheseHouses(
    set<const House*> houses
)
{   
    set<Resident*> residents;
    for (const House* house : houses)
    {   
        if (hasResident(house))
        {   
            Resident* rr = getCurrResident(house);
            residents.insert(rr);
        }  
    }
    return residents;
}

const House* Simulator_Basic_A::Simulator_Basic_A::selectRandom(
    unordered_set<const House*>& setOfHouses
) const
{   
    int size = setOfHouses.size();
    int r = rand() % size;
    unordered_set<const House*>::iterator it = setOfHouses.begin();
    advance(it, r);
    return *it;
}

const House* Simulator_Basic_A::_get_res_cur_house (Resident* res)
{
    const House* currHouse = _house_per_resident_map.at(res);
    return currHouse;
}

Resident* Simulator_Basic_A::getCurrResident (const House* house)
{
    Resident* currRes = _res_per_house_map.at(house);
    return currRes;
}

bool Simulator_Basic_A::hasResident (const House* house)
{
    unordered_map<const House*, Resident*>::iterator it = _res_per_house_map.find(house);
    return ( it != _res_per_house_map.end() );
}

bool Simulator_Basic_A::hasHouse (Resident* res)
{
    unordered_map<Resident*, const House*>::iterator it = _house_per_resident_map.find(res);
    return !(it == _house_per_resident_map.end());
    //return _curr_res_to_house_map.count(res) > 0;
}

void Simulator_Basic_A::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _get_res_cur_house(res);
        set<const House*> adjHouses = _city->getAdjacentHouses(house->getAddress());
        set<Resident*> adjResidents = getResidentsInTheseHouses(adjHouses);
        res->setHappiness(adjResidents, adjHouses.size());
    }
}

double Simulator_Basic_A::calculateHappinessValueFor(Resident* res, int address)
{
    set<const House*> adjHouses = _city->getAdjacentHouses(address);
    return res->calculateHappiness(getResidentsInTheseHouses(adjHouses), adjHouses.size());
}