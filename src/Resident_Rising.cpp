#include "Resident_Rising.h"
#include <iostream>

Resident_Rising::Resident_Rising ( 
    int id,
    Color color,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity
    ):
    Resident(id, color, allowedMovementDistance, happinessGoal),
    _happiness_at_zero_diversity(happinessValueAtZeroDiversity),
    _happiness_at_one_diversity(happinessValueAtOneDiversity),
    _happiness_func{
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity
    }
{
}

std::string Resident_Rising::toStrBasic() const
{
    return "Res_Rising(id, clr, mov, goal, hap0, hap1): (" + 
        std::to_string(getID()) +
        ", " + _the_color_infos[getColor()]._my_string +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_at_zero_diversity) +
        ", " + std::to_string(_happiness_at_one_diversity) +
        ")"; 
}

double Resident_Rising::implCalculateHappiness (
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
    int like  = 0;
    int diff  = 0;
    for (Resident* res : neighbors)
    {
        if (res->getColor() == getColor())
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

House* Resident_Rising::findHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::map<House*, Resident*> houseToResMap
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

House* Resident_Rising::findBestHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::map<House*, Resident*> houseToResMap
) const
{
    House* bestHouse = oldHouse;
    double bestScore = -1;

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
        if (happiness > bestScore) 
        {
            bestScore = happiness;
            bestHouse = currHouse;
        }
    }

    return bestHouse;
}