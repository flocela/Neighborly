#ifndef RESIDENTFACTORY_STEPUP_H
#define RESIDENTFACTORY_STEPUP_H

#include "ResidentsFactory.h"
#include "Question_Int.h"
#include "Question_Double.h"
#include "Question_YN.h"

// Creates residents that use a step up happiness function.
// Residents' happiness is two tiered. The lower happiness value is found
// at zero diversity through the step-up diversity, and the higher happiness
// value is found after the step-up diversity through 1.0 diversity.
class ResidentsFactory_StepUp: public ResidentsFactory
{
public:

    std::vector<std::unique_ptr<Resident>> createResidents(
        const UI& ui,
        int firstID, 
        int count, 
        double happinessGoal,
        double allowedMovement,
        int groupNumber,
        BaseColor baseColor
    ) const override;

    std::string toString () override;
    std::string residentType () const override;
    
private:

    // if can not get a high happiness value from user, then use _fall_back_high_happiness_value
    double _fallback_high_happiness_value = 100.0;

    // if can not get a happiness drop location from user, then use _fall_back_drop_location
    double _fallback_drop_location = 0.5;

    // User prompts for getting information from user.

    // prompt for happiness value when resident has no neighbors
    std::string _happiness_with_zero_neighbors_prompt  = 
        "\nStepUp type residents happiness values are two tiered. The lower happiness"
        " value starts at zero and runs through the drop-down diversity. The higher"
        " happiness value starts after the step-up diversity through a diversity of 1.0."
        " Diversity is defined as the number of disparate neighbors divided"
        " by the total number of neighbors. When a resident has no neighbors,"
        " diversity is undefined and the resident has a special happiness value."
        "\nFor the  residents, enter the happiness value corresponding to when a resident has"
        " no neighbors. _";

    // prompt for low happiness value, from diversity equal to 0.0 to step down
    // diversity (inclusive).
    std::string _low_happiness_value_prompt  = 
        "\nDiversity is measured as the number of disparate neighbors divided by the total"
        " number of neighbors."
        "\nFor the  residents, enter the lower happiness value, corresponding to a diverstiy of"
        " 0.0 through to the step-up diversity. _";
    
    // prompt for the high happiness value, from after the drop down diversity to 1.0.
    std::string _high_happiness_value_prompt  = 
        "\nFor the  residents, enter the lower happiness value found after the step-up"
        " diversity. _";

    // prompts for the location where the happiness drop happens along the diversity axis.
    std::string _stepup_location_prompt  = 
        "\nFor the  residents, enter the point at which the happiness value jumps, the step-up"
        " diversity. This will be the diversity value where the happiness jumps from the lower"
        " value to the higher value. The diversity value must be between 0.0 and 1.0"
        " inclusive. _";
    
    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
    
    // Often have to place the group color in "For the ____ residents, enter". This method returns the 
    // character index where the group color would go. It's a very specialized method, in that
    // it finds the specific words "For the  residents, enter" and returns character after "the" and space.
    int charLocationForColor (std::string str) const;
};


#endif