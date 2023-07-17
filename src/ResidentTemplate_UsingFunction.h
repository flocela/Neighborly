#ifndef RESIDENT_TEMPLATE_USING_FUNCTION_H
#define RESIDENT_TEMPLATE_USING_FUNCTION_H

#include <memory>
#include "Resident.h"
#include "HappinessFunc.h"

// Uses the HappinessFunc given in the constructor to determine the resident happiness.
class ResidentTemplate_UsingFunction : public ResidentTemplate
{
protected:
    ResidentTemplate_UsingFunction (const ResidentTemplate_UsingFunction& obj) = default;
    ResidentTemplate_UsingFunction (ResidentTemplate_UsingFunction&& obj) noexcept = default;
    ResidentTemplate_UsingFunction& 
        operator= (const ResidentTemplate_UsingFunction& obj) = default;
    ResidentTemplate_UsingFunction&
        operator= (ResidentTemplate_UsingFunction&& obj) noexcept = default;

public:
    ResidentTemplate_UsingFunction (
        double allowedMovementDistance,
        double happinessGoal,
        std::string functionType);
    ResidentTemplate_UsingFunction () = delete;
    ~ResidentTemplate_UsingFunction () noexcept = default;

    std::string getType () const;

private:
    std::string _function_type;

};

#endif