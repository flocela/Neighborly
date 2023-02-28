#ifndef RESIDENTFACTORY_STEPDOWN_H
#define RESIDENTFACTORY_STEPDOWN_H

#include "ResidentsFactory.h"

// Creates residents that use a step down happiness function.
// Residents' happiness is two tiered. The higher happiness value is found
// at zero diversity through the drop-down diversity, and the lower happiness
// value is found after the drop-down diversity through to 1.0 diversity.
class ResidentsFactory_StepDown: public ResidentsFactory
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

    // if can not get a low happiness value from user, then use _fall_back_low_happiness_value
    double _fallback_low_happiness_value = 0.0;

    // if can not get a happiness drop-down location from user, then use _fall_back_drop_location
    double _fallback_drop_location = 0.5;

    // User prompts for getting information from user.

    // prompt for happiness value when resident has no neighbors
    std::string _happinessWithZeroNeighborsPrompt  = 
        "\nStepDown type residents' happiness value is two tiered. The higher happiness"
        " value starts at zero and runs through the drop-down diversity. The lower"
        " happiness value starts after the drop-down diversity through to a diversity of 1.0."
        " Diversity is defined as the number of disparate neighbors divided"
        " by the total number of neighbors. When a resident has no neighbors,"
        " diversity is undefined and the resident has a special happiness value."
        "\nFor the  group, enter the happiness value corresponding to when a resident has"
        " no neighbors. _";

    // prompt for high happiness value, from diversity equal to 0.0 to the drop-down
    // diversity (inclusive).
    std::string _high_happiness_value_prompt  = 
        "\nDiversity is measured as the number of disparate neighbors divided by the total"
        " number of neighbors."
        "\nFor the  group, enter the higher happiness value, corresponding to a diversity of"
        " 0.0 through to the drop-down diversity. _";
    
    // prompt for the low happiness value, from after the drop-down diversity to 1.0.
    std::string _low_happiness_value_prompt  = 
        "\nFor the  group, enter the lower happiness value found after the drop-down"
        " diversity. _";

    // prompts for the location where the happiness drop happens along the diverstiy axis.
    std::string _dropLocationOrigPrompt  = 
        "\nFor the  group, enter the point at which the happiness value drops, the drop-down"
        " diversity. This will be the diversity value where the happiness drops from the higher"
        " value to the lower value. The diversity value must be between 0.0 and 1.0"
        " inclusive. _";
    
    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
    
    // Often have to place the group color in "For the ____ group". This method returns the 
    // character index where the group color would go. It's a very specialized method, in that
    // it finds the specific words "the  group" and returns character after "the" and space.
    int charLocationForColor (std::string str) const ;
};


#endif