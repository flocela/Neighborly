#include "Simulator_Basic_A.h"
#include <iostream>

using namespace std;

template <typename T>
T selectRandom(unordered_set<T>& setOfT)
{
    int size = setOfT.size();
    int r = rand() % size;
    auto it = setOfT.begin();
    advance(it,r);
    return *it;
}

Simulator_Basic_A::Simulator_Basic_A (
    const City* city,
    set<Resident*> residents
): _city{city},
   _residents{residents}
{   
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

unordered_map<const House*, Resident*> Simulator_Basic_A::run ()
{   
    if (!_first_run_done)
    {   
        firstRun();
        _first_run_done = true;
    }
    else
    {  
        normalRun();
    }
    
    setHappinessValuesForAllResidents();

    return _res_per_house;
}

string Simulator_Basic_A::toString()
{
    return "Simulator Basic A";
}

void Simulator_Basic_A::firstRun ()
{   
    // make a copy of the set or residents (copy is needed to randomly choose residents)
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
        
        _res_per_house.insert({house, randRes});
        
        _house_per_resident.insert({randRes, house});
        
        _open_houses.erase(house);

        copySetOfResidents.erase(randRes);
    }

}

void Simulator_Basic_A::normalRun ()
{
    // make a copy of the set or residents (copy needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    // for each resident, if unhappy try to move resident
    while (copySetOfResidents.size() > 0)
    {
        Resident* randRes = selectRandom(copySetOfResidents);

        if (calculateHappinessValueFor(randRes, _house_per_resident[randRes]->getAddress()) < 
            randRes->getHappinessGoal())
        {
            moveResident(randRes, _num_of_tries);
        }

        copySetOfResidents.erase(randRes);
    }
}

void Simulator_Basic_A::moveResident (Resident* res, int numOfTries)
{  
    const House* currHouse = _house_per_resident[res];
    
    unordered_set<const House*> nearHouses = _city->getHousesWithinDistance
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
        _res_per_house.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    _res_per_house.insert(pair<const House*, Resident*>(newHouse, res));
    _house_per_resident.insert(pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);
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
    set<const House*> adjHouses = _city->getHousesAdjacent(address);
    return res->calculateHappiness(getResidentsInTheseHouses(adjHouses), adjHouses.size());
}

set<const Resident*> Simulator_Basic_A::getResidentsInTheseHouses (set<const House*> houses)
{   
    set<const Resident*> residents;
    for (const House* house : houses)
    {   
        if (_res_per_house.find(house) != _res_per_house.end())
        {
            residents.insert(_res_per_house[house]);
        } 
    }
    return residents;
}
