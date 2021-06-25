#include "Resident.h"

Resident::Resident (
    int    id,
    Color  color,
    double allowedMovementDistance,
    double happinessGoal,
    bool   happyAtGoal):
    _ID{id}, 
    _color{color}, 
    _allowed_movement_distance{allowedMovementDistance}, 
    _happiness_goal{happinessGoal},
    _happy_at_goal{happyAtGoal}             
{
    if (happinessGoal < 0.0 || happinessGoal > 1.0)
        throw "HappinessGoal must be between 0.0 and 1.0 inclusive.";
}