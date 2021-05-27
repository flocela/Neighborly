#include "HappinessFunc_Falling.h"

HappinessFunc_Falling::HappinessFunc_Falling (double happinessAtZeroPercentDiversity,
                                            double happinessAt100PercentDiversity): 
    _happiness_at_zero_percent_diversity{happinessAtZeroPercentDiversity},
    _happiness_at_hundred_percent_diversity{happinessAt100PercentDiversity}
{}

double HappinessFunc_Falling::getHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    double diversity = num_of_diff_neighbors / (num_of_diff_neighbors + num_of_like_neighbors);
    return _happiness_at_zero_percent_diversity - 
            (_happiness_at_hundred_percent_diversity/_happiness_at_zero_percent_diversity) * diversity;
}