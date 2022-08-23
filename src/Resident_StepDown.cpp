#include "Resident_StepDown.h"
#include <iostream>

Resident_StepDown::Resident_StepDown ( 
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity,
    double diversityWhereDropHappens):
    Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
    _happiness_at_zero_diversity(happinessValueAtZeroDiversity),
    _happiness_at_one_diversity(happinessValueAtOneDiversity),
    _diversity_where_drop_happens(diversityWhereDropHappens),
    _happiness_func{
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity, 
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
        ", " + std::to_string(_happiness_at_zero_diversity) +
        ", " + std::to_string(_happiness_at_one_diversity) +
        ", " + std::to_string(_diversity_where_drop_happens) +
        ")"; 
}

double Resident_StepDown::implCalculateHappiness (
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
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
    if ( (like + diff) == 0 )
    {
        return _happiness_at_zero_diversity; // happy to be alone
    }
    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

House* Resident_StepDown::findHome(
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::unordered_map<House*, Resident*> houseToResMap
) const
{
    for (auto h2N : openHousesAndTheirAdjacentHouses)
    {
        House* currHouse = h2N.first;
        std::set<House*> setOfAdjHouses = h2N.second;
        std::set<Resident*> currHouseAdjacentResidents;
        for (House* nH : setOfAdjHouses)
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

House* Resident_StepDown::findBestHome(
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::unordered_map<House*, Resident*> houseToResMap
) const
{
    return findHome(oldHouse, openHousesAndTheirAdjacentHouses, houseToResMap);
}