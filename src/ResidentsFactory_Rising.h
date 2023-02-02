#ifndef RESIDENTSFACTORY_RISING_H
#define RESIDENTSFACTORY_RISING_H

#include "ResidentsFactory.h"

// Creates residents that use a rising happiness function.
// Residents' happiness is steadily increaing as diversity increases.
class ResidentsFactory_Rising: public ResidentsFactory
{
public:
    std::vector<std::unique_ptr<Resident>> createResidents(
        UI& ui,
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

    // if can not get a high happiness value from the user, then use _fallback_high_happiness_value.
    double _fallback_high_happiness_value = 100.0;

    // User prompts for getting information from user.
    
    // prompt for happiness value when resident has no neighbors
    std::string _happinessWithZeroNeighborsPrompt =
        "\nRising type residents' happiness values increase with a constant slope as diversity"
        " increases. Diversity is defined as the number of disparate neighbors divided"
        " by the total number of neighbors. When a resident has no neighbors,"
        " diversity is undefined and the resident has a special happiness value."
        "\nFor  residents, enter the happiness value corresponding to when a resident has"
        " no neighbors. _";

    // prompt for low happiness value, when diversity is at 0.0.
    std::string _low_happiness_value_prompt =
        "Diversity is measured as the number of disparate neighbors divided by the total"
        " number of neighbors."
        "\nFor the  residents, enter the lower happiness value, corresponding"
        " to a diversity of 0.0. _";

    // prompt for high happiness value, when diversity is 1.0
    std::string _high_happiness_value_prompt =
        "\nFor the  residents, enter the higher happiness value, corresponding to a"
        " diversity of 1.0. _";

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;

    // Often have to place the group color in "For the ____ residents, enter". This method returns the 
    // character index where the group color would go. It's a very specialized method, in that
    // it finds the specific words "For the  residents, enter" and returns character after "the" and space.
    int charLocationForColor (std::string str) const ;
};

#endif