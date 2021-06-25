#include "Resident_Flat.h"
#include <iostream>
Resident_Flat::Resident_Flat (
    int    id,
    Color  color,
    double allowedMovementDistance,
    double happinessGoal,
    bool   happyAtGoal,
    double happinessValue):
    Resident(id, color, allowedMovementDistance, happinessGoal, happyAtGoal),
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
