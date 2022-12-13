#include "Simulator_Basic_A.h"
#include <iostream>

Simulator_Basic_A::Simulator_Basic_A (City* city, std::set<Resident*> residents):
    _city{city}, _residents{residents}
{   
    for (const House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

std::unordered_map<const House*, Resident*> Simulator_Basic_A::simulate ()
{   
    if (!_first_simulation_done)
    {   
        firstSimulation();
        _first_simulation_done = true;
    }
    else
    {   int count  = 0;
        for (Resident* res : _residents)
        {   
            if ( calculateHappinessValueFor(res, _curr_res_to_house_map[res]->getAddress()) <
                res->getHappinessGoal() )
            {
                moveResident(res);
                ++count;
            }
        }
        std::cout << "SimBA moved/total: " << count << "/" << _residents.size() << std::endl;
    }
    
    setHappinessValuesForAllResidents();

    return _curr_house_to_res_map;
}

void Simulator_Basic_A::firstSimulation ()
{   
    for (Resident* res : _residents)
    {   
        const House* house = selectRandom(_open_houses);
        
        _curr_house_to_res_map.insert(std::pair<const House*, Resident*>(house, res));
        
        _curr_res_to_house_map.insert(std::pair<Resident*, const House*>(res, house));
        
        _open_houses.erase(house);
        
    }

}

void Simulator_Basic_A::moveResident (Resident* res)
{  
    const House* currHouse = _curr_res_to_house_map[res];
    std::unordered_set<const House*> nearHouses;  
    _city->findHousesWithinDistance(
        currHouse,
        res->getAllowedMovementDistance(),
        nearHouses
    );
    if (nearHouses.size() == 0)
        return;
    else
    {  
        // remove houses in nearHouses set that are not open.
        std::unordered_set<const House*>::iterator iter = nearHouses.begin();
        while (iter != nearHouses.end())
        {
            if (_open_houses.find(*iter) == _open_houses.end())
            {
                std::unordered_set<const House*>::iterator copy = iter;
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
        const House* oldHouse = getCurrHouse(res);
        _curr_res_to_house_map.erase(res);
        _curr_house_to_res_map.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    _curr_house_to_res_map.insert(std::pair<const House*, Resident*>(newHouse, res));
    _curr_res_to_house_map.insert(std::pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);
}

std::set<Resident*> Simulator_Basic_A::getResidentsInTheseHouses(
    std::set<const House*> houses
)
{   
    std::set<Resident*> residents;
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
    std::unordered_set<const House*>& setOfHouses
) const
{   
    int size = setOfHouses.size();
    int r = rand() % size;
    std::unordered_set<const House*>::iterator it = setOfHouses.begin();
    std::advance(it, r);
    return *it;
}

const House* Simulator_Basic_A::getCurrHouse (Resident* res)
{
    const House* currHouse = _curr_res_to_house_map.at(res);
    return currHouse;
}

Resident* Simulator_Basic_A::getCurrResident (const House* house)
{
    Resident* currRes = _curr_house_to_res_map.at(house);
    return currRes;
}

bool Simulator_Basic_A::hasResident (const House* house)
{
    std::unordered_map<const House*, Resident*>::iterator it = _curr_house_to_res_map.find(house);
    return ( it != _curr_house_to_res_map.end() );
}

bool Simulator_Basic_A::hasHouse (Resident* res)
{
    std::unordered_map<Resident*, const House*>::iterator it = _curr_res_to_house_map.find(res);
    return !(it == _curr_res_to_house_map.end());
    //return _curr_res_to_house_map.count(res) > 0;
}

void Simulator_Basic_A::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = getCurrHouse(res);
        std::set<const House*> adjHouses = _city->getAdjacentHouses(house->getAddress());
        std::set<Resident*> adjResidents = getResidentsInTheseHouses(adjHouses);
        res->setHappiness(adjResidents, adjHouses.size());
    }
}

double Simulator_Basic_A::calculateHappinessValueFor(Resident* res, int address)
{
    std::set<const House*> adjHouses = _city->getAdjacentHouses(address);
    return res->calculateHappiness(getResidentsInTheseHouses(adjHouses), adjHouses.size());
}