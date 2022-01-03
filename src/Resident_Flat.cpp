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
        ", " + _the_color_infos[getColor()]._my_string +
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
    if ( (like + diff) == 0 )
        return _happiness_val; // regular value when alone
    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

House* Resident_Flat::findHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::map<House*, Resident*> houseToResMap
) const
{
    (void) houseToResMap;
    for (auto h2SH : openHousesAndTheirAdjacentHouses)
    {
        return h2SH.first;
    }
    return oldHouse;
}

House* Resident_Flat::findBestHome (
    House* oldHouse,
    std::map<House*, std::set<House*>> openHousesAndTheirAdjacentHouses,
    std::map<House*, Resident*> houseToResMap
) const
{
    return findHome(oldHouse, openHousesAndTheirAdjacentHouses, houseToResMap);
}

