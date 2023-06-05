#include "Simulator_Basic_B.h"

#include <algorithm>
#include <limits>

#include "CityState_Simple.h"

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

Simulator_Basic_B::Simulator_Basic_B (
    const City* city,
    unordered_set<Resident*> residents,
    double percentOfResidents,
    int numOfHousesToChooseFrom,
    unique_ptr<CityState> cityState
): _city{city},
   _residents{residents},
   _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesToChooseFrom},
   _city_state{std::move(cityState)}
{}

std::unordered_map<const House*, const Resident*> Simulator_Basic_B::run ()
{   
    std::unordered_map<const House*, const Resident*> results{};

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
    ++runNum;
    
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();

    results.reserve(resPerHouse.size());
    for (auto pair : resPerHouse)
    {
        results.insert(pair);
    }

    return results;
}

string Simulator_Basic_B::toString()
{
    return "Simulator Basic B";
}

void Simulator_Basic_B::firstRun ()
{  
    // will be deleteing residents from set, so make a copy.
    unordered_set<Resident*> residentsCopy{};
    for (Resident* res : _residents)
    {
        residentsCopy.insert(res);
    }

    unordered_set<const House*> openHousesWithinRange = _city_state->getOpenHouses();

    // for each resident, choose a random house.
    while (residentsCopy.size() > 0 && openHousesWithinRange.size() > 0)
    {   
        Resident* randomResident = selectRandom(residentsCopy);
        const House* randomHouse = selectRandom(openHousesWithinRange);

        _city_state->moveIn(randomResident, randomHouse);

        residentsCopy.erase(randomResident);
        openHousesWithinRange.erase(randomHouse);
    }
}

void Simulator_Basic_B::normalRun ()
{   
    int numOfResToMove = _residents.size() * _percent_of_residents /100;

    // make a copy of the residents as a vector
    resetMovingResidentsVector();

    // don't move a resident twice in the same run.
    unordered_set<Resident*> residentsMovedFromVector{};

    // randomly choose a resident and find a house for resident
    for (int ii=0; ii<numOfResToMove; ++ii)
    {   
        if (_residents_chosen_from_cur_vector.size() == _moving_residents_vector.size()/3)
        {
            updateMovingResidentsVector();
        }
        
        // select a resident
        Resident* curRes = selectRandom(_moving_residents_vector);

        // remember a resident can not be chosen twice in one run
        while ( _residents_chosen_from_cur_vector.find(curRes) !=
                _residents_chosen_from_cur_vector.end() )
        {
            curRes = selectRandom(_moving_residents_vector);
        }

        _residents_chosen_from_cur_vector.insert(curRes);
        
        // create a set of open houses that are within the range of the current resident's house.
        const House* currHouse = _city_state->getHousePerResident(curRes);
        Coordinate currHouseCoord = _city->getCoordinate(currHouse->getAddress());
        
        vector<const House*> openHousesWithinRange = _city_state->getOpenHousesWithinRange(
            currHouseCoord.getX(),
            currHouseCoord.getY(),
            curRes->getAllowedMovementDistance()
        );
        
        // Find a new house for current resident. Only get _max_num_of_tries_to_find_house.
        // If an open house does not found in _max_tries, then resident does not move.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;

        // openHousesWithinRange contains the original house, so subtract size by one
        int maxTries = min(_max_num_of_tries_to_find_house, (int)openHousesWithinRange.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
        // 
        unordered_set<const House*> housesTried{};
        for (int ii=0; ii<maxTries; ++ii)
        {
            
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(openHousesWithinRange);
            while ( housesTried.find(randHouse) != housesTried.end() || randHouse == currHouse)
            {
                randHouse = selectRandom(openHousesWithinRange);
            }
            housesTried.insert(randHouse);
            
            // TODO check for nullptr, check for vector being size zero
            // TODO what happens if openHousesWithinRange is empty?

            double happinessFromRandomHouse = calculateHappinessValueFor(curRes, randHouse->getAddress());
            
            if (happinessFromRandomHouse >= selectedHappiness)
            {   
                selectedHappiness = happinessFromRandomHouse;
                selectedHouse = randHouse;
            }
            if (selectedHappiness == curRes->getMaximumPossibleHappiness())
            {
                break;
            }
        }
        
        if (selectedHouse != nullptr)
        {   
            _city_state->moveInAndOutOfHouse(curRes, selectedHouse);
            
        }
    }
}

void Simulator_Basic_B::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* resHouse = _city_state->getHousePerResident(res);

        unordered_set<const House*> adjHouses = _city->getHousesAdjacent(resHouse->getAddress());

        // populate adjacentNeighbors which contains all the resident's neighbors
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

// todo res should be const.
double Simulator_Basic_B::calculateHappinessValueFor(Resident* res, int address)
{
    unordered_set<const Resident*> adjacentNeighbors;

    unordered_set<const House*> adjacentHouses = _city->getHousesAdjacent(address);
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

void Simulator_Basic_B::resetMovingResidentsVector ()
{
    _moving_residents_vector = vector<Resident*>(_residents.size());

    int ii = 0;
    for (Resident* resident : _residents)
    {
        _moving_residents_vector[ii] = resident;
        ++ii;
    }

    _residents_chosen_from_cur_vector = {};
}

void Simulator_Basic_B::updateMovingResidentsVector ()
{
    std::vector<Resident*> tempVector{};
    tempVector.reserve(_moving_residents_vector.size() - _residents_chosen_from_cur_vector.size());
    for (Resident* resident : _moving_residents_vector)
    {
        if (_residents_chosen_from_cur_vector.find(resident) ==
            _residents_chosen_from_cur_vector.end())
        {
            tempVector.push_back(resident);
        }
        _moving_residents_vector = move(tempVector);
    }

    _residents_chosen_from_cur_vector = {};
}