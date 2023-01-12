#include "HappinessFunc_Rising.h"

HappinessFunc_Rising::HappinessFunc_Rising (
    double happinessWithNoNeighbors,
    double happinessAtZeroDiversity,
    double happinessAtOneDiversity
): _happ_with_no_neighbors(happinessWithNoNeighbors),
   _happ_at_zero_diversity{happinessAtZeroDiversity},
   _happ_at_one_diversity{happinessAtOneDiversity}
{
    if ( _happ_at_one_diversity  < 0.0 ||
         _happ_at_one_diversity  > 100.0 )
    {
        throw "values of happiness at zero diversity must be between 0.0 and 100.0 inclusive.";
    }
    if ( _happ_at_zero_diversity < 0.0 ||
         _happ_at_zero_diversity > 1.0 )
    {
        throw "values of happiness at one diversity must be between 0.0 and 100.0 inclusive.";
    }
        
    if (_happ_at_one_diversity <= _happ_at_zero_diversity)
        throw "hapinessAtOneDiversity must be larger than at happinessAtZeroDiversity.";
}

double HappinessFunc_Rising::calcHappiness ( 
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
    return _happ_at_zero_diversity + 
           (_happ_at_one_diversity -_happ_at_zero_diversity) * diversity;
}