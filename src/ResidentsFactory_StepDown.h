#ifndef RESIDENTFACTORY_STEPDOWN_H
#define RESIDENTFACTORY_STEPDOWN_H

#include "ResidentsFactory.h"
#include "Question_Int.h"
#include "Question_Double.h"
#include "Question_YN.h"

class ResidentsFactory_StepDown: public ResidentsFactory
{
    public:
        ResidentsFactory_StepDown () = default;
        ResidentsFactory_StepDown (const ResidentsFactory_StepDown& obj) = default;
        ResidentsFactory_StepDown (ResidentsFactory_StepDown&& obj) noexcept = default;
        ResidentsFactory_StepDown& operator= (const ResidentsFactory_StepDown& obj) = default;
        ResidentsFactory_StepDown& operator= (ResidentsFactory_StepDown&& obj) noexcept = default;
        ~ResidentsFactory_StepDown() = default;

        std::vector<std::unique_ptr<Resident>> createResidents(
            UI& ui,
            int firstID, 
            int count, 
            double happinessGoal,
            double allowedMovement,
            int groupNumber,
            BaseColor baseColor
        ) override;
        std::string toString () override;
        std::string residentType () override;
        
    private:

        /*  Prompts for the Happiness Value when the Diversity is zero for 
            this group of residents.    */
        std::string _happinessWithZeroNeighborsPrompt  = 
            "\nStepDown residents measure diversity as the number of disparate"
            " neighbors divided by total number of neighbors. When StepDown"
            " residents have no neighbors their happiness has a special value named"
            " zero-neighbors. When StepDown Residents have neighbors, StepDown Residents have"
            " one of two happiness values. They have a high happiness value for diversities"
            " starting close to zero and up to and including a given diversity named diversity-drop."
            " Then they have a lower happiness value after the"
            " diversity-drop. Enter the happiness value when the residents have no neighbors. _";
        std::string _happinessWithZeroNeighborsTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 13.0. _";
        std::string _happinessWithZeroNeighborsRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and 100.0"
            " inclusive. _";

        /*  Prompts for the higher Happiness Value when the Diversity is close to zero and 
            up to and including the diversity-drop for this group of residents.    */
        std::string _high_happiness_value_prompt  = 
            "\nEnter the higher happiness value found close to"
            " diversity 0.0 and continuing onto the diversity-drop. The happiness value"
            " must be between 0.0 and 100.0"
            " inclusive. _";
        std::string _high_happiness_value_type_prompt  = 
            "Nope, that's not a number, i.e. 0.2 or 13.0. _";
        std::string _high_happiness_value_range_prompt = 
            "That number is too small or too large. Should be between 0.0 and 100.0"
            " inclusive. _";
        
        /*  Prompts for the HappinessValue for diversity after the diversity-drop for
            this group of residents.    */
        std::string _low_happiness_value_prompt  = 
            "\nEnter the lower happiness value found after the diversity-drop."
            " The happiness value must be between 0.0 and  inclusive. _";
        std::string _low_happiness_value_type_prompt  = 
            "Nope, that's not a number, i.e. 0.2 or 55.0. _";
        std::string _low_happiness_value_range_prompt = 
            "That number is too small or too large. Should be between 0.0 and"
            "  inclusive. _";

        /*  Prompts for the location where the happiness drop happens along the
            diverstity axis.   */
        std::string _dropLocationOrigPrompt  = 
            "Enter the point at which the happiness value drops, the drop-diversity. This will be"
            " the diversity value where the happiness drops from the higher value"
            " to the lower value. The diversity value must be between 0.0 and 100.0"
            " inclusive. _";
        std::string _dropLocationTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 90.0. _";
        std::string _dropLocationRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and 100.0"
            " inclusive. _";   

        int askUserForInt (UI& ui,
                           Question_Int question, 
                           std::string failureString);
        double askUserForDouble (UI& ui,
                                 Question_Double question, 
                                 std::string failureString);
};


#endif