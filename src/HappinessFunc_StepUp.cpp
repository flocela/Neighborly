#include "HappinessFunc_StepUp.h"
#include <iostream>

HappinessFunc_StepUp::HappinessFunc_StepUp (
    double happinessAtZeroDiversity,
    double happinessAtOneDiversity,
    double whereRiseHappens): 
    _happiness_at_zero_diversity{happinessAtZeroDiversity},
    _happiness_at_one_diversity{happinessAtOneDiversity},
    _diversity_where_rise_happens{whereRiseHappens}
{
    if (happinessAtZeroDiversity  < 0.0 || 
        happinessAtZeroDiversity  > 1.0 ||
        happinessAtOneDiversity   < 0.0 ||
        happinessAtOneDiversity   > 1.0)
        throw "happinessAtZeroDiversity and happinessAtOneDiversity "
             "must be between 0.0 and 1.0 inclusive.";
    if (happinessAtZeroDiversity >= happinessAtOneDiversity)
        throw "happinessAtZeroDiversity must be smaller than happinessAtOneDiversity.";
    if (whereRiseHappens < 0 || whereRiseHappens > 1.0)
        throw "whereRiseHappens must be between 0.0 and 1.0 inclusive.";
}

double HappinessFunc_StepUp::getHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{   (void) tot_num_of_possible_neighbors;
    double diversity = num_of_diff_neighbors / (double)(num_of_diff_neighbors + num_of_like_neighbors);
    if (diversity < _diversity_where_rise_happens)
        return _happiness_at_zero_diversity;
    return _happiness_at_one_diversity;

}