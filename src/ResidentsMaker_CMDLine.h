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
        ResidentsMaker_CMDLine () = default;
        ~ResidentsMaker_CMDLine () = default;

        // Only allows 1 to 3 groups of residents.
        std::vector<std::unique_ptr<Resident>> makeResidents (
            std::vector<ResidentsFactory*> residentsFactories,
            int maxNumOfResidents,
            std::set<BaseColor> colors // these are the colors that the residents can be.
        )
        override;
        // change colors to an iterator<BaseColor> type.
        std::vector<std::unique_ptr<Resident>> makeBaseResidents (
            std::vector<ResidentsFactory*> residentsFactories,
            int maxNumOfResidents,
            std::set<BaseColor> colors // these are the colors that the residents can be.
        )
        override;

    private:
        
        ColorInfo askForGroupColor (int groupIdx);
        double askForHappinessGoalForGroup (std::string color);
        int askForNumOfGroupsOfResidents ();
        int askForNumOfResidents (int count, std::string color);
        int askForGroupResidentType (
            std::string color, 
            std::vector<ResidentsFactory*> residentsFactories
        );
        
        Question_Int createQuestionHowManyResidentGroups ();
        Question_Int createQuestionHowManyResidents (int count, std::string color);
        Question_Double createQuestionGroupHappiness(std::string color);

        void initColors (std::set<BaseColor> colorInfos);
        void initWithBaseColors ();
        std::vector<std::string>  getFactoryNames (
            std::vector<ResidentsFactory*> residentsFactories
        );

        UI_CMDLine _ui = UI_CMDLine{};

        // map of color strings, is diminished as users use their colors.
        std::vector<BaseColor> _available_colors;
        int _num_of_groups = 2;

        // Prompt for what is this group's color question.
        std::string _which_group_color_prompt = "What will be the color of your"
            " group? Choose a color by typing the corresponding number.";
        
        // Prompt for what is this group's type (as in Resident_Flat or StepDown)
        std::string _which_type_prompt = "All of residents in the group will"
            " be which type of residents? Choose their resident type by typing"
            " the corresponding number.";

        // Prompts for how_many_resident_groups question.
        std::string _how_many_groups_orig_prompt =
            "How many different groups of residents will there be? 1, 2, or 3?  ";
        std::string _how_many_groups_type_prompt = 
            "Nope that's not a whole number.  Should be 1, 2, or 3. No decimals.  ";
        std::string _how_many_groups_range_prompt = 
            "That's either too small or too large. Should be 1, 2, or 3.  ";
        std::string _how_many_groups_failure = 
            "Could not determine how many resident types the user wanted.";
        
        //Prompts for how_many_residents_in_this_group question.
        std::string _how_many_residents_orig_prompt = 
            "How many residents will be in the first group, the group? Must be less than .  ";
        std::string _how_many_residents_type_prompt =
            "Nope that's not a whole number. No decimals.  ";
        std::string _how_many_residents_range_prompt =
            "That's too small or too large. Should be between 1 and  inclusive.  ";
        std::string _how_many_residents_failure = 
            "Could not determine how many residents in group .";

        //Prompts for group_happiness_goal question.
        std::string _group_happiness_orig_prompt = 
            "What will be the happiness goal for all members of the group? The"
            " number must be between 0 and 1 inclusive.  ";
        std::string _group_happiness_type_prompt = 
            "Nope that's not a number. Should look like 0.5 or 0.8.  ";
        std::string _group_happiness_range_prompt =
            "That's too small or too large. Should be between 0 and 1 inclusive.  ";
        std::string _group_happiness_failure = 
            "Could not determine the happiness goal for members of group.";

};

#endif