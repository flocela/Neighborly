#include "Simulator_Basic_B.h"

#include <algorithm>
#include <limits>

#include "CityState_Simple.h"
#include "RandomIntegers.h"

using namespace std;

// Used for sorting vectors of pointers
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
   _residents{residents},
   _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesToChooseFrom},
   _city_state{std::move(cityState)}
{}

std::unordered_map<const House*, const Resident*> Simulator_Basic_B::run ()
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
{  
    // Make a copy of the set of residents; A copy is needed to randomly choose residents.
    vector<Resident*> copyOfResidents{};
    copyOfResidents.reserve(_residents.size());
    for (Resident* res : _residents)
    {
        copyOfResidents.push_back(res);
    }
    std::sort(copyOfResidents.begin(), copyOfResidents.end(), compare<Resident*>);

    // For the first run, all houses in city are open.
    unordered_set<const House*> openHouses = _city_state->getOpenHouses();

    // Make a copy of open houses; A copy is need to randomly choose houses.
    vector<const House*> copyOfOpenHouses{};
    copyOfOpenHouses.reserve(openHouses.size());
    for (const House* h : openHouses)
    {
        copyOfOpenHouses.push_back(h);
    }
    sort(copyOfOpenHouses.begin(), copyOfOpenHouses.end(), compare<const House*>);

    // For each resident, choose a random house.
    RandomIntegers randomIntegers{};
    vector<int> randomIntegersForResidents = 
        randomIntegers.getRandomIntegers(copyOfResidents.size(), copyOfResidents.size());
    vector<int> randomIntegersForHouses = 
        randomIntegers.getRandomIntegers(copyOfOpenHouses.size(), copyOfOpenHouses.size());
    
    for (size_t ii=0; ii<randomIntegersForResidents.size(); ++ii)
    {   
        Resident* randRes = copyOfResidents[randomIntegersForResidents[ii]];
        const House* randHouse = copyOfOpenHouses[randomIntegersForHouses[ii]];

        _city_state->moveIn(randRes, randHouse);
    } 
}

void Simulator_Basic_B::normalRun ()
{   
    // Make a copy of the set of residents; A copy is needed to randomly choose residents.
    vector<Resident*> residents{};
    residents.reserve(_residents.size());
    for (Resident* res : _residents)
    {
        residents.push_back(res);
    }
    std::sort(residents.begin(), residents.end(), compare<Resident*>);

    // Randomly choose a number of residents and find a house for resident
    int numOfRes = _percent_of_residents * residents.size() / 100;
    RandomIntegers rI{};
    vector<int> randomIntsForResidents = rI.getRandomIntegers(residents.size(), numOfRes);

    for (size_t ii=0; ii<randomIntsForResidents.size(); ++ii)
    {   
        Resident* curRes = residents[randomIntsForResidents[ii]];
        
        // Create a set of open houses that are within the range of the current resident's house.
        const House* currHouse = _city_state->getHousePerResident(curRes);
        Coordinate currHouseCoord = _city->getCoordinate(currHouse->getAddress());
        
        vector<const House*> openHouses = _city_state->getOpenHousesWithinRange(
            currHouseCoord.getX(),
            currHouseCoord.getY(),
            curRes->getAllowedMovementDistance()
        );
        sort(openHouses.begin(), openHouses.end(), compare<const House*>);

        // Create a vector of shuffled indices from the openHouses vector.
        RandomIntegers randomInts{};
        int maxTries = min((int)openHouses.size(), _max_num_of_tries_to_find_house);
        vector<int> randIndices = randomInts.getRandomIntegers(
            openHouses.size(),
            maxTries);

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
        
        // If none of the open houses in range make the resident happy, then don't move.
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
