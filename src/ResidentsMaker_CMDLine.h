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
        ColorInfo askForGroupColor (int groupIdx);
        double askForHappinessGoalForGroup (std::string color);
        double askForAllowedMovementForGroup (std::string color, double maxAllowedMovement);
        int askForNumOfGroupsOfResidents ();
        int askForNumOfResidents (int count, std::string color);
        int askForGroupResidentType (
            std::string color, 
            const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
        );
        int _num_of_groups = 2;
        
        Question_Int createQuestionHowManyResidentGroups ();
        Question_Int createQuestionHowManyResidents (int count, std::string color);
        Question_Double createQuestionGroupHappinessGoal(std::string color);
        Question_Double createQuestionGroupAllowableMovement(
            std::string color,
            double maxAllowedMovement
        );

        void initColors (std::vector<BaseColor> colors);
        std::vector<std::string>  getFactoryNames (
            const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
        );

        UI_CMDLine _ui = UI_CMDLine{};

        // map of color strings, is diminished as users use their colors.
        std::vector<BaseColor> _available_colors;
        

        // Prompt for what is this group's color question.
        std::string _which_group_color_prompt = "What will be the color of your"
            " group? Choose a color by typing the corresponding number. _";
        
        // Prompt for what is this group's type (as in Resident_Flat or StepDown)
        std::string _which_type_prompt = "\nAll of residents in the group will"
            " be which type of residents? Choose their resident type by typing"
            " the corresponding number.";

        // Prompts for how_many_resident_groups question.
        std::string _how_many_groups_orig_prompt =
            "How many different groups of residents will there be? 1, 2, or 3? _";
        std::string _how_many_groups_type_prompt = 
            "Nope that's not a whole number.  Should be 1, 2, or 3. No decimals. _";
        std::string _how_many_groups_range_prompt = 
            "That's either too small or too large. Should be 1, 2, or 3. _";
        std::string _how_many_groups_failure = 
            "Could not determine how many resident types the user wanted.";
        
        //Prompts for how_many_residents_in_this_group question.
        std::string _how_many_residents_orig_prompt = 
            "\nHow many residents will be in the group? Maximum allowable number is . _";
        std::string _how_many_residents_type_prompt =
            "Nope that's not a whole number. No decimals. _";
        std::string _how_many_residents_range_prompt =
            "That's too small or too large. Should be between 1 and  inclusive. _";
        std::string _how_many_residents_failure = 
            "Could not determine how many residents in group .";

        //Prompts for group_happiness_goal question.
        std::string _group_happiness_orig_prompt = 
            "\nWhat will be the happiness goal for all members of the group? The"
            " number must be between 0 and 100 inclusive. _";
        std::string _group_happiness_type_prompt = 
            "Nope that's not a number. Should look like 0.5 or 0.8. _";
        std::string _group_happiness_range_prompt =
            "That's too small or too large. Should be between 0 and 100 inclusive. _";
        std::string _group_happiness_failure = 
            "Could not determine the happiness goal for members of group.";

        /*  Prompts for the allowed movement for this group of residents.   */
        std::string _group_movement_orig_prompt  = 
            "\nThe simulator you choose may restrict the residents' movements."
            " If so, when the residents move, how far away can their new house be from"
            " their original house? Must be less than . _";
        std::string _group_movement_type_prompt  = 
            "Nope, that's not a number, i.e. 0.2 or 13.0. _";
        std::string _group_movement_range_prompt = 
            "That number must be between 0 and . _";
        std::string _group_movement_failure =
            "Can not get information needed to determine the allowed movement for these"
            " residents from the user.";

};

#endif