#include "ResidentTemplate_UsingFunction.h"

using namespace std;

ResidentTemplate_UsingFunction::ResidentTemplate_UsingFunction (
    double allowedMovementDistance,
    double happinessGoal,
    std::string functionType
): ResidentTemplate(allowedMovementDistance, happinessGoal),
   _function_type{functionType}
{}

std::string ResidentTemplate_UsingFunction::getType () const
{
    return _function_type;
}
