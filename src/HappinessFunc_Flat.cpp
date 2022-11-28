#include "HappinessFunc_Flat.h"
#include <iostream>

HappinessFunc_Flat::HappinessFunc_Flat(double happinessValue): 
    _result{happinessValue}
{   
    if (_result  < 0.0 || _result  > 100.0) // TODO this  error doesn't show , all I get is terminate called after throwing an instace of 'char const*'
    { 
        throw "HappinessValue must be between 0.0 and 1.0 inclusive.";
    }
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