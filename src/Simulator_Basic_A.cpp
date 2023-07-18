#include "Simulator_Basic_A.h"
#include <iostream>
#include <algorithm>
#include "RandomIntegers.h"
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
    int numOfHousesToChooseFrom,
    unique_ptr<CityState> cityState
): _city{city},
   _residents{residents},
   _num_of_tries{numOfHousesToChooseFrom},
   _city_state{std::move(cityState)}
{}

ResPerHouse Simulator_Basic_A::run ()
{   
    // If city is empty, populate city.
    if (_city_state->getResidentsPerHouse().size() == 0)
    {   
        firstRun();
    }
    else
    {  
        normalRun();
    }
    
    // Update residents' happiness values.
    setHappinessValuesForAllResidents();

    // _city_state returns non-const Resident pointers.
    // Convert them to const Resident pointers before returning results.
    std::unordered_map<const House*, Resident*> resPerHouse = _city_state->getResidentsPerHouse();

    ResPerHouse results{};
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

void Simulator_Basic_A::normalRun ()
{   
    // Make a copy of the set of residents; A copy is needed to randomly choose residents.
    vector<Resident*> copyOfResidents{};
    copyOfResidents.reserve(_residents.size());
    for (Resident* res : _residents)
    {
        copyOfResidents.push_back(res);
    }
    std::sort(copyOfResidents.begin(), copyOfResidents.end(), compare<Resident*>);
              
    // for each resident, if unhappy try to move resident
    RandomIntegers rI{};
    vector<int> randomIntegersForResidents = 
        rI.getRandomIntegers(copyOfResidents.size(), copyOfResidents.size());
    for (size_t ii=0; ii<randomIntegersForResidents.size(); ++ii)
    {
        Resident* randRes = copyOfResidents[randomIntegersForResidents[ii]];
        double curHappiness = 
            calculateHappiness(randRes, _city_state->getHousePerResident(randRes)->getAddress());
        if (curHappiness < randRes->getHappinessGoal())
        {   
            moveResident(randRes, _num_of_tries);
        }
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
    sort(housesInRange.begin(), housesInRange.end(), compare<const House*>);

    RandomIntegers randomIntegers{};
    int quantity = min((int)housesInRange.size(), numOfTries);
    vector<int> randIndices = randomIntegers.getRandomIntegers(housesInRange.size(), quantity);
    for (size_t ii=0; ii<randIndices.size(); ++ii)
    {
        int randIndex = randIndices[ii];
        const House* randOpenHouse = housesInRange[randIndex];
        // if house will make resident happy, then move in.
        if ( calculateHappiness(res, randOpenHouse->getAddress()) > res->getHappinessGoal() )
        {   
            _city_state->moveInAndOutOfHouse(res, randOpenHouse);
            break;
        }
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
