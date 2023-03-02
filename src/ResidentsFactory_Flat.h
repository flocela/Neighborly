#ifndef RESIDENTFACTORY_FLAT_H
#define RESIDENTFACTORY_FLAT_H

#include "ResidentsFactory.h"

class ResidentsFactory_Flat: public ResidentsFactory
{
public:
    
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

    // if can not get happiness value from user, then use _fallback_happiness_value
    double _fallback_happiness_value = 50.0;

    // User prompts for getting information from user.
    
    // prompt for happiness value when resident has no neighbors 
    std::string _happinessWithZeroNeighborsPrompt  = 
        "\nFlat type residents have a constant happiness for all diversities. Diversity is defined"
        " as the number of disparate neighbors divided by total number of neighbors. When a"
        " resident has no neighbors, diversity is undefined and the resident has a special"
        " happiness value."
        "\nFor the  group, enter the happiness value corresponding to having no neighbors. _";

                                        
    // prompt for happiness value, which is constant for all diversities.
    std::string _happinessValueOrigPrompt  = 
        "\nFlat type residents have a constant happiness value."
        "\nFor the  group, enter the happiness value. The value must be between"
        " 0.0 and 100.0 inclusive. _";

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
    
    // Often have to place the group color in "For the ____ group". This method returns the 
    // character index where the group color would go. It's a very specialized method, in that
    // it finds the specific words "the  group" and returns character after "the" and space.
    int charLocationForColor (std::string str) const;
};

#endif