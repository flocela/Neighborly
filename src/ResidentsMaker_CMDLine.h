#ifndef RESIDENTSMAKER_CMDLINE_H
#define RESIDENTSMAKER_CMDLINE_H

#include <set>
#include "ResidentsMaker.h"
#include "Question_Int.h"
#include "Question_Double.h"
#include "Question_YN.h"
#include "Color.h"
#include "UI_CMDLine.h"

// Creates Residents by asking user how many resident groups they want (max is 3).
// Then for each group, asks what type of Resident the group will be composed of.
// For each type of Resident type, asks specific questions that are necessary
// to create Residents of that type.
class ResidentsMaker_CMDLine: public ResidentsMaker
{
public:
    ResidentsMaker_CMDLine () = delete;
    ResidentsMaker_CMDLine (const UI_CMDLine& cmdline);
    ~ResidentsMaker_CMDLine () = default;

    ResidentsGroupInfo makeResidents (
        const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories, //TODO should residentFactories be const also?
        int maxNumOfResidents,
        int maxNumberOfGroupsOfResidents, // Currently just using two groups!
        std::vector<BaseColor> colors,
        double maxAllowableMovement
    )
    override;

private:
    double askForHappinessGoalForGroup (std::string color);
    double askForAllowedMovementForGroup (std::string color, double maxAllowedMovement);
    int askForNumOfGroupsOfResidents (int maxNumOfResidentGroups);
    int askForNumOfResidents (int count, std::string color);
    int askForGroupResidentType (
        std::string color, 
        const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
    );
    int _num_of_resident_groups = 2;

    void initColors (std::vector<BaseColor> colors);
    std::vector<std::string>  getFactoryNames (
        const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
    );

    UI_CMDLine _ui = UI_CMDLine{};

    // map of color strings, is diminished as users use their colors.
    std::vector<BaseColor> _available_colors;
    
    double _fallback_group_happiness_goal_failure = 50.0;

    // Prompt for what is this group's color question.
    std::string _which_group_color_prompt = "What will be the color of your"
        " group? Choose a color by typing the corresponding number. _";
    
    // Prompt for what is this group's type (as in Resident_Flat or StepDown)
    std::string _which_type_prompt = "\nAll of residents in the  group will"
        " be which type of residents? Choose their resident type by typing"
        " the corresponding number.";

    // Prompts for how_many_resident_groups question.
    std::string _how_many_groups_orig_prompt =
        "\nHow many different groups of residents will there be? 1, 2, or ...? _";
    
    //Prompts for how_many_residents_in_this_group question.
    std::string _how_many_residents_orig_prompt = 
        "\nHow many residents will be in the  group? Maximum allowable number is . _";

    //Prompts for group_happiness_goal question.
    std::string _group_happiness_orig_prompt = 
        "\nWhat will be the happiness goal for all members of the  group? The"
        " number must be between 0 and 100 inclusive. _";

    /*  Prompts for the allowed movement for this group of residents.   */
    std::string _group_movement_orig_prompt  = 
        "\nThe simulator you choose may restrict the residents' movements."
        " For the  group, when the residents move, how far away can their new house be from"
        " their original house? Must be less than . _";

    // If can not get a chosen Resident type from menu, then use _fallback_menu_response.
    std::string _fallback_res_type_response = "Could not determine the"
    " resident group type, will be using ";

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