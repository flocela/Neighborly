#include "HappinessFunc_StepUp.h"
#include <iostream>

HappinessFunc_StepUp::HappinessFunc_StepUp (
    double happinessWthZeroNeighbors,
    double happinessAtStart,
    double happinessAtEnd,
    double stepUp):
    _happ_with_zero_neighbors{happinessWthZeroNeighbors},
    _happ_at_start{happinessAtStart},
    _happ_at_end{happinessAtEnd},
    _step_up{stepUp}
{
    if (happinessAtStart  < 0.0 || 
        happinessAtStart  > 100.0 ||
        happinessAtEnd   < 0.0 ||
        happinessAtEnd   > 100.0)
        throw "happinessWithZeroNeighbors, happinessAtStart and happinessAtEnd "
             "must be between 0.0 and 100.0 inclusive.";
    if (happinessAtStart >= happinessAtEnd)
        throw "happinessAtStart must be smaller than happinessAtEnd.";
    if (stepUp < 0 || stepUp > 1.0)
        throw "stepUp must be between 0.0 and 1.0 inclusive.";
}

double HappinessFunc_StepUp::calcHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{   
    (void)tot_num_of_possible_neighbors;

    if (num_of_diff_neighbors + num_of_like_neighbors == 0)
    {
        return _happ_with_zero_neighbors;
    }

    double diversity = num_of_diff_neighbors /
                       (double)(num_of_diff_neighbors + num_of_like_neighbors);
    if (diversity < _step_up)
    {
        return _happ_at_start;
    }
    else
    {
        return _happ_at_end;
    }

}