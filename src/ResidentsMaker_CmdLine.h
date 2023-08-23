#ifndef RESIDENTSMAKER_CMDLINE__H
#define RESIDENTSMAKER_CMDLINE__H

#include "ResidentsMaker.h"
#include "UI_CmdLine.h"

// For each group, asks user what type of resident the group will be composed of.
// For each type of Resident type, asks specific questions that are necessary
// to create Residents of that type.
class ResidentsMaker_CmdLine: public ResidentsMaker
{
    
public:

    ResidentsGroupInfo makeResidents (
        const UI& ui,
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories,
        int maxNumberOfGroupsOfResidents,
        std::vector<BaseColor> colors,
        double maxAllowableMovement
    )override;

private:

    int _num_of_resident_groups = 2;

    std::vector<BaseColor> _available_colors{};
    
    double _fallback_group_happiness_goal_failure = 50.0;
    
    // prompt for this group's type (as in Resident_Flat or StepDown...)
    std::string _which_type_prompt = "\nFor the  group, what will be the residents' type?"
        " Choose the residents' type by typing the corresponding number.";
    
    // prompt for the number of resdidents in this group
    std::string _how_many_residents_orig_prompt = 
        "\nHow many residents will be in the  group? Maximum allowable number is .";

    // prompt for the happiness goal for this group
    std::string _happiness_goal_orig_prompt = 
        "\nFor the  group, what will be the happiness goal for all members of the group? The"
        " number must be between 0 and 100 inclusive.";

    // prompt for the allowed movement of each resident in the group
    std::string _group_movement_orig_prompt  = 
        "\nThe simulator you choose may restrict the residents' movements."
        " For the  group, when the residents move, how far away can their new house be from"
        " their original house? Must be less than or equal to .";

    // If can not get a resident type from the menu, then use _fallback_menu_response.
    std::string _fallback_res_type_response = "Could not determine the"
        " resident group type, will be using .";

    // Will return at least 1.
    int askForNumOfResidents (const UI& ui, int maxNumOfResidents, std::string color);

    int askForGroupResidentType (
        const UI& ui, 
        std::string color, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories);

    double askForAllowedMovementForGroup (
        const UI& ui,
        std::string color,
        double maxAllowedMovement);

    double askForHappinessGoalForGroup (const UI& ui, std::string color);
    
    std::vector<std::string>  getFactoryNames (
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories
    );

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;

    // Often have to place the group color in the sentence fragment "For the ____ group". This
    // method returns the character index where the group color would go. It's a very specialized
    // method, in that it finds the specific words "the  group" and returns the character after
    // "the" and space.
    int charLocationForColor (std::string str);
};

#endif