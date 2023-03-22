#include "Simulator_Basic_B.h"

#include <limits>
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

Simulator_Basic_B::Simulator_Basic_B (
    const City* city,
    set<Resident*> residents,
    double percentOfResidents,
    int numOfHousesChosen
): _city{city},
   _residents{residents},
   _percent_of_residents{percentOfResidents},
   _num_of_houses_chosen{numOfHousesChosen}
{
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

std::unordered_map<const House*, Resident*> Simulator_Basic_B::run ()
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

string Simulator_Basic_B::toString()
{
    return "Simulator Basic B";
}

void Simulator_Basic_B::firstRun ()
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

void Simulator_Basic_B::normalRun ()
{
    // make a copy of the set or residents (copy needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    int subsetToMove = _residents.size() * _percent_of_residents /100;
    
    for (int ii=0; ii<subsetToMove; ++ii)
    {   
        Resident* curRes = selectRandom(copySetOfResidents);
        const House* currHouse = _house_per_resident[curRes];

        unordered_set<const House*> nearHouses = _city->getHousesWithinDistance
        (   
            currHouse,
            curRes->getAllowedMovementDistance()
        );

        // erase houses that are occupied from nearHouses. Can't move into an occupied house.
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

        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;
        for (int ii=0; ii<_num_of_houses_chosen; ++ii)
        {
            if (nearHouses.empty())
            {
                break;
            }

            const House* randHouse = selectRandom(nearHouses);
            double randHouseHappiness = calculateHappinessValueFor(curRes, randHouse->getAddress());
            if (randHouseHappiness >= selectedHappiness)
            {
                selectedHappiness = randHouseHappiness;
                selectedHouse = randHouse;
            }
            nearHouses.erase(randHouse);
        }

        if (selectedHouse != nullptr)
        {
            moveResidentIntoHouse(curRes, selectedHouse);
        }

    }
}

void Simulator_Basic_B::moveResidentIntoHouse (Resident* res, const House* newHouse)
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

void Simulator_Basic_B::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _house_per_resident[res];
        res->setHappiness(calculateHappinessValueFor(res, house->getAddress()));
    }
}

double Simulator_Basic_B::calculateHappinessValueFor(Resident* res, int address)
{
    set<const House*> adjHouses = _city->getHousesAdjacent(address);
    return res->calculateHappiness(getResidentsInTheseHouses(adjHouses), adjHouses.size());
}

set<const Resident*> Simulator_Basic_B::getResidentsInTheseHouses (set<const House*> houses)
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