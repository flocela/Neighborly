#include "HappinessFunc_Falling.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

HappinessFunc_Falling::HappinessFunc_Falling (
    double happinessWithNoNeighbors, 
    double happinessAtZeroDiversity,
    double happinessAtOneDiversity
):  _happ_with_no_neighbors{happinessWithNoNeighbors},
    _happ_at_zero_diversity{happinessAtZeroDiversity},
    _happ_at_one_diversity{happinessAtOneDiversity}
{

    if (_happ_at_zero_diversity < 0.0 || 
        _happ_at_zero_diversity > 100.0 )
    {
        throw invalid_argument("happiness At Zero Diversity must be "
        "between 0.0 and 100.0 inclusive.");
    }
    if (_happ_at_one_diversity < 0.0 ||
        _happ_at_one_diversity > 100.0)
    {
        throw invalid_argument("happiness At One Diversity must be "
        "between 0.0 and 100.0 inclusive.");
    }
    if (_happ_at_zero_diversity <= _happ_at_one_diversity)
    {
        throw invalid_argument("happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.");
    } 
}

double HappinessFunc_Falling::getLargestValue () const
{
    return max(_happ_with_no_neighbors, _happ_at_zero_diversity);
}

double HappinessFunc_Falling::getSmallestValue () const
{   
    return min(_happ_with_no_neighbors, _happ_at_one_diversity);
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

    return _happ_at_zero_diversity + 
           (_happ_at_one_diversity -_happ_at_zero_diversity) * diversity;
}

string HappinessFunc_Falling::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "Falling Happiness Function, ";
    returnStream << "happiness:: no neighbors: ";
    returnStream << fixed << setprecision(2) << _happ_with_no_neighbors;
    returnStream << ", zero diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_zero_diversity;
    returnStream << ", one hundred diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_one_diversity;
    
    return returnStream.str();
}