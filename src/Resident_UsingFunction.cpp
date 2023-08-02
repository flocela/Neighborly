#include "Resident_UsingFunction.h"
#include "ResidentTemplate_UsingFunction.h"
#include <iostream>
using namespace std;

Resident_UsingFunction::Resident_UsingFunction (
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    unique_ptr<HappinessFunc> happinessFunc
): Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
   _hap_func{move(happinessFunc)}
{}

double Resident_UsingFunction::getMaximumPossibleHappiness () const
{
    return _hap_func->getLargestValue();
}
double Resident_UsingFunction::getLeastPossibleHappiness () const
{
    return _hap_func->getSmallestValue();
}

std::string Resident_UsingFunction::implimentToStrBasic () const
{
    string funcType = "Resident Using Function: "; 
    return funcType + _hap_func->toStrBasic();
}

double Resident_UsingFunction::implimentHappiness(
    const std::unordered_set<const Resident*>& neighbors,
    int numOfAdjacentHouses
) const
{
    int like  = 0;
    int diff  = 0;
    for (const Resident* res : neighbors)
    {
        if (res->getGroupId() == getGroupId())
            like++;
        else
            diff++;
    }
    return _hap_func->calcHappiness(numOfAdjacentHouses, like, diff);
}

std::unique_ptr<const ResidentTemplate> Resident_UsingFunction::getTemplate () const
{
    return make_unique<const ResidentTemplate_UsingFunction>(
        getAllowedMovementDistance(),
        getHappinessGoal(),
        toStrType()
    );
}