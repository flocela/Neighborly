#include "Resident_StepDown.h"
#include <iostream>

Resident_StepDown::Resident_StepDown ( 
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessWithZeroNeighbors,
    double highHappinessValue,
    double lowHappinessValue,
    double diversityWhereDropHappens):
    Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
    _happiness_with_zero_neighbors(happinessWithZeroNeighbors),
    _high_happiness_value(highHappinessValue),
    _low_hapiness_value(lowHappinessValue),
    _diversity_drop(diversityWhereDropHappens),
    _happiness_func{
        happinessWithZeroNeighbors,
        highHappinessValue,
        lowHappinessValue, 
        diversityWhereDropHappens
    }
{}

std::string Resident_StepDown::toStrBasic() const
{
    return "Res_StepDown(id, clr, mov, goal, hap0, hap1, drop): (" + 
        std::to_string(getID()) +
        ", " + std::to_string(getGroupNumber()) +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_with_zero_neighbors) +
        ", " + std::to_string(_high_happiness_value) +
        ", " + std::to_string(_low_hapiness_value) +
        ", " + std::to_string(_diversity_drop) +
        ")"; 
}

double Resident_StepDown::implCalculateHappiness (
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
    if (neighbors.empty())
        return _happiness_with_zero_neighbors;
    int like  = 0;
    int diff  = 0;
    for (Resident* res : neighbors)
    {
        if (res->getGroupNumber() == getGroupNumber())
        {
            like++;
        }
        else
            diff++;
        
    }
    return _happiness_func.calcHappiness(numOfAdjacentHouses, like, diff);
}

const House* Resident_StepDown::findHome(
    const House* oldHouse,
    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
    std::unordered_map<const House*, Resident*> houseToResMap
) const
{
    for (auto h2N : openHousesAndTheirAdjacentHouses)
    {
        const House* currHouse = h2N.first;
        std::set<const House*> setOfAdjHouses = h2N.second;
        std::set<Resident*> currHouseAdjacentResidents;
        for (const House* nH : setOfAdjHouses)
        {
            if (houseToResMap.count(nH) > 0)
                currHouseAdjacentResidents.insert(houseToResMap.at(nH));
        }
        int numOfNeighboringHouses = openHousesAndTheirAdjacentHouses.at(currHouse).size();
        double happiness = implCalculateHappiness(
            currHouseAdjacentResidents,
            numOfNeighboringHouses
        );
        if (happiness >= getHappinessGoal())
            return currHouse;
    }

    return oldHouse;
}

const House* Resident_StepDown::findBestHome(
    const House* oldHouse,
    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
    std::unordered_map<const House*, Resident*> houseToResMap
) const
{
    return findHome(oldHouse, openHousesAndTheirAdjacentHouses, houseToResMap);
}