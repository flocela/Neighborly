#include "ResidentsFactory_StepDown.h"
#include <limits>
#include "Resident_StepDown.h"
#include <sstream>
#include <iomanip>

std::string ResidentsFactory_StepDown::toString ()
{
    return "Step Down Residents Factory";
}

std::string ResidentsFactory_StepDown::residentType ()
{
    return "Step Down Residents";
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_StepDown::createResidents (
    UI& ui,
    int firstID, 
    int count,
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor
)
{   (void) baseColor;

    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        _happinessWithZeroNeighborsPrompt,
        _happinessWithZeroNeighborsTypePrompt,
        _happinessWithZeroNeighborsRangePrompt
    };

    double happinessWithZeroNeighbors = askUserForDouble(
    ui,
    qHappinessWithZeroNeighbors,
    "Can not get information needed to determine the happiness value with"
    " zero neighbors."
    );

    Question_Double qHighHappinessValue{
        3,
        0.0,
        100.0,
        _high_happiness_value_prompt,
        _high_happiness_value_type_prompt,
        _high_happiness_value_range_prompt
    };

    double highHappinessValue = askUserForDouble(
        ui,
        qHighHappinessValue,
        "Can not get information needed to determine the happiness value at"
        " zero for these residents from the user."
    );

    std::string copy_low_happiness_value_prompt = _low_happiness_value_prompt;
    std::string copy_low_happiness_range_prompt = _low_happiness_value_range_prompt;
    std::stringstream high_val_stream;
    high_val_stream << std::fixed << std::setprecision(1) << highHappinessValue;
    
    Question_Double qLowHappinessValue{
        4,
        0,
        highHappinessValue,
        copy_low_happiness_value_prompt.insert(
            copy_low_happiness_value_prompt.size()-13,
            high_val_stream.str()),
        _low_happiness_value_type_prompt,
        copy_low_happiness_range_prompt.insert(
            copy_low_happiness_range_prompt.size() - 13,
            high_val_stream.str())
    };

    double lowHappinessValue = askUserForDouble(
        ui,
        qLowHappinessValue,
        "Can not get information needed to determine the happiness value at"
        " one for these residents from the user."
    );

    Question_Double qHappinessDropLocation{
    5,
    0.0,
    100.0,
    _dropLocationOrigPrompt,
    _dropLocationTypePrompt,
    _dropLocationRangePrompt
    };

    double locationOfDrop = askUserForDouble(
        ui,
        qHappinessDropLocation,
        "Can not get information needed to determine the diversity value at the"
        " drop for these residents from the user."
    );

    std::vector<std::unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            happinessWithZeroNeighbors,
            highHappinessValue,
            lowHappinessValue,
            locationOfDrop
        ));
    }
    return residents;
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