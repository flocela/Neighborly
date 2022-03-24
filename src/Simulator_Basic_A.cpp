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
        // Make a set of currently unhappy residents. They get the opportunity 
        // to move in this round of the simulation.
        std::set<Resident*> currUnhappyResidents;
        for (Resident* res : _residents)
        {
            if ( res->getHappiness() < res->getHappinessGoal() )
            {
                currUnhappyResidents.insert(res);
            }
        } 
    }

    for (Resident* res : _residents)
    {   
        moveResidentIfUnhappy(res); // can only make decisions based on current neighbors.
    }
   
    return _curr_house_to_res_map;
}

void Simulator_Basic_A::firstSimulation ()
{   
    for (Resident* res : _residents)
    {   
        House* house = selectRandom(_open_houses);
        _curr_house_to_res_map.insert(std::pair<House*, Resident*>(house, res));
        _curr_res_to_house_map.insert(std::pair<Resident*, House*>(res, house));
        _open_houses.erase(house);
    }

}

void Simulator_Basic_A::moveResidentIfUnhappy (Resident* res)
{   
    House* house = getCurrHouse(res);
    std::set<House*> adjHouses = _city->getAdjacentHouses(house);
    std::set<Resident*> adjResidents = getResidentsInTheseHouses(adjHouses);
    double happiness = res->calculateHappiness(adjResidents, adjHouses.size());
    if ( happiness < res->getHappinessGoal() )
    {   
        std::set<House*> readyHouses = _city->getNumberOfUnoccupiedNearHouses(
            _curr_res_to_house_map.at(res),
            res->getAllowedMovementDistance(),
            _open_houses,
            1
        );
        if (readyHouses.size() == 0)
            return;
        else
        {  
            // Move into the first house that's ready. 
            std::set<House*>::iterator it = readyHouses.begin();
            moveResidentIntoHouse(res, *it);
        }
    }
}

void Simulator_Basic_A::moveResidentIntoHouse (Resident* res, House* newHouse)
{   
    if (hasHouse(res))
    {
        House* oldHouse = getCurrHouse(res);
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
    House* house = _curr_res_to_house_map.at(res);
    std::set<House*> adjHouses = _city->getAdjacentHouses(house);
    std::set<Resident*> adjResidents = getResidentsInTheseHouses(adjHouses);
    res->calculateHappiness(adjResidents, adjHouses.size());
}

std::set<Resident*> Simulator_Basic_A::getResidentsInTheseHouses(
    std::set<House*> houses
)
{   
    std::set<Resident*> residents;
    for (House* house : houses)
    {   
        if (hasResident(house))
        {   
            Resident* rr = getCurrResident(house);
            residents.insert(rr);
        }  
    }
    return residents;
}

House* Simulator_Basic_A::selectRandomWithinMovingDist (
    std::set<House*> setOfHouses,
    House* origHouse,
    double allowedMovement
)
{
    while (setOfHouses.size() > 0)
    {
        House* randomHouse = selectRandom(setOfHouses);
        if (_city->dist(origHouse->getAddress(), randomHouse->getAddress()) <= allowedMovement)
            return randomHouse;
        else
            setOfHouses.erase(randomHouse);
    }
    return nullptr;
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

House* Simulator_Basic_A::getCurrHouse (Resident* res)
{
    House* currHouse = _curr_res_to_house_map.at(res);
    if (currHouse ==  nullptr)
    {
        std::cout << "getCurrHouse is returning nullpointer house" << std::endl;
    }
    return currHouse;
}

Resident* Simulator_Basic_A::getCurrResident (House* house)
{
    Resident* currRes = _curr_house_to_res_map.at(house);
    if (currRes == nullptr)
    {
        std::cout << "getCurrResident is returning a nullpointer" << std::endl;
    }
    return currRes;
}

bool Simulator_Basic_A::hasResident (House* house)
{
    std::map<House*, Resident*>::iterator it = _curr_house_to_res_map.find(house);
    return ( it != _curr_house_to_res_map.end() );
}

bool Simulator_Basic_A::hasHouse (Resident* res)
{
    std::map<Resident*, House*>::iterator it = _curr_res_to_house_map.find(res);
    return !(it == _curr_res_to_house_map.end());
    //return _curr_res_to_house_map.count(res) > 0;
}

void Simulator_Basic_A::updateNeighbors (House* house)
{
    std::set<House*> adjToHouse = _city->getAdjacentHouses(house);
    for (House* adjHouse: adjToHouse)
    {
        if (hasResident(adjHouse))
        {
            Resident* currRes = getCurrResident(adjHouse);
            updateResident(currRes);
        }
    }
}