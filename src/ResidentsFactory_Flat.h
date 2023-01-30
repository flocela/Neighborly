#ifndef RESIDENTFACTORY_FLAT_H
#define RESIDENTFACTORY_FLAT_H

#include "ResidentsFactory.h"
#include "Question_Int.h"
#include "Question_Double.h"
#include "Question_YN.h"

class ResidentsFactory_Flat: public ResidentsFactory
{
public:
    ResidentsFactory_Flat () = default;
    ResidentsFactory_Flat (const ResidentsFactory_Flat& obj) = default;
    ResidentsFactory_Flat (ResidentsFactory_Flat&& obj) noexcept = default;
    ResidentsFactory_Flat& operator= (const ResidentsFactory_Flat& obj) = default;
    ResidentsFactory_Flat& operator= (ResidentsFactory_Flat&& obj) noexcept = default;
    ~ResidentsFactory_Flat() = default;
    
    std::vector<std::unique_ptr<Resident>> createResidents(
        UI&    ui,
        int    firstID, 
        int    count, 
        double happinessGoal,
        double allowedMovement,
        int groupNumber,
        BaseColor basecolor
    ) override;
    std::string toString () override;
    std::string residentType () override;

private:

    std::string _happinessWithZeroNeighborsPrompt  = 
    "\nFlat type residents have a constant happiness for all diversities (disparate neighbors"
    "/total number of neighbors). When a Flat type resident has no neighbors, a special "
    " happiness value is used, the 'zero-neighbors happiness value'.\nEnter the happiness value"
    " used when the resident has no neighbors, zero-neigbors happiness value. _";

    std::string _happinessWithZeroNeighborsTypePrompt  = 
    "Nope, that's not a number, i.e. 0.2 or 13.0. _";

    std::string _happinessWithZeroNeighborsRangePrompt = 
    "That number is too small or too large. Should be between 0.0 and 100.0"
    " inclusive. _";

    std::string _happiness_with_zero_neighbors_failure =
    "Could not get happiness value when resident has zero neighbors, using .";

    // if can not get happiness value from user, then use _fallback_happiness_value
    double _fallback_happiness_value = 50.0;                                     
    /*  Prompts for the Happiness Value when the Diversity is zero for 
        this group of residents.    */
    std::string _happinessValueOrigPrompt  = 
        "\n\"Flat Residents\" have a constant happiness value"
        " regardless of the diversity of their neighbors. Enter the happiness"
        " value for these flat residents.  The happiness value"
        " must be between 0.0 and 100.0 inclusive. _";
    std::string _happinessValueTypePrompt  = 
        "Nope, that's not a number, i.e. 0.2 or 15.0. _";
    std::string _happinessValueRangePrompt = 
        "That number is too small or too large. Should be between 0.0 and 100.0"
        " inclusive. _";
    std::string _happinessValueFailure = 
        "Can not get information needed to determine the happiness value for"
        " these residents. Will use .";

    int askUserForInt (UI& ui, Question_Int question);
    double askUserForDouble (UI& ui, Question_Double question);

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
};

#endif