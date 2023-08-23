#include "ResidentTemplate_Customizable.h"

using namespace std;

ResidentTemplate_Customizable::ResidentTemplate_Customizable (
    double allowedMovementDistance,
    double happinessGoal,
    std::string functionType
):
    ResidentTemplate(allowedMovementDistance, happinessGoal),
    _function_type{functionType}
{}

std::string ResidentTemplate_Customizable::getType () const
{
    return _function_type;
}
