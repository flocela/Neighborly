#ifndef RESIDENTFACTORY_STEPDOWN_H
#define RESIDENTFACTORY_STEPDOWN_H

#include "ResidentsFactory.h"
#include "Question_Int.h"
#include "Question_Double.h"

class ResidentsFactory_StepDown: public ResidentsFactory
{
    public:
        ResidentsFactory_StepDown ();
        ResidentsFactory_StepDown (const ResidentsFactory_StepDown& obj) = default;
        ResidentsFactory_StepDown (ResidentsFactory_StepDown&& obj) noexcept = default;
        ResidentsFactory_StepDown& operator= (const ResidentsFactory_StepDown& obj) = default;
        ResidentsFactory_StepDown& operator= (ResidentsFactory_StepDown&& obj) noexcept = default;
        ~ResidentsFactory_StepDown() = default;

        std::vector<std::unique_ptr<Resident>> createResidents (
            UI& ui,
            int firstID,
            int maxCount, 
            Color color
        ) override;
        std::vector<std::unique_ptr<Resident>> createResidents(
            UI& ui,
            int firstID, 
            int maxCount, 
            double happinessGoal, 
            Color color
        ) override;
        std::vector<std::unique_ptr<Resident>> createBaseResidents(
            UI& ui,
            int firstID, 
            int maxCount, 
            double happinessGoal, 
            Color color
        ) override;
        std::string toString () override;
    private:
        /*  Prompts for how many residents in this group. Prompts aren't complete.
            Need to have the maximum number of residents allowed.   */
        std::string _howManyOrigPrompt  = 
            "How many \"StepDown Residents\" should there be? Must be less than ";
        std::string _howManyTypePrompt  =
            "Nope, that's not a whole number. Should be a number without any"
            " decimals.";
        std::string _howManyRangePrompt = 
            "That number is too small or too large. Should be between 1 and ";

        /*  Prompts for the happiness goal for this group of residents. */
        std::string _happinessGoalOrigPrompt  = 
            "What should the happiness goal of these residents?  Must be a number"
            " between 0 and 1 inclusively.";
        std::string _happinessGoalTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 1.0";
        std::string _happinessGoalRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and 1.0"
            " inclusive.";
                                        
        /*  Prompts for the allowed movement for this group of residents.   */
        std::string _movmentOrigPrompt  = 
            "When these residents move, how far away can their new house be from"
            "their  original house? Must be a positive number.";
        std::string _movementTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 13.0";
        std::string _movemenRangePrompt = 
            "That number is not positive. It must be 0.0 or greater.";
                                        
        /*  Prompts for the Happiness Value when the Diversity is zero for 
            this group of residents.    */
        std::string _happinessAtZeroOrigPrompt  = 
            "\"StepDown Residents\" start at a high happiness value at zero"
            " diversity, then drop to a lower happiness value after a certain"
            " diversity. Enter the starting, higher happiness value found at"
            " diversity 0.0. The happiness value must be between 0.0 and 1.0"
            " inclusive.";
        std::string _happinessAtZeroTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 1.0";
        std::string _happinessAtZeroRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and 1.0"
            " inclusive.";
        
        /*  Prompts for the HappinessValue when the Diversity is one for
            this group of residents.    */
        std::string _happinessAtOneOrigPrompt  = 
            "Enter the later, lower happiness value found at diversity 0.0."
            " The happiness value must be between 0.0 and 1.0 inclusive.";
        std::string _happinessAtOneTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 1.0";
        std::string _happinessAtOneRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and"
            " 1.0 inclusive.";

        /*  Prompts for the location where the happiness drop happens along the
            diverstity axis.   */
        std::string _dropLocationOrigPrompt  = 
            "Enter the point at which the happiness value drops. This will be"
            " the diversity value where the happiness drops from the higher value"
            " to the lower value. The diversity value must be between 0.0 and 1.0"
            " inclusive.";
        std::string _dropLocationTypePrompt  = 
            "Nope, that's not a number, i.e. 0.2 or 1.0";
        std::string _dropLocationRangePrompt = 
            "That number is too small or too large. Should be between 0.0 and 1.0"
            " inclusive.";   

        int askUserForInt (UI& ui,
                           Question_Int question, 
                           std::string failureString);
        double askUserForDouble (UI& ui,
                                 Question_Double question, 
                                 std::string failureString);
};


#endif