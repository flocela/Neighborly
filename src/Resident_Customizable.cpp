#include "Resident_Customizable.h"
#include "ResidentTemplate_UsingFunction.h"
#include <iostream>
using namespace std;

Resident_Customizable::Resident_Customizable (
    int id,
    int groupNumber,
    double allowedMovementDistance,
    double happinessGoal,
    unique_ptr<HappinessFunc> happinessFunc
): 
    Resident(id, groupNumber, allowedMovementDistance, happinessGoal),
    _hap_func{move(happinessFunc)}
{}

double Resident_Customizable::getMaximumPossibleHappiness () const
{
    return _hap_func->getLargestValue();
}

double Resident_Customizable::getLeastPossibleHappiness () const
{
    return _hap_func->getSmallestValue();
}

std::unique_ptr<const ResidentTemplate> Resident_Customizable::getTemplate () const
{
    return make_unique<const ResidentTemplate_UsingFunction>(
        getAllowedMovementDistance(),
        getHappinessGoal(),
        getType()
    );
}

double Resident_Customizable::implimentHappiness(
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


std::string Resident_Customizable::implimentGetType () const
{
    string funcType = "Customizable Resident: "; 
    return funcType + _hap_func->toStrBasic();
}