#ifndef RESIDENTFACTORY_FLAT__H
#define RESIDENTFACTORY_FLAT__H

#include "ResidentsFactory.h"

class ResidentsFactory_Flat: public ResidentsFactory
{
    
public:
    
    // Creates Residents that use the HappinessFunc_Falling to determine their happiness.
    // Basically the residents' happiness will be constant.
    // The function will use @ui to get information from the user to create the 
    // happiness function.
    // Creates @count number of residents. Their ids' range from @firstID to @firstID + @count -1.
    std::vector<std::unique_ptr<Resident>> createResidents(
        const UI& ui,
        int firstID, 
        int count, 
        double happinessGoal,
        double allowedMovement,
        int groupNumber,
        BaseColor basecolor
    ) const override;

    std::string residentType () const override;
    
    std::string toString () override;

private:

    // If can not get happiness value from user, then use _fallback_happiness_value
    double _fallback_happiness_value = 50.0;

    // User prompts for getting information from user.
    
    // prompt for happiness value when resident has no neighbors 
    std::string _happinessWithZeroNeighborsPrompt  = 
        "\nFlat type residents have a constant happiness for all diversities. Diversity is defined"
        " as the number of disparate neighbors divided by total number of neighbors. When a"
        " resident has no neighbors, diversity is undefined and the resident has a special"
        " happiness value."
        "\nFor the  group, enter the happiness value corresponding to having no neighbors.";

                                        
    // prompt for happiness value, which is constant for all diversities.
    std::string _happinessValueOrigPrompt  = 
        "\nFlat type residents have a constant happiness value."
        "\nFor the  group, enter the happiness value. The value must be between"
        " 0.0 and 100.0 inclusive.";

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