#ifndef RESIDENTSFACTORY_FALLING_H
#define RESIDENTSFACTORY_FALLING_H

#include "ResidentsFactory.h"

// Creates residents that use a falling happiness function.
// Residents' happiness is steadily decreasing as diversity increases.
class ResidentsFactory_Falling: public ResidentsFactory
{
    
public:

    // Creates Residents that use the HappinessFunc_Falling to determine their happiness.
    // Basically the residents' happiness slopes down as diversity increases.
    // The function will use the ui to get information from the user to create the 
    // happiness function.
    // Creates count number of residents. Their ids' range from firstID to firstID + count -1.
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
    // If can not get a low happiness value from the user, then use _fallback_low_happiness_value.
    double _fallback_low_happiness_value = 0.0;

    // User prompts for getting information from user.
    
    // prompt for happiness value when resident has no neighbors
    std::string _happinessWithZeroNeighborsPrompt =
        "\nFalling type residents' happiness values decrease with a constant slope as diversity"
        " increases. Diversity is defined as the number of disparate neighbors divided"
        " by the total number of neighbors. When a resident has no neighbors,"
        " diversity is undefined and the resident has a special happiness value."
        "\nFor the  group, enter the happiness value corresponding to when a resident has"
        " no neighbors.";

    // prompt for higher happiness value, when diversity is 0.0
    std::string _high_happiness_value_prompt =
        "\nDiversity is measured as the number of disparate neighbors divided by the total"
        " number of neighbors."
        "\nFor the  group, enter the higher happiness value, corresponding to a diversity of"
        " 0.0.";
    
    // prompt for lower happiness value, when diversity is 1.0.
    std::string _low_happiness_value_prompt = 
        "\nFor the  group, enter the lower happiness value, corresponding to a diversity of 1.0.";

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