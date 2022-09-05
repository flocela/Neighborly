#include "Resident_StepUp.h"
#include <iostream>

Resident_StepUp::Resident_StepUp ( 
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity,
    double diversityWhereRiseHappens):
    Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
    _happiness_at_zero_diversity{happinessValueAtZeroDiversity},
    _happiness_at_one_diversity{happinessValueAtOneDiversity},
    _diversity_where_rise_happens{diversityWhereRiseHappens},
    _happiness_func{
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity, 
        diversityWhereRiseHappens
    }
{
}

std::string Resident_StepUp::toStrBasic() const
{
    return "Res_StepUp(id, clr, mov, goal, hap0, hap1, rise): (" + 
        std::to_string(getID()) +
        ", " + std::to_string(getGroupNumber()) +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_at_zero_diversity) +
        ", " + std::to_string(_happiness_at_one_diversity) +
        ", " + std::to_string(_diversity_where_rise_happens) +
        ")"; 
}

double Resident_StepUp::implCalculateHappiness (
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
        return _happiness_at_zero_diversity; // unhappy to be alone
    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

const House* Resident_StepUp::findHome(
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

const House* Resident_StepUp::findBestHome(
    const House* oldHouse,
    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjacentHouses,
    std::unordered_map<const House*, Resident*> houseToResMap
) const
{
    return findHome(oldHouse, openHousesAndTheirAdjacentHouses, houseToResMap);
}