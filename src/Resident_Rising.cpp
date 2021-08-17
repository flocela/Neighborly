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
        ", " + colorMap[getColor()] +
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
    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

House* Resident_Rising::findHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesToNeighbors,
    std::map<House*, Resident*> houseToResMap
) const
{
    (void) oldHouse;
    (void) openHousesToNeighbors;
    (void) houseToResMap;
    return oldHouse;
}

House* Resident_Rising::findBestHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesToNeighbors,
    std::map<House*, Resident*> houseToResMap
) const
{
    (void) oldHouse;
    (void) openHousesToNeighbors;
    (void) houseToResMap;
    return oldHouse;
}