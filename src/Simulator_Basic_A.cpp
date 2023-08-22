#include "Simulator_Basic_A.h"

using namespace std;

Simulator_Basic_A::Simulator_Basic_A (
    const City* city,
    std::unordered_set<Resident*> residents,
    double percentOfResidents,
    int numOfHousesToChooseFrom,
    std::unique_ptr<CityState> cityState
    ): Simulator_Basic(
            city,
            residents,
            percentOfResidents,
            numOfHousesToChooseFrom,
            move(cityState))
    {}

string Simulator_Basic_A::toString() const
{
    return "Simulator Basic A";
}

bool Simulator_Basic_A::doMoveResident (
        double newHouseHappiness,
        const Resident* resident,
        const CityState* cityState,
        const City* city,
        int curAddress
) const
{
    // Calculate current happiness for resident. May have changed since run started.
    unordered_set<const House*> adjacentHouses = city->getHousesAdjacent(curAddress);
    
    unordered_set<const Resident*> adjacentNeighbors;
    for (const House* adjacentHouse : adjacentHouses)
    {   
        Resident* adjacentNeighbor = cityState->getResidentPerHouse(adjacentHouse);
        if (adjacentNeighbor != nullptr)
        {
            adjacentNeighbors.insert(adjacentNeighbor);
        }
    }
    
    return newHouseHappiness >=
        resident->calculateHappiness(adjacentNeighbors, adjacentHouses.size());
}