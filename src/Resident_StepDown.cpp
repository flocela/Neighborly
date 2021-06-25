#include "Resident_StepDown.h"
#include <iostream>

Resident_StepDown::Resident_StepDown ( 
    int id,
    Color color,
    double allowedMovementDistance,
    double happinessGoal,
    bool   happyAtGoal,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity,
    double diversityWhereDropHappens):
    Resident(id, color, allowedMovementDistance, happinessGoal, happyAtGoal),
    _happiness_func{
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity, 
        diversityWhereDropHappens
    }
{
}

double Resident_StepDown::getHappiness(
    std::vector<Color> neighbors,
    int numOfAdjacentHouses
) const
{std::cout << "Resident_StepDown line 26" << std::endl;
    int like  = 0;
    int diff  = 0;
    
    for (Color color : neighbors)
    {
        if (color == getColor())
        {
            like++;
        }
        else
            diff++;
        
    }

    return _happiness_func.getHappiness(numOfAdjacentHouses, like, diff);
}