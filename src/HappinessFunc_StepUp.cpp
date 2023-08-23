#include "HappinessFunc_StepUp.h"
#include <iostream>

#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

HappinessFunc_StepUp::HappinessFunc_StepUp (
    double happinessWthZeroNeighbors,
    double happinessAtStart,
    double happinessAtEnd,
    double stepUp):
    _happ_with_zero_neighbors{happinessWthZeroNeighbors},
    _happ_at_start{happinessAtStart},
    _happ_at_end{happinessAtEnd},
    _step_up{stepUp}
{
    if (_happ_with_zero_neighbors < 0.0 ||
        _happ_with_zero_neighbors > 100.0 ||
        _happ_at_start  < 0.0 || 
        _happ_at_start  > 100.0 ||
        _happ_at_end   < 0.0 ||
        _happ_at_end   > 100.0)
        throw invalid_argument("happinessWithZeroNeighbors, happinessAtStart,"
        " and happinessAtEnd must be between 0.0 and 100.0 inclusive.");

    if (happinessAtStart >= happinessAtEnd)
        throw invalid_argument("happinessAtStart must be less than happinessAtEnd.");
        
    if (stepUp < 0 || stepUp > 1.0)
        throw invalid_argument("stepUp must be between 0.0 and 1.0 inclusive.");
}

double HappinessFunc_StepUp::getLargestValue () const
{
    return max(_happ_at_end, _happ_with_zero_neighbors);
}

double HappinessFunc_StepUp::getSmallestValue () const
{
    return min(_happ_at_start, _happ_with_zero_neighbors);
}

double HappinessFunc_StepUp::calcHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{   
    (void)tot_num_of_possible_neighbors;

    if (num_of_diff_neighbors + num_of_like_neighbors == 0)
    {
        return _happ_with_zero_neighbors;
    }

    double diversity = num_of_diff_neighbors /
                       (double)(num_of_diff_neighbors + num_of_like_neighbors);
    if (diversity <= _step_up)
    {
        return _happ_at_start;
    }
    else
    {
        return _happ_at_end;
    }

}

string HappinessFunc_StepUp::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "StepUp Happiness Function. Happiness with no neighbors is ";
    returnStream << fixed << setprecision(2) << _happ_with_zero_neighbors;
    returnStream << "; at 0.0 diversity is ";
    returnStream << fixed << setprecision(2) << _happ_at_start;
    returnStream << "; at 1.0 diversity is ";
    returnStream << fixed << setprecision(2) << _happ_at_end;
    returnStream << "; drop's diversity location is ";
    returnStream << fixed << setprecision(2) << _step_up;
    returnStream << ".";
    
    return returnStream.str();
}