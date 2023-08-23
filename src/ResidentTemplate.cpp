#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include "ResidentTemplate.h"

using namespace std;

ResidentTemplate::ResidentTemplate (
    double allowedMovementDistance,
    double happinessGoal
): _allowed_movement_distance{allowedMovementDistance}, 
   _happiness_goal{happinessGoal}
{
    if (happinessGoal < 0.0 || happinessGoal > 100.0)
    {   
        throw std::invalid_argument("HappinessGoal must be between 0.0 and 100.0 inclusive.");
    }
}

double ResidentTemplate::getAllowedMovementDistance () const
{
    return _allowed_movement_distance;
}

double ResidentTemplate::getHappinessGoal () const
{
    return _happiness_goal;
}