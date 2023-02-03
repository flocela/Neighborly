#include "Simulator_Basic_A.h"
#include <iostream>

using namespace std;

Simulator_Basic_A::Simulator_Basic_A (
    City* city, // TODO should be const
    set<Resident*> residents
): _city{city},
   _residents{residents}
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
        normalSimulation();
    }
    
    setHappinessValuesForAllResidents();

    return _res_per_house_map;
}

void Simulator_Basic_A::firstSimulation ()
{   
    // make a copy of the set or residents (needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    // for each resident, choose a random house.
    while (copySetOfResidents.size() != 0)
    {
        Resident* randRes = selectRandom(copySetOfResidents);

        const House* house = selectRandom(_open_houses);
        
        _res_per_house_map.insert(pair<const House*, Resident*>(house, randRes));
        
        _house_per_resident.insert(pair<Resident*, const House*>(randRes, house));
        
        _open_houses.erase(house);

        copySetOfResidents.erase(randRes);
    }

}

void Simulator_Basic_A::normalSimulation ()
{
    // make a copy of the set or residents (needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    // for each resident, if unhappy try to move resident
    while (copySetOfResidents.size() != 0)
    {
        Resident* randRes = selectRandom(copySetOfResidents);

        if (calculateHappinessValueFor(randRes, _house_per_resident[randRes]->getAddress()) < 
            randRes->getHappinessGoal())
        {
            moveResident(randRes, _count);
        }

        copySetOfResidents.erase(randRes);
    }
}
void Simulator_Basic_A::moveResident (Resident* res, int numOfTries)
{  
    const House* currHouse = _house_per_resident[res];
    
    unordered_set<const House*> nearHouses = _city->findHousesWithinDistance
    (   
        currHouse,
        res->getAllowedMovementDistance()
    );
    
    if (nearHouses.size() == 0)
    {
        return;
    }
    // remove houses in nearHouses set that are not open. 
    // resident can't move into houses that are occupied even if they are near.
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
    
    while (numOfTries > 0)
    {  
        if (nearHouses.size() == 0)
        {
            return;
        }

        const House* randomHouse = selectRandom(nearHouses);
        
        if ( calculateHappinessValueFor(res, randomHouse->getAddress()) > res->getHappinessGoal() )
        {   
            moveResidentIntoHouse(res, randomHouse);
            break;
        }

        --numOfTries;

        nearHouses.erase(randomHouse);
    }
}

void Simulator_Basic_A::moveResidentIntoHouse (Resident* res, const House* newHouse)
{   
    if (_house_per_resident.find(res) != _house_per_resident.end())
    {
        const House* oldHouse = _house_per_resident[res];
        _house_per_resident.erase(res);
        _res_per_house_map.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    _res_per_house_map.insert(pair<const House*, Resident*>(newHouse, res));
    _house_per_resident.insert(pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);
}


// TODO make a template, for selecting houses and residents.
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

Resident* Simulator_Basic_A::Simulator_Basic_A::selectRandom(
    unordered_set<Resident*>& setOfResidents
) const
{   
    int size = setOfResidents.size();
    int r = rand() % size;
    unordered_set<Resident*>::iterator it = setOfResidents.begin();
    advance(it, r);
    return *it;
}

void Simulator_Basic_A::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _house_per_resident[res];
        res->setHappiness(calculateHappinessValueFor(res, house->getAddress()));
    }
}

double Simulator_Basic_A::calculateHappinessValueFor(Resident* res, int address)
{
    set<const House*> adjHouses = _city->getAdjacentHouses(address);
    return res->calculateHappiness(getResidentsInTheseHouses(adjHouses), adjHouses.size());
}

set<Resident*> Simulator_Basic_A::getResidentsInTheseHouses (set<const House*> houses)
{   
    set<Resident*> residents;
    for (const House* house : houses)
    {   
        if (_res_per_house_map.find(house) != _res_per_house_map.end())
        {
            residents.insert(_res_per_house_map[house]);
        } 
    }
    return residents;
}