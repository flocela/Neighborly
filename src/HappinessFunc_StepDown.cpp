#include "HappinessFunc_StepDown.h"

#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

HappinessFunc_StepDown::HappinessFunc_StepDown ( 
    double happinessWithZeroNeighbors,
    double happinessAtStart, 
    double happinessAtEnd, 
    double stepDown
): _happ_with_zero_neighbors{happinessWithZeroNeighbors},
   _happ_at_start{happinessAtStart},
   _happ_at_end{happinessAtEnd},
   _step_down{stepDown}
{   
    if (_happ_with_zero_neighbors < 0.0   || 
        _happ_with_zero_neighbors > 100.0 ||
        _happ_at_start < 0.0   || 
        _happ_at_start > 100.0 ||
        _happ_at_end   < 0.0   ||
        _happ_at_end   > 100.0)
    {
       throw std::invalid_argument("happinessWithZeroNeighbors, happinessAtStart"
            " and happinessAtEnd"
            " must be between 0.0 and 100.0 inclusive.");
    }
    if (_happ_at_start <= _happ_at_end)
    {   
        throw std::invalid_argument("starting happiness value must be larger"
        " than ending happiness value.");
    }
    if (_step_down < 0 || _step_down > 1.0)
    {
        throw std::invalid_argument("step down location must be between 0.0 "
            "and 1.0 inclusive.");
    }
    
}

double HappinessFunc_StepDown::getLargestValue () const
{
    return max(_happ_at_start, _happ_with_zero_neighbors);
}

double HappinessFunc_StepDown::getSmallestValue () const
{
    return min(_happ_at_end, _happ_with_zero_neighbors);
}

double HappinessFunc_StepDown::calcHappiness (
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
    if (diversity <= _step_down)
    {
        return _happ_at_start;
    }
    else
    {
        return _happ_at_end;
    }
}

string HappinessFunc_StepDown::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "StepDown Happiness Function, happiness:: no neighbors: ";
    returnStream << fixed << setprecision(2) << _happ_with_zero_neighbors;
    returnStream << ", zero diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_start;
    returnStream << ", one diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_end;
    returnStream << ", drop's diversity location: ";
    returnStream << fixed << setprecision(2) << _step_down;
    
    return returnStream.str();
}