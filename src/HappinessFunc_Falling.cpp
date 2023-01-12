#include "HappinessFunc_Falling.h"

HappinessFunc_Falling::HappinessFunc_Falling (
    double happinessWithNoNeighbors,
    double happinessAtZeroPercentDiversity,
    double happinessAt100PercentDiversity
):  _happ_with_no_neighbors{happinessWithNoNeighbors},
    _happ_at_zero_percent_diversity{happinessAtZeroPercentDiversity},
    _happ_at_hundred_percent_diversity{happinessAt100PercentDiversity}
{
    if (_happ_at_zero_percent_diversity < 0.0 || 
        _happ_at_zero_percent_diversity > 100.0 )
    {
        throw "happiness At Zero Diversity must be "
        "between 0.0 and 100.0 inclusive.";
    }
    if (_happ_at_hundred_percent_diversity < 0.0 ||
        _happ_at_hundred_percent_diversity > 100.0)
    {
        throw "happiness At One Diversity must be "
        "between 0.0 and 100.0 inclusive.";
    }
    if (_happ_at_hundred_percent_diversity >=
        _happ_at_zero_percent_diversity)
    {
        throw "happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.";
    }

}

double HappinessFunc_Falling::calcHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    (void) tot_num_of_possible_neighbors;

    if (num_of_like_neighbors + num_of_diff_neighbors == 0)
    {
        return _happ_with_no_neighbors;
    }

    double diversity = num_of_diff_neighbors / 
                       (double)(num_of_diff_neighbors + num_of_like_neighbors);

    return _happ_at_zero_percent_diversity + 
           (_happ_at_hundred_percent_diversity -_happ_at_zero_percent_diversity) * diversity;
}