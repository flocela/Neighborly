#include "Simulator_Basic_B.h"

#include <algorithm>
#include <limits>

#include "CityState_Simple.h"
#include "RandIntsMaker.h"

using namespace std;

// Used for sorting vectors of pointers.
template<class T>
bool compare (T a, T b)
{
    return *a < *b;
}

Simulator_Basic_B::Simulator_Basic_B (
    const City* city,
    unordered_set<Resident*> residents,
    double percentOfResidents,
    int numOfHousesToChooseFrom,
    unique_ptr<CityState> cityState
): _city{city},
   _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesToChooseFrom},
   _city_state{std::move(cityState)}
{   
    _sorted_residents.reserve(residents.size());
    for (Resident* res : residents)
    {
        _sorted_residents.push_back(res);
    }
    std::sort(_sorted_residents.begin(), _sorted_residents.end(), compare<Resident*>);
}

ResPerHouse Simulator_Basic_B::run ()
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
    
    // Convert unordered_map<const House*, Resident*> to ResPerHouse before returning.
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();

    ResPerHouse results{};
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
    // For the first run, all houses in city are open.
    unordered_set<const House*> openHouses = _city_state->getOpenHouses();

    // Create a vector of sorted houses.
    vector<const House*> sortedOpenHouses{};
    sortedOpenHouses.reserve(openHouses.size());
    for (const House* h : openHouses)
    {
        sortedOpenHouses.push_back(h);
    }
    sort(sortedOpenHouses.begin(), sortedOpenHouses.end(), compare<const House*>);

    // Create a vector of random indices from the _sorted_residents vector.
    RandIntsMaker randIntsMaker{};
    vector<int> shuffledResidentsVIndices =
        randIntsMaker.getRandomIntegers(_sorted_residents.size(), _sorted_residents.size());
    
    // Create a vector of random indices from the sortedOpenHouses vector.
    vector<int> shuffledHouseVIndices = 
        randIntsMaker.getRandomIntegers(sortedOpenHouses.size(), sortedOpenHouses.size());
    
    // Go through shuffledResidentsVIndices and find a house using the
    // shuffledHouseVIndices. Resident order is random. House order is random.
    for (size_t ii=0; ii<shuffledResidentsVIndices.size(); ++ii)
    {   
        Resident* randRes = _sorted_residents[shuffledResidentsVIndices[ii]];
        const House* randHouse = sortedOpenHouses[shuffledHouseVIndices[ii]];

        // Move random resident into random house.
        _city_state->moveIn(randRes, randHouse);
    } 
}

void Simulator_Basic_B::normalRun ()
{   
    // Create a vector of shuffled resident indices taking only a _percent_of_residents.
    int numOfRes = _percent_of_residents * _sorted_residents.size() / 100;

    RandIntsMaker randIntsMaker{};
    vector<int> shuffledResidentsVIndices =
        randIntsMaker.getRandomIntegers(_sorted_residents.size(), numOfRes);

    // Go through shuffledResidentsVIndices and find a house for each resident.
    for (size_t ii=0; ii<shuffledResidentsVIndices.size(); ++ii)
    {   
        Resident* curRes = _sorted_residents[shuffledResidentsVIndices[ii]];
        const House* curHouse = _city_state->getHousePerResident(curRes);
        Coordinate curHouseCoord = _city->getCoordinate(curHouse->getAddress());

        // Create a sorted vector of open houses that are within the range of the
        // current resident's house.
        vector<const House*> sortedOpenHouses = _city_state->getOpenHousesWithinRange(
            curHouseCoord.getX(),
            curHouseCoord.getY(),
            curRes->getAllowedMovementDistance()
        );
        sort(sortedOpenHouses.begin(), sortedOpenHouses.end(), compare<const House*>);

        // Create a vector of shuffled indices from the sortedOpenHouses vector.
        RandIntsMaker randIntsMaker{};
        int maxTries = min((int)sortedOpenHouses.size(), _max_num_of_tries_to_find_house);
        vector<int> shuffledHouseVIndices = randIntsMaker.getRandomIntegers(
            sortedOpenHouses.size(),
            maxTries);

        // Find a new house for current resident.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;

        // Try houses in order of shuffledHouseVIndices until one maxes out the resident's
        // happiness or all houses have been tried. Keep track of which house
        // would make the resident happiest (or at least tie for the happiest).
        for (size_t ii=0; ii<shuffledHouseVIndices.size(); ++ii)
        {
            const House* randHouse = sortedOpenHouses[shuffledHouseVIndices[ii]];

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
        
        // If none of the open houses in range make the resident happy, then don't move.
        if (selectedHouse != nullptr && selectedHappiness >= curRes->getHappinessGoal())
        {   
            _city_state->moveInAndOutOfHouse(curRes, selectedHouse);
        }
    }
}

void Simulator_Basic_B::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _sorted_residents)
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

double Simulator_Basic_B::calculateHappinessValueFor(Resident* res, int address) const
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
