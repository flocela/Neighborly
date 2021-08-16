#include "HappinessFunc_Falling.h"

HappinessFunc_Falling::HappinessFunc_Falling (double happinessAtZeroPercentDiversity,
                                            double happinessAt100PercentDiversity): 
    _happiness_at_zero_percent_diversity{happinessAtZeroPercentDiversity},
    _happiness_at_hundred_percent_diversity{happinessAt100PercentDiversity}
{
    if (_happiness_at_zero_percent_diversity < 0.0 || 
        _happiness_at_zero_percent_diversity > 1.0 ||
        _happiness_at_hundred_percent_diversity < 0.0 ||
        _happiness_at_hundred_percent_diversity > 1.0)
    {
        throw "happiness At Zero Diversity and One Diversity must be "
        "between 0.0 and 1.0 inclusive.";
    }
    if (_happiness_at_hundred_percent_diversity >
        _happiness_at_zero_percent_diversity)
    {
        throw "happiness at Zero Diversity must be less than"
        "value at One Diversity.";
    }

}

double HappinessFunc_Falling::getHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    (void) tot_num_of_possible_neighbors;
    double diversity = num_of_diff_neighbors / (double)(num_of_diff_neighbors + num_of_like_neighbors);
    return _happiness_at_zero_percent_diversity + 
            (_happiness_at_hundred_percent_diversity-_happiness_at_zero_percent_diversity) * diversity;
}