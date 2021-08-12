#include "Simulator_Basic_A.h"
#include <iostream>

Simulator_Basic_A::Simulator_Basic_A (City* city, std::set<Resident*> residents):
    _city{city}, _residents{residents}
{
    for (House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

std::map<House*, Resident*> Simulator_Basic_A::simulate ()
{   
    if (!_first_simulation_done)
    {
        firstSimulation();
        _first_simulation_done = true;
    }
    else
    {
        for (Resident* res : _residents)
        {   
            moveResidentIfUnhappy(res);
        }
    }
    
    return _curr_house_to_res_map;
}

void Simulator_Basic_A::firstSimulation ()
{
    for (Resident* res : _residents)
    {
        House* house = selectRandom(_open_houses);
        moveResidentIntoHouse(res, house);
        updateResident(res);
    }
}
void Simulator_Basic_A::moveResidentIfUnhappy (Resident* res)
{   
    if ( res->getHappiness() < res->getHappinessGoal() )
    {   
        House* newHouse = selectRandom(_open_houses);
        moveResidentIntoHouse(res, newHouse);
        updateResident(res);
    }
}

void Simulator_Basic_A::moveResidentIntoHouse (Resident* res, House* newHouse)
{   
    if (_curr_res_to_house_map.count(res) > 0)
    {
        House* oldHouse = _curr_res_to_house_map[res];
        _curr_res_to_house_map.erase(res);
        _curr_house_to_res_map.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }

    _curr_house_to_res_map.insert(std::pair<House*, Resident*>(newHouse, res));
    _curr_res_to_house_map.insert(std::pair<Resident*, House*>(res, newHouse));
    _open_houses.erase(newHouse);
  
}

void Simulator_Basic_A::updateResident (Resident* res)
{   
    House* house = _curr_res_to_house_map[res];
    std::set<House*> adjHouses = _city->getAdjacentHouses(house);
    std::set<Resident*> adjResidents = getResidentsInHouses(adjHouses);
    res->calculateHappiness(adjResidents, adjHouses.size());
}

std::set<Resident*> Simulator_Basic_A::getResidentsInHouses(
    std::set<House*> houses
)
{   
    std::set<Resident*> residents;
    for (House* house : houses)
    {   
        if (_curr_house_to_res_map.count(house) > 0)
        {
            Resident* currRes = _curr_house_to_res_map[house];
            residents.insert(currRes);
        }  
    }
    return residents;
}

House* Simulator_Basic_A::Simulator_Basic_A::selectRandom(
    std::set<House*>& setOfHouses
) const
{   
    int size = setOfHouses.size();
    int r = rand() % size;
    std::set<House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    return *it;
}


