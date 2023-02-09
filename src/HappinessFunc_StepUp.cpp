#include "HappinessFunc_StepUp.h"
#include <iostream>

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
    if (happinessAtStart  < 0.0 || 
        happinessAtStart  > 100.0 ||
        happinessAtEnd   < 0.0 ||
        happinessAtEnd   > 100.0)
        throw invalid_argument("happinessWithZeroNeighbors, happinessAtStart,"
        " and happinessAtEnd must be between 0.0 and 100.0 inclusive.");
    if (happinessAtStart > happinessAtEnd)
        throw invalid_argument("happinessAtStart must be less than or equal to happinessAtEnd.");
    if (stepUp < 0 || stepUp > 1.0)
        throw invalid_argument("stepUp must be between 0.0 and 1.0 inclusive.");
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
    if (diversity < _step_up)
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
    returnStream << "HappinessFunc: Step Up. happiness:: with no neighbors: ";
    returnStream << fixed << setprecision(2) << _happ_with_zero_neighbors;
    returnStream << " at start diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_start;
    returnStream << " at end diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_end;
    returnStream << " step-up's diversity location: ";
    returnStream << fixed << setprecision(2) << _step_up;
    
    return returnStream.str();
}