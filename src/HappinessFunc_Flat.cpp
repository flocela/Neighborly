#include "HappinessFunc_Flat.h"

#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

HappinessFunc_Flat::HappinessFunc_Flat(double happinessWithNoNeighbors, double happinessValue):
    _happ_with_no_neighbors{happinessWithNoNeighbors},
    _flat_happiness_val{happinessValue}
{   
    if (_flat_happiness_val  < 0.0 || _flat_happiness_val  > 100.0)
    { 
        throw invalid_argument("Constant happiness value must be between 0.0"
        " and 100.0 inclusive.");
    }
    if (_happ_with_no_neighbors < 0.0 || _happ_with_no_neighbors > 100)
    {
        throw invalid_argument("Happiness value for no neighbors must be between 0.0"
        " and 100.0 inclusive.");
    }
}

double HappinessFunc_Flat::calcHappiness ( 
    int tot_num_of_possible_neighbors, 
    int num_of_like_neighbors, 
    int num_of_diff_neighbors) const
{
    (void) tot_num_of_possible_neighbors;

    if (num_of_like_neighbors + num_of_diff_neighbors == 0)
    {
        return _happ_with_no_neighbors;
    }

    return _flat_happiness_val;
}

double HappinessFunc_Flat::getLargestValue () const
{
    return max(_flat_happiness_val, _happ_with_no_neighbors);
}

double HappinessFunc_Flat::getSmallestValue () const
{
    return min(_flat_happiness_val, _happ_with_no_neighbors);
}

string HappinessFunc_Flat::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "Flat Happiness Function, happiness:: no neighbors: ";
    returnStream << fixed << setprecision(2) << _happ_with_no_neighbors;
    returnStream << ", constant happiness: ";
    returnStream << fixed << setprecision(2) << _flat_happiness_val;
    
    return returnStream.str();
}