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
{
    cout <<"SimlulatorB constructor" << endl;
}

std::unordered_map<const House*, const Resident*> Simulator_Basic_B::run ()
{   cout << "first run done: " << _first_run_done << endl;
    if (!_first_run_done)
    {   
        firstRun();
        _first_run_done = true;
    }
    else
    {   
        cout <<"start Normal run" << endl;
        normalRun();
    }
    
    setHappinessValuesForAllResidents();
    ++runNum;
    
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();

    std::unordered_map<const House*, const Resident*> results{};
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
{   cout <<"SimulatorB MM" << endl;
    // make a copy of the set or residents (copy is needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }
    cout << "copySetOfResdients size: " << copySetOfResidents.size() << endl;
    unordered_set<const House*> copyOpenHouses =
        _city_state->getOpenHousesWithinRange(0, _city->getWidth()-1, 0, _city->getHeight()-1);

    for (const House* h : copyOpenHouses)
    {
        copyOpenHouses.insert(h);
    }

    // for each resident, choose a random house.
    cout <<"SimulatorB NN" << endl;
    while (copySetOfResidents.size() > 0 && copyOpenHouses.size() > 0)
    {   
        Resident* randRes = selectRandom(copySetOfResidents);
        const House* randHouse = selectRandom(copyOpenHouses);
        _city_state->moveIn(randRes, randHouse);

        copySetOfResidents.erase(randRes);
        copyOpenHouses.erase(randHouse);
    }
    cout <<"SimulatorB PP" << endl;
}

void Simulator_Basic_B::normalRun ()
{   cout << "SimulatorBasicB: AA" << endl;
    unordered_set<int> chosenResidents{};
    // make a copy of the set or residents (copy needed to randomly choose residents)
    vector<Resident*> vectorOfResidents{};
    for (Resident* res : _residents)
    {
        vectorOfResidents.push_back(res);
    }

    int numOfResToMove = _residents.size() * _percent_of_residents /100;

    // Find a house for each randomly chosen resident
    for (int ii=0; ii<numOfResToMove; ++ii)
    {   
        Resident* curRes = selectRandom(vectorOfResidents); // make new setOfResidents if finding is 1/4
        //TODO makes curRes isn't being deleted.
        // resident can't be chosen twice in one run.
        while ( chosenResidents.find(curRes->getID()) != chosenResidents.end() )
        {
            curRes = selectRandom(vectorOfResidents);
        }
        chosenResidents.insert(curRes->getID());

        const House* currHouse = _city_state->getHousePerResident(curRes);

        vector<const House*> vectorOpenHousesReduced{};
        pair<int, int> xRange = _city->getXRangeForAllowableDistanceToHouse(
            currHouse,
            curRes->getAllowedMovementDistance());
        pair<int, int> yRange = _city->getYRangeForAllowableDistanceToHouse(
            currHouse,
            curRes->getAllowedMovementDistance());
        unordered_set<const House*> openHousesWithinRange = _city_state->getOpenHousesWithinRange(
            xRange.first,
            xRange.second,
            yRange.first,
            yRange.second
        );
        openHousesWithinRange.erase(currHouse);

        // try to find a new house for current resident. Only get _max_num_of_tries_to_find_house.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;
        int maxTries = min(_max_num_of_tries_to_find_house, (int)vectorOpenHousesReduced.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
       
        for (int ii=0; ii<maxTries; ++ii)
        {
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(openHousesWithinRange);
            openHousesWithinRange.erase(randHouse);
            // TODO check for nullptr, check for vector being size zero
            while ( _city->getDist(randHouse->getAddress(), currHouse->getAddress()) >
                        curRes->getAllowedMovementDistance() )
            {
                randHouse = selectRandom(vectorOpenHousesReduced);
                openHousesWithinRange.erase(randHouse);
            }

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