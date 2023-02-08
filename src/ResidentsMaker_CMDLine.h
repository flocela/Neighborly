#ifndef RESIDENTSMAKER_CMDLINE_H
#define RESIDENTSMAKER_CMDLINE_H

#include "Color.h"
#include "ResidentsMaker.h"
#include "UI_CMDLine.h"

// Creates Residents by asking user how many resident groups they want.
// Then for each group, asks what type of resident the group will be composed of.
// For each type of Resident type, asks specific questions that are necessary
// to create Residents of that type.
class ResidentsMaker_CMDLine: public ResidentsMaker
{
public:
    
    ResidentsMaker_CMDLine () = delete;
    ResidentsMaker_CMDLine (const UI_CMDLine& cmdline);
    ResidentsMaker_CMDLine (const ResidentsMaker_CMDLine& orig) = default;
    ResidentsMaker_CMDLine& operator= (const ResidentsMaker_CMDLine& orig) = default;
    ResidentsMaker_CMDLine (ResidentsMaker_CMDLine&& orig) = default;
    ResidentsMaker_CMDLine& operator= (ResidentsMaker_CMDLine&& orig) = default;

    ~ResidentsMaker_CMDLine () = default;

    ResidentsGroupInfo makeResidents (
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories, 
        int maxNumOfResidents,
        int maxNumberOfGroupsOfResidents,
        std::vector<BaseColor> colors,
        double maxAllowableMovement
    )override;

private:

    int _num_of_resident_groups = 2;

    UI_CMDLine _ui = UI_CMDLine{};

    std::vector<BaseColor> _available_colors{};
    
    double _fallback_group_happiness_goal_failure = 50.0;
    
    // prompt for this group's type (as in Resident_Flat or StepDown...)
    std::string _which_type_prompt = "\nWhat will be the type for the residents in the  group?"
        " Choose the resident type by typing the corresponding number.";

    // prompt for the number of resident groups.
    std::string _how_many_groups_orig_prompt =
        "\nHow many different groups of residents will there be? 1, 2, or ...? _";
    
    // prompt for the number of resdidents in this group.
    std::string _how_many_residents_orig_prompt = 
        "\nHow many residents will be in the  group? Maximum allowable number is . _";

    // prompt for the happiness for this group
    std::string _happiness_goal_orig_prompt = 
        "\nWhat will be the happiness goal for all members of the  group? The"
        " number must be between 0 and 100 inclusive. _";

    // prompt for the allowed movement of each resident in the group.
    std::string _group_movement_orig_prompt  = 
        "\nThe simulator you choose may restrict the residents' movements."
        " For the  group, when the residents move, how far away can their new house be from"
        " their original house? Must be less than . _";

    // if can not get a resident type from the user using the menu, then
    // use _fallback_menu_response.
    std::string _fallback_res_type_response = "Could not determine the"
        " resident group type, will be using ";
    
    void initColors (std::vector<BaseColor> colors);

    int askForNumOfGroupsOfResidents (int maxNumOfResidentGroups);
    int askForNumOfResidents (int count, std::string color);
    int askForGroupResidentType (
        std::string color, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories
    );
    double askForAllowedMovementForGroup (std::string color, double maxAllowedMovement);
    double askForHappinessGoalForGroup (std::string color);
    
    std::vector<std::string>  getFactoryNames (
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentsFactories
    );

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;

    // Often have to place the group color in "What will be xxx for the xxx group". This method returns the 
    // character index where the group color would go. It's a very specialized method, in that
    // it finds the specific words "the  group" and returns character after "the" and space.
    int charLocationForColor (std::string str);
};

#endif