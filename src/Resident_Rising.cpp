#include "Resident_Rising.h"
#include <iostream>

Resident_Rising::Resident_Rising ( 
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    double happinessWithZeroNeighbors,
    double happinessValueAtZeroDiversity,
    double happinessValueAtOneDiversity
    ):
    Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
    _happiness_with_zero_neighbors(happinessWithZeroNeighbors),
    _happiness_at_zero_diversity(happinessValueAtZeroDiversity),
    _happiness_at_one_diversity(happinessValueAtOneDiversity),
    _happiness_func{
        happinessWithZeroNeighbors,
        happinessValueAtZeroDiversity, 
        happinessValueAtOneDiversity
    }
{
}

std::string Resident_Rising::toStrBasic() const
{
    return "Res_Rising(id, clr, mov, goal, hap0, hap1): (" + 
        std::to_string(getID()) +
        ", " + std::to_string(getGroupNumber()) +
        ", " + std::to_string(getAllowedMovementDistance()) +
        ", " + std::to_string(getHappinessGoal()) +
        ", " + std::to_string(_happiness_at_zero_diversity) +
        ", " + std::to_string(_happiness_at_one_diversity) +
        ")"; 
}

double Resident_Rising::implCalculateHappiness (
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{   
    if (neighbors.empty())
        return _happiness_with_zero_neighbors;
    int like  = 0;
    int diff  = 0;
    for (Resident* res : neighbors)
    {
        if (res->getGroupNumber() == getGroupNumber())
        {
            like++;
        }
        else
            diff++;
        
    }
    if ( (like + diff) == 0 )
        return _happiness_at_zero_diversity; // unhappy to be alone
    return _happiness_func.calcHappiness(numOfAdjacentHouses, like, diff);
}