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
    int numOfHousesChosen,
    unique_ptr<CityState> cityState
): _city{city},
   _residents{residents},
   _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesChosen},
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

    unordered_set<const House*> openHousesWithinRange =
        _city_state->getOpenHousesWithinRange(0, _city->getWidth()-1, 0, _city->getHeight()-1);

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

    // residents will be erased from container, so make a copy.
    vector<Resident*> residentsCopy{};
    for (Resident* res : _residents)
    {
        residentsCopy.push_back(res);
    }

    // don't move a resident twice in the same run.
    unordered_set<Resident*> residentsMovedInThisRun{};

    // randomly choose a resident and find a house for resident
    for (int ii=0; ii<numOfResToMove; ++ii)
    {   
        // keep ratio of in residents in vector that have already moved vs 
        // residents that have not moved low
        /*if (ii == numOfResToMove/2)
        {
            residentsCopy.clear();
            for (Resident* res : _residents)
            {
                if (residentsMovedInThisRun.find(res) != residentsMovedInThisRun.end())
                {
                    residentsCopy.push_back(res);
                }
            }
        }*/

        // select a resident, remember a resident can not move twice in one run.
        Resident* curRes = selectRandom(residentsCopy);

        while ( residentsMovedInThisRun.find(curRes) != residentsMovedInThisRun.end() )
        {
            curRes = selectRandom(residentsCopy);
        }

        residentsMovedInThisRun.insert(curRes);

        // create a set of open houses that are within the range of the current resident's house.
        const House* currHouse = _city_state->getHousePerResident(curRes);
        double maxDist = curRes->getAllowedMovementDistance();
        pair<int, int> xRange = _city->getXRangeForAllowableDistanceToHouse(currHouse,maxDist);
        pair<int, int> yRange = _city->getYRangeForAllowableDistanceToHouse(currHouse,maxDist);

        unordered_set<const House*> openHousesWithinRange = _city_state->getOpenHousesWithinRange(
            xRange.first,
            xRange.second,
            yRange.first,
            yRange.second
        );

        openHousesWithinRange.erase(currHouse);

        vector<const House*> openHousesVector{};
        for (const House* openHouse: openHousesWithinRange)
        {
            if ( _city->getDist(openHouse->getAddress(), currHouse->getAddress()) <=
                 curRes->getAllowedMovementDistance() )
            {
                openHousesVector.push_back(openHouse);
            }
        }

        // Find a new house for current resident. Only get _max_num_of_tries_to_find_house.
        // If an open house does not found in _max_
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;
        int maxTries = min(_max_num_of_tries_to_find_house, (int)openHousesVector.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
        // 
        unordered_set<const House*> housesTried{};
        for (int ii=0; ii<maxTries; ++ii)
        {
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(openHousesVector);
            while ( housesTried.find(randHouse) != housesTried.end() )
            {
                randHouse = selectRandom(openHousesVector);
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
    cout << "SimulatorBasicB: ZZ" << endl;
}

void Simulator_Basic_B::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _city_state->getHousePerResident(res);
        if (house != nullptr) //TODO really shouldn't be nullptr
        {
            res->setHappiness(calculateHappinessValueFor(res, house->getAddress()));
        }
        
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