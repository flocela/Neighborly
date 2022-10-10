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
    if (happinessGoal < 0.0 || happinessGoal > 100.0)
    {
        throw std::invalid_argument("HappinessGoal must be between 0.0 and 100.0 inclusive.");
    }
        
}

double Resident::calculateHappiness ( 
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
    return implCalculateHappiness (neighbors, numOfAdjacentHouses);
}

double Resident::setHappiness (std::set<Resident*> neighbors, int numOfAdjacentHouses)
{
    _curr_happiness = calculateHappiness(neighbors, numOfAdjacentHouses);
    return _curr_happiness;
}

bool Resident:: operator< (const Resident& other) const
{
    return _ID < other._ID;
}
