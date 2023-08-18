#ifndef RESIDENTFACTORY_STEPUP_H
#define RESIDENTFACTORY_STEPUP_H

#include "Question_Double.h"
#include "Question_Int.h"
#include "ResidentsFactory.h"

// Creates residents that use a step up happiness function.
// Residents' happiness is two tiered. The lower happiness value is found
// at zero diversity through the step-up diversity, and the higher happiness
// value is found after the step-up diversity through to 1.0 diversity.
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

    std::string residentType () const override;

    std::string toString () override;
    
private:

    // If can not get a high happiness value from user, then use _fall_back_high_happiness_value.
    double _fallback_high_happiness_value = 100.0;

    // If can not get a happiness step-up location from user, then use _fall_back_step_location.
    double _fallback_step_location = 0.5;

    // User prompts for getting information from user.

    // prompt for happiness value when resident has no neighbors
    std::string _happiness_with_zero_neighbors_prompt  = 
        "\nStepUp type residents' happiness value is two tiered. The lower happiness"
        " value starts at zero and runs through the step-up diversity. The higher"
        " happiness value starts after the step-up diversity through to 1.0."
        " Diversity is defined as the number of disparate neighbors divided"
        " by the total number of neighbors.\nWhen a resident has no neighbors,"
        " diversity is undefined and the resident has a special happiness value."
        "\nFor the  group, enter the happiness value corresponding to when a resident has"
        " no neighbors.";

    // prompt for low happiness value, from diversity equal to 0.0 to step up
    // diversity (inclusive)
    std::string _low_happiness_value_prompt  = 
        "\nDiversity is measured as the number of disparate neighbors divided by the total"
        " number of neighbors."
        "\nFor the  group, enter the lower happiness value, corresponding to a diversity of"
        " 0.0 to the step-up diversity (inclusive).";
    
    // prompt for the high happiness value, from after the step up diversity to 1.0
    std::string _high_happiness_value_prompt  = 
        "\nFor the  group, enter the lower happiness value found after the step-up"
        " diversity.";

    // prompts for the location where the happiness drop happens along the diversity axis
    std::string _stepup_location_prompt  = 
        "\nFor the  group, enter the point at which the happiness value jumps, the step-up"
        " diversity. This will be the diversity value where the happiness jumps from the lower"
        " value to the higher value. The diversity value must be between 0.0 and 1.0"
        " inclusive.";
    
    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
    
    // Often have to place the group color in the sentence fragment "For the ____ group". This
    // method returns the character index where the group color would go. It's a very specialized
    // method, in that it finds the specific words "the  group" and returns the character after
    // "the" and space.
    int charLocationForColor (std::string str) const;
};


#endif