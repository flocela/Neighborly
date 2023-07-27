#include "Simulator_Basic_A.h"

#include <algorithm>
#include <limits>

#include "CityState_Simple.h"
#include "RandIntsMaker.h"

using namespace std;

// Used for sorting vectors of pointers
template<class T>
bool compare (T a, T b)
{
    return *a < *b;
}

Simulator_Basic_A::Simulator_Basic_A (
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

ResPerHouse Simulator_Basic_A::run ()
{   
    // If city is empty, then populate city first
    if (_city_state->getResidentsPerHouse().size() == 0)
    {
        firstRun();
    }
    else
    {   
        normalRun();
    }
    
    setHappinessValuesForAllResidents();
    
    // _city_state returns non-const Resident pointers, convert them to const Resident pointers
    // before returning results.
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();

    ResPerHouse results{};
    results.reserve(resPerHouse.size());
    for (auto pair : resPerHouse)
    {
        results.insert(pair);
    }

    return results;
}

string Simulator_Basic_A::toString()
{
    return "Simulator Basic B";
}

void Simulator_Basic_A::firstRun ()
{  
    // Make a copy of the vector to Resident pointers. A copy is needed to randomly choose
    // residents. Note, the pointers are copied, not the residents.
    vector<Resident*> sortedResidents{};
    sortedResidents.reserve(_residents.size());
    for (Resident* res : _residents)
    {
        sortedResidents.push_back(res);
    }
    std::sort(sortedResidents.begin(), sortedResidents.end(), compare<Resident*>);

    // For the first run, all houses in city are open.
    unordered_set<const House*> openHouses = _city_state->getOpenHouses();

    // Make a copy of the vector of open house pointers.
    vector<const House*> sortedOpenHouses{};
    sortedOpenHouses.reserve(openHouses.size());
    for (const House* h : openHouses)
    {
        sortedOpenHouses.push_back(h);
    }
    sort(sortedOpenHouses.begin(), sortedOpenHouses.end(), compare<const House*>);

    // For each resident, choose a random house.
    // This is done by creating a vector of random integers from the sortedResidents
    // and sortedOpenHouses vector indices.
    RandIntsMaker randomIntegers{};
    vector<int> randomIntegersForResidents = 
        randomIntegers.getRandomIntegers(sortedResidents.size(), sortedResidents.size());
    vector<int> randomIntegersForHouses = 
        randomIntegers.getRandomIntegers(sortedOpenHouses.size(), sortedOpenHouses.size());
    
    for (size_t ii=0; ii<randomIntegersForResidents.size(); ++ii)
    {   
        Resident* randRes = sortedResidents[randomIntegersForResidents[ii]];
        const House* randHouse = sortedOpenHouses[randomIntegersForHouses[ii]];

        // Move random resident into random house.
        _city_state->moveIn(randRes, randHouse);
    } 
}

void Simulator_Basic_A::normalRun ()
{   
    // Make a sorted copy of the vector of resident pointers.
    vector<Resident*> sortedResidents{};
    sortedResidents.reserve(_residents.size());
    for (Resident* res : _residents)
    {
        sortedResidents.push_back(res);
    }
    std::sort(sortedResidents.begin(), sortedResidents.end(), compare<Resident*>);

    // Randomly choose a number of residents. This is done by randomly choosing
    // indexes from the sortedResidents vector.
    int numOfRes = _percent_of_residents * sortedResidents.size() / 100;
    RandIntsMaker rI{};
    vector<int> randomIntsForResidents = rI.getRandomIntegers(sortedResidents.size(), numOfRes);

    // Find a house for each resident.
    for (size_t ii=0; ii<randomIntsForResidents.size(); ++ii)
    {   
        Resident* curRes = sortedResidents[randomIntsForResidents[ii]];
        
        // Create a set of open houses that are within the range of the current resident's house.
        const House* curHouse = _city_state->getHousePerResident(curRes);
        Coordinate curHouseCoord = _city->getCoordinate(curHouse->getAddress());
        
        vector<const House*> openHouses = _city_state->getOpenHousesWithinRange(
            curHouseCoord.getX(),
            curHouseCoord.getY(),
            curRes->getAllowedMovementDistance()
        );
        sort(openHouses.begin(), openHouses.end(), compare<const House*>);

        // Create a vector of shuffled indices from the openHouses vector.
        RandIntsMaker randomInts{};
        int maxTries = min((int)openHouses.size(), _max_num_of_tries_to_find_house);
        vector<int> randIndices = randomInts.getRandomIntegers(openHouses.size(), maxTries);

        // Find a new house for current resident.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;

        unordered_set<const House*> housesTried{};
        for (size_t ii=0; ii<randIndices.size(); ++ii)
        {
            const House* randHouse = openHouses[randIndices[ii]];

            double randHouseHappiness = 
                calculateHappinessValueFor(curRes, randHouse->getAddress());
            
            if (randHouseHappiness >= selectedHappiness)
            {   
                selectedHappiness = randHouseHappiness;
                selectedHouse = randHouse;
            }
            if (selectedHappiness == curRes->getMaximumPossibleHappiness())
            {
                break;
            }
        }
        
        // Move to house that makes them happiest if it makes them happier than current house.
        if (selectedHouse != nullptr && selectedHappiness > curRes->getHappiness())
        {   
            _city_state->moveInAndOutOfHouse(curRes, selectedHouse);
        }
    }
}

void Simulator_Basic_A::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* resHouse = _city_state->getHousePerResident(res);

        unordered_set<const House*> adjHouses = _city->getHousesAdjacent(resHouse->getAddress());

        // Create adjacentNeighbors which contains all the resident's neighbors
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

// TODO res should be const.
double Simulator_Basic_A::calculateHappinessValueFor(Resident* res, int address)
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
