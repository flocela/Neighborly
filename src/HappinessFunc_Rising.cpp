#include "HappinessFunc_Rising.h"

HappinessFunc_Rising::HappinessFunc_Rising (double happinessAtZeroDiversity,
                                          double happinessAtOneDiversity): 
    _happiness_at_zero_diversity{happinessAtZeroDiversity},
    _happiness_at_one_diversity{happinessAtOneDiversity}
{
    if (_happiness_at_one_diversity  < 0.0 ||
        _happiness_at_one_diversity  > 1.0 ||
        _happiness_at_zero_diversity < 0.0 ||
        _happiness_at_zero_diversity > 1.0)
        throw "values of happiness at zero and one must be between 0.0 and 1.0 inclusive.";
    if (_happiness_at_one_diversity <= _happiness_at_zero_diversity)
        throw "hapinessAtOneDiversity must be larger than at happinessAtZeroDiversity.";
}

double HappinessFunc_Rising::getHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    double slope = (_happiness_at_one_diversity-_happiness_at_zero_diversity)/1;
    double diversity_diff = num_of_diff_neighbors / 
                            (double)(num_of_diff_neighbors + num_of_like_neighbors);
    return _happiness_at_zero_diversity + ( slope * diversity_diff );
}