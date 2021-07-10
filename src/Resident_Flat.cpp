#include "Resident_Flat.h"
#include <iostream>
Resident_Flat::Resident_Flat (
    int    id,
    Color  color,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessValue):
    Resident(id, color, allowedMovementDistance, happinessGoal),
    _happiness_func{happinessValue}
{}

double Resident_Flat::getHappiness(
    std::vector<Color> neighbors,
    int numOfAdjacentHouses
) const
{
    (void) neighbors;
    int like  = 0;
    int diff  = 0;

    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}

House* Resident_Flat::findHome (
    City* city, 
    House* oldHouse,
    std::set<House*> openHouses,
    std::map<House*, Resident*> houseToResMap
) const
{
(void) city;
(void) oldHouse;
(void) openHouses;
(void) houseToResMap;
return oldHouse;
}

House* Resident_Flat::findBestHome(
    City* city, 
    House* oldHouse,
    std::set<House*> openHouses,
    std::map<House*, Resident*> houseToResMap
) const
{
(void) city;
(void) oldHouse;
(void) openHouses;
(void) houseToResMap;
return oldHouse;
}