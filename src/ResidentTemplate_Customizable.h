#ifndef RESIDENT_TEMPLATE_CUSTOMIZABLE__H
#define RESIDENT_TEMPLATE_CUSTOMIZABLE__H

#include <memory>
#include "HappinessFunc.h"
#include "Resident.h"

class ResidentTemplate_Customizable : public ResidentTemplate
{

protected:

    ResidentTemplate_Customizable (const ResidentTemplate_Customizable& obj) = default;
    ResidentTemplate_Customizable (ResidentTemplate_Customizable&& obj) noexcept = default;
    ResidentTemplate_Customizable& operator= (const ResidentTemplate_Customizable& obj) = default;
    ResidentTemplate_Customizable&
        operator= (ResidentTemplate_Customizable&& obj) noexcept = default;

public:

    ResidentTemplate_Customizable (
        double allowedMovementDistance,
        double happinessGoal,
        std::string functionType);
    ResidentTemplate_Customizable () = delete;
    ~ResidentTemplate_Customizable () noexcept = default;

    std::string getType () const;

private:

    std::string _function_type;

};

#endif