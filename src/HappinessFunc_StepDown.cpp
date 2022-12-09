#include "HappinessFunc_StepDown.h"
#include <iostream>

HappinessFunc_StepDown::HappinessFunc_StepDown ( 
    double happinessWithZeroNeighbors,
    double highHappinessValue, 
    double lowHappinessValue, 
    double stepDownHappensAt): 
    _happiness_at_zero_diversity{happinessWithZeroNeighbors},
    _high_happiness_value{highHappinessValue},
    _low_happiness_value{lowHappinessValue},
    _where_drop_happens{stepDownHappensAt}
{   
    if (happinessWithZeroNeighbors < 0.0   || 
        happinessWithZeroNeighbors > 100.0 ||
        highHappinessValue       < 0.0   || 
        highHappinessValue       > 100.0 ||
        lowHappinessValue        < 0.0   ||
        lowHappinessValue        > 100.0)
    {
       throw std::invalid_argument("happinessAtZeroDiversity, highHappinessValue"
            " and lowHappinessValue"
            " must be between 0.0 and 100.0 inclusive.");
    }
    if (_high_happiness_value < _low_happiness_value)
    {   std::cout << "HappinessFunc_Stepdown error: " << _high_happiness_value << ", " << _low_happiness_value << std::endl;
        throw std::invalid_argument("highHappinessValue must be larger than "
            "lowHappinessValue.");
    }
    if (stepDownHappensAt < 0 || stepDownHappensAt > 100.0)
    {
        throw std::invalid_argument("stepDownHappensAt must be between 0.0 "
            "and 100.0 inclusive.");
    }
    
}

double HappinessFunc_StepDown::getHappiness ( int tot_num_of_possible_neighbors, 
                                              int num_of_like_neighbors, 
                                              int num_of_diff_neighbors) const
{
    (void)tot_num_of_possible_neighbors;
    int num_of_neighbors = (num_of_diff_neighbors + num_of_like_neighbors);
    if (num_of_neighbors == 0)
    {
        return _happiness_at_zero_diversity;
    }

    double diversity = num_of_diff_neighbors / (double)num_of_neighbors;
    if (diversity < _where_drop_happens)
    {
        return _high_happiness_value;
    }
    return _low_happiness_value;

}