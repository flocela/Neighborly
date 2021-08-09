#include "Resident_Flat.h"
#include <iostream>
Resident_Flat::Resident_Flat (
    int    id,
    Color  color,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValue):
    Resident(id, color, allowedMovementDistance, happinessGoal),
    _happiness_val(happinessValue),
    _happiness_func{happinessValue}
{}

std::string Resident_Flat::toStrBasic () const
{
    return "Res_Flat(id, clr, mov, goal, hapV): (" + 
        std::to_string(getID()) +
        ", " + colorMap[getColor()] +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_val) +
        ")";
}

double Resident_Flat::implCalculateHappiness(
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
    (void) neighbors;
    int like  = 0;
    int diff  = 0;

    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

House* Resident_Flat::findHome (
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

House* Resident_Flat::findBestHome (
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

