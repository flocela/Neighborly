#include "Resident.h"

Resident::Resident (
    int    id,
    Color  color,
    double allowedMovementDistance,
    double happinessGoal):
    _ID{id}, 
    _color{color}, 
    _allowed_movement_distance{allowedMovementDistance}, 
    _happiness_goal{happinessGoal}            
{
    if (happinessGoal < 0.0 || happinessGoal > 1.0)
        throw "HappinessGoal must be between 0.0 and 1.0 inclusive.";
}

double Resident::calculateHappiness ( 
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
)
{
    _curr_happiness = implCalculateHappiness (neighbors, numOfAdjacentHouses);
    return _curr_happiness;
}
