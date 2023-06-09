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

template <typename T>
T selectRandom(vector<T>& vectorOfT)
{   
    int size = vectorOfT.size();
    int r = rand() % size;
    return vectorOfT[r];
}

Simulator_Basic_A::Simulator_Basic_A (
    const City* city,
    unordered_set<Resident*> residents,
    int numOfHousesToChooseFrom,
    unique_ptr<CityState> cityState
): _city{city},
   _residents{residents},
   _num_of_tries{numOfHousesToChooseFrom},
   _city_state{std::move(cityState)}
{}

unordered_map<const House*, const Resident*> Simulator_Basic_A::run ()
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
    // TODO increase runNUm???
    setHappinessValuesForAllResidents();

    // Create results from _city_state's residents perHouse.
    std::unordered_map<const House*, const Resident*> results{};
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();
    results.reserve(resPerHouse.size());
    for (auto pair : resPerHouse)
    {
        results.insert(pair);
    }
    return results;
}

void Simulator_Basic_A::firstRun ()
{   
    // Make a copy of the set of residents; A copy is needed to randomly choose residents.
    unordered_set<Resident*> copyOfResidents{};
    for (Resident* res : _residents)
    {
        copyOfResidents.insert(res);
    }

    // For the first run all houses in city are open.
    unordered_set<const House*> openHouses = _city_state->getOpenHouses();

    // For each resident, choose a random house.
    while (copyOfResidents.size() != 0)
    {   
        Resident* randRes = selectRandom(copyOfResidents);

        const House* house = selectRandom(openHouses);
        
        _city_state->moveIn(randRes, house);

        copyOfResidents.erase(randRes);
        
        openHouses.erase(house);
        
    }
}

void Simulator_Basic_A::normalRun ()
{
    // Make a copy of the set of residents; A copy is needed to randomly choose residents.
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    // for each resident, if unhappy try to move resident
    while (copySetOfResidents.size() > 0)
    {
        Resident* randRes = selectRandom(copySetOfResidents);
        double curHappiness = 
            calculateHappiness(randRes, _city_state->getHousePerResident(randRes)->getAddress());
        if (curHappiness < randRes->getHappinessGoal())
        {
            moveResident(randRes, _num_of_tries);
        }

        copySetOfResidents.erase(randRes);
    }
}

void Simulator_Basic_A::moveResident (Resident* res, int numOfTries)
{  
    const House* currHouse = _city_state->getHousePerResident(res);
    Coordinate currHouseCoord = _city->getCoordinate(currHouse->getAddress());

    vector<const House*> housesInRange = _city_state->getOpenHousesWithinRange(
        currHouseCoord.getX(),
        currHouseCoord.getY(),
        res->getAllowedMovementDistance()
    );
    
    unordered_set<const House*> housesTried{};
    while (numOfTries > 0 && housesInRange.size() != housesTried.size())
    {  
        // Choose a random house that has not been chosen before.
        const House* randHouse = selectRandom(housesInRange);
        while ( housesTried.find(randHouse) != housesTried.end() || randHouse == currHouse)
        {
            randHouse = selectRandom(housesInRange);
        }
        housesTried.insert(randHouse);
        
        // If house will make resident happy, then move in.
        if ( calculateHappiness(res, randHouse->getAddress()) > res->getHappinessGoal() )
        {   
            _city_state->moveInAndOutOfHouse(res, randHouse);
            break;
        }

        --numOfTries;
    }
}

void Simulator_Basic_A::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _city_state->getHousePerResident(res);

        // Create adjacentNeighbors which contains all the resident's neighbors
        unordered_set<const House*> adjHouses = _city->getHousesAdjacent(house->getAddress());
        unordered_set<const Resident*> adjacentNeighbors;
        for (const House* adjacentHouse : adjHouses)
        {   
            Resident* adjacentNeighbor = _city_state->getResidentPerHouse(adjacentHouse);
            if (adjacentNeighbor != nullptr)
            {
                adjacentNeighbors.insert(adjacentNeighbor);
            }
        }

        res->setHappiness(adjacentNeighbors, adjHouses.size());
        
    }
}

double Simulator_Basic_A::calculateHappiness(Resident* res, int address)
{
    // Create adjacentNeighbors which contains all the resident's neighbors
    unordered_set<const House*> adjacentHouses = _city->getHousesAdjacent(address);
    unordered_set<const Resident*> adjacentNeighbors;
    for (const House* adjacentHouse : adjacentHouses)
    {   
        Resident* adjacentNeighbor = _city_state->getResidentPerHouse(adjacentHouse);
        if (adjacentNeighbor != nullptr)
        {
            adjacentNeighbors.insert(adjacentNeighbor);
        }
    }

    return res->calculateHappiness(adjacentNeighbors, adjacentHouses.size());
}

string Simulator_Basic_A::toString()
{
    return "Simulator Basic A";
}
