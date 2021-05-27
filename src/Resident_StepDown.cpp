#include "Resident_StepDown.h"
#include <iostream>

Resident_StepDown::Resident_StepDown ( int id,
                                       Color color,
                                       double allowedMovementDistance,
                                       double happinessGoal,
                                       double happinessValueAtZeroDiversity,
                                       double happinessValueAtOneDiversity,
                                       double diversityWhereDropHappens):
    Resident(id, color, allowedMovementDistance, happinessGoal),
    _happiness_func{happinessValueAtZeroDiversity, 
                    happinessValueAtOneDiversity, 
                    diversityWhereDropHappens}
{
    
}

double Resident_StepDown::getHappiness(std::vector<Color> neighbors) const
{
    int total = neighbors.size();
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

    return _happiness_func.getHappiness(total, like, diff);
}