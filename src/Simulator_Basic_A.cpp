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
        return _curr_house_to_res_map;
    }
    for (Resident* res : _residents)
    {   
        std::cout << "SBasicA 24" << std::endl;
        moveResidentIfUnhappy(res);
    }
    return _curr_house_to_res_map;
}

void Simulator_Basic_A::firstSimulation ()
{
    for (Resident* res : _residents)
    {
        House* house = selectRandom(_open_houses);
        moveResidentIntoHouse(res, house);
    }
}
void Simulator_Basic_A::moveResidentIfUnhappy (Resident* res)
{
    House* oldHouse = _curr_res_to_house_map[res];

    std::set<House*> adjHouses = _city->getAdjacentHouses(oldHouse);
    std::set<Resident*> adjResidents = getResidentsInHouses(adjHouses);
    if ( res->getHappiness(adjResidents, adjHouses.size()) <
         res->getHappinessGoal() )
    {   
        House* newHouse = selectRandom(_open_houses);
        moveResidentIntoHouse(res, newHouse);
    }

}

void Simulator_Basic_A::moveResidentIntoHouse (Resident* res, House* newHouse)
{   /*
    House* oldHouse = _curr_res_to_house_map[res];
    if ( oldHouse ) // if resident has a current house
    {
        _curr_house_to_res_map.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    std::cout << "Sim 60 new house "; std::cout << res->getID() << " " << newHouse->_address << std::endl;
    _curr_house_to_res_map.insert(std::pair<House*, Resident*>(newHouse, res));
    _curr_res_to_house_map.insert(std::pair<Resident*, House*>(res, newHouse));
    //_open_houses.erase(newHouse);
    std::cout << "Sim 64 newHouse: " << newHouse->_address << std::endl;
    std::cout << "Sim 65: " << res->getID(); std::cout << " " << _curr_res_to_house_map.count(res) << std::endl;
    std::cout << "Sim 66: " << res->getID() << std::endl;
    std::cout << "Sim 67: " << ((_curr_res_to_house_map[res])== nullptr) << std::endl;
    */

   std::map<Resident*, House*> testMap;
   testMap.insert(std::pair<Resident*, House*>(res, newHouse));
   std::cout << "Sim 72: " << testMap[res]->_address << std::endl;
}

std::set<Resident*> Simulator_Basic_A::getResidentsInHouses(
    std::set<House*> houses
)
{   std::set<Resident*> residents;
    for (House* house : houses)
    {   
        Resident* currRes = _curr_house_to_res_map[house];
        if (currRes)
            residents.insert(_curr_house_to_res_map[house]);
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


