#include "HappinessFunc_StepDown.h"
#include <iostream>

HappinessFunc_StepDown::HappinessFunc_StepDown ( 
    double happinessAtZeroDiversity, 
    double happinessAtOneDiversity, 
    double stepDownHappensAt): 
    _happiness_at_zero_diversity{happinessAtZeroDiversity},
    _happiness_at_one_diversity{happinessAtOneDiversity},
    _where_drop_happens{stepDownHappensAt}
{
    if (happinessAtZeroDiversity  < 0.0 || 
        happinessAtZeroDiversity  > 1.0 ||
        happinessAtOneDiversity   < 0.0 ||
        happinessAtOneDiversity   > 1.0)
       throw "happinessAtZeroDiversity and happinessAtOneDiversity "
             "must be between 0.0 and 1.0 inclusive.";
    if (happinessAtZeroDiversity <= happinessAtOneDiversity)
        throw "happinessAtZeroDiversity must be larger than happinessAtOneDiversity.";
    if (stepDownHappensAt < 0 || stepDownHappensAt > 1.0)
        throw "stepDownHappensAt must be between 0.0 and 1.0 inclusive.";
    
}

double HappinessFunc_StepDown::getHappiness ( int tot_num_of_possible_neighbors, 
                                              int num_of_like_neighbors, 
                                              int num_of_diff_neighbors) const
{
    (void)tot_num_of_possible_neighbors;
    int num_of_neighbors = (num_of_diff_neighbors + num_of_like_neighbors);

    double diversity = num_of_diff_neighbors / (double)num_of_neighbors;
    if (diversity < _where_drop_happens)
        return _happiness_at_zero_diversity;
    return _happiness_at_one_diversity;

}