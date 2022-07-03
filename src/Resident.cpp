#include "Resident.h"

Resident::Resident (
    int    id,
    int    groupNumber,
    double allowedMovementDistance,
    double happinessGoal):
    _ID{id}, 
    _group_number{groupNumber}, 
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

bool Resident:: operator< (const Resident& other) const
{
    return _ID < other._ID;
}
