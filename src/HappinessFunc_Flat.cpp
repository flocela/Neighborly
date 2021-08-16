#include "HappinessFunc_Flat.h"

HappinessFunc_Flat::HappinessFunc_Flat(double happinessValue): 
    _result{happinessValue}
{   
    if (_result  < 0.0 || _result  > 1.0)
       throw "HappinessValue must be between 0.0 and 1.0 inclusive.";
}

double HappinessFunc_Flat::getHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    (void) tot_num_of_possible_neighbors;
    (void) num_of_like_neighbors;
    (void) num_of_diff_neighbors;
    return _result;
}