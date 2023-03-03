#include "Resident_UsingFunction.h"

using namespace std;

Resident_UsingFunction::Resident_UsingFunction (
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    std::unique_ptr<HappinessFunc> happinessFunc,
    std::string name
): Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
   _hap_func{move(happinessFunc)},
   _name{name}
{}

std::string Resident_UsingFunction::implimentToStrBasic () const
{
    string funcType = "Resident Using Function: "; 
    return funcType + _hap_func->toStrBasic();
}

double Resident_UsingFunction::implimentHappiness(
    std::set<Resident*> neighbors,
    int numOfAdjacentHouses
) const
{
    int like  = 0;
    int diff  = 0;
    for (Resident* res : neighbors)
    {
        if (res->getGroupId() == getGroupId())
            like++;
        else
            diff++;
    }
    return _hap_func->calcHappiness(numOfAdjacentHouses, like, diff);
}