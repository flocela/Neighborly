#include "HappinessFunc_Rising.h"

#include <sstream>
#include <iomanip>

using namespace std;

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
        throw invalid_argument("values of happiness at zero diversity must be"
        " between 0.0 and 100.0 inclusive.");
    }
    if ( _happ_at_zero_diversity < 0.0 ||
         _happ_at_zero_diversity > 100.0 )
    {
        throw invalid_argument("values of happiness at one diversity must be"
        " between 0.0 and 100.0 inclusive.");
    }
        
    if (_happ_at_one_diversity <= _happ_at_zero_diversity)
        throw invalid_argument("hapinessAtOneDiversity must be larger than"
        " at happinessAtZeroDiversity.");
}

double HappinessFunc_Rising::getLargestValue () const
{
    return max(_happ_at_one_diversity, _happ_with_no_neighbors);
}

double HappinessFunc_Rising::getSmallestValue () const
{
    return min(_happ_at_zero_diversity, _happ_with_no_neighbors);
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


string HappinessFunc_Rising::toStrBasic () const
{
    stringstream returnStream;
    returnStream << "Rising Happiness Function, happiness:: no neighbors: ";
    returnStream << fixed << setprecision(2) << _happ_with_no_neighbors;
    returnStream << ", zero diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_zero_diversity;
    returnStream << ", one diversity: ";
    returnStream << fixed << setprecision(2) << _happ_at_one_diversity;
    
    return returnStream.str();
}