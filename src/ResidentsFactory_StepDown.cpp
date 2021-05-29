#include "ResidentsFactory_StepDown.h"
#include <limits>
#include "Resident_StepDown.h"

std::string ResidentsFactory_StepDown::toString ()
{
    return "Step Down Residents Factory";
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_StepDown::createResidents (
    UI& ui, 
    int firstID,
    int maxCount,
    Color color
)
{   
    Question_Double qHappinessGoal{
        1,
        0.0,
        1.0,
        _happinessGoalOrigPrompt,
        _happinessGoalTypePrompt,
        _happinessGoalRangePrompt
    };

    double happinessGoal = askUserForDouble(
        ui,
        qHappinessGoal,
        "Can not get information needed to determine the happiness goal for"
        " these residents from the user."
    );
    
    return createResidents(ui, firstID, maxCount, happinessGoal, color);
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_StepDown::createBaseResidents (
    UI& ui,
    int firstID, 
    int maxCount,
    double happinessGoal,
    Color color
)
{   
    (void) ui;
    (void) maxCount;
    int howMany = 13;
    double movement = 2.0;
    double happinessAtZero = 1.0;
    double happinessAtOne = 0.5;
    double locationOfDrop = 0.5;

    std::vector<std::unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<howMany; ++ii)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            firstID+ii,
            color,
            movement,
            happinessGoal,
            happinessAtZero,
            happinessAtOne,
            locationOfDrop
        ));
    }
    return residents;
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_StepDown::createResidents (
    UI& ui,
    int firstID, 
    int maxCount,
    double happinessGoal,
    Color color
)
{   
    Question_Int qHowMany{
        0,
        1,
        maxCount,
        _howManyOrigPrompt + std::to_string(maxCount) + ".",
        _howManyTypePrompt,
        _howManyRangePrompt + std::to_string(maxCount) + "."
    };

    Question_Double qMovement{
        2,
        0.0,
        std::numeric_limits<double>::max(),
        _movmentOrigPrompt,
        _movementTypePrompt,
        _movemenRangePrompt
    };

    Question_Double qHappinessAtZero{
        3,
        0.0,
        1.0,
        _happinessAtZeroOrigPrompt,
        _happinessAtZeroTypePrompt,
        _happinessAtZeroRangePrompt
    };

    Question_Double qHappinessAtOne{
        4,
        0.0,
        1.0,
        _happinessAtOneOrigPrompt,
        _happinessAtOneTypePrompt,
        _happinessAtOneRangePrompt};

    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        _dropLocationOrigPrompt,
        _dropLocationTypePrompt,
        _dropLocationRangePrompt
    };
    
    int howMany = askUserForInt(
        ui,
        qHowMany, 
        "Can not get information needed to determine number of residents from the"
        " user."
    );
    
    double movement = askUserForDouble(
        ui,
        qMovement,
        "Can not get information needed to determine the allowed movement for"
        " these residents from the user."
    );

    double happinessAtZero = askUserForDouble(
        ui,
        qHappinessAtZero,
        "Can not get information needed to determine the happiness value at"
        " zero for these residents from the user."
    );

    double happinessAtOne = askUserForDouble(
        ui,
        qHappinessAtOne,
        "Can not get information needed to determine the happiness value at"
        " one for these residents from the user."
    );

    double locationOfDrop = askUserForDouble(
        ui,
        qHappinessDropLocation,
        "Can not get information needed to determine the diversity value at the"
        " drop for these residents from the user."
    );

    std::vector<std::unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<howMany; ++ii)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            firstID+ii,
            color,
            movement,
            happinessGoal,
            happinessAtZero,
            happinessAtOne,
            locationOfDrop
        ));
    }
    return residents;
}

int ResidentsFactory_StepDown::askUserForInt (
    UI& ui, 
    Question_Int question, 
    std::string failureString
)
{
    ui.getAnswer(question);
    if (question.hasValidAnswer())
    {
        return std::stoi(question.getAnswer());
    }
    else
    {
        throw failureString;
    }
}

double ResidentsFactory_StepDown::askUserForDouble (
    UI& ui, 
    Question_Double question, 
    std::string failureString
)
{
    ui.getAnswer(question);
    if (question.hasValidAnswer())
    {
        return std::stod(question.getAnswer());
    }
    else
    {
        throw failureString;
    }
}
