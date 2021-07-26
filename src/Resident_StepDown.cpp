#include "Resident_StepDown.h"
#include <iostream>

Resident_StepDown::Resident_StepDown ( 
    int id,
    Color color,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity,
    double diversityWhereDropHappens):
    Resident(id, color, allowedMovementDistance, happinessGoal),
    _happiness_func{
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity, 
        diversityWhereDropHappens
    }
{
}

double Resident_StepDown::getHappiness(
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

House* Resident_StepDown::findHome(
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

House* Resident_StepDown::findBestHome(
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