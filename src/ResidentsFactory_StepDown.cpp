#include "ResidentsFactory_StepDown.h"
#include <limits>
#include "Resident_StepDown.h"
#include <sstream>
#include <iomanip>

using namespace std;

string ResidentsFactory_StepDown::toString ()
{
    return "Step Down Residents Factory";
}

string ResidentsFactory_StepDown::residentType ()
{
    return "Step Down Residents";
}

vector<unique_ptr<Resident>> ResidentsFactory_StepDown::createResidents (
    UI& ui,
    int firstID, 
    int count,
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor
)
{   (void) baseColor;

    stringstream goalStream;
    goalStream << fixed << setprecision(2) << happinessGoal;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal if can not get happiness value for zero neighbors.
    string copyHappinessWithZeroNeighborsFailure = _happiness_with_zero_neighbors_failure;
    copyHappinessWithZeroNeighborsFailure.insert(70, goalStream.str());

    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        _happinessWithZeroNeighborsPrompt,
        _happinessWithZeroNeighborsTypePrompt,
        _happinessWithZeroNeighborsRangePrompt,
        goalStream.str(),
        copyHappinessWithZeroNeighborsFailure
    };

    double happinessWithZeroNeighbors = askUserForDouble(ui, qHappinessWithZeroNeighbors);

    // ask user for high happiness value.
    // uses happiness goal if can not get high happiness value.
    string copyHighHappinessFailure = _high_happiness_value_failure;
    copyHighHappinessFailure.insert(42, goalStream.str());
    Question_Double qHighHappinessValue{
        3,
        0.0,
        100.0,
        _high_happiness_value_prompt,
        _high_happiness_value_type_prompt,
        _high_happiness_value_range_prompt,
        goalStream.str(),
        copyHighHappinessFailure
    };

    double highHappinessValue = askUserForDouble(
        ui,
        qHighHappinessValue
    );

    // ask user for low happiness value.
    // uses _fallback_low_happiness_value if can not get low happiness value
    string copyLowHappinessValuePrompt = _low_happiness_value_prompt;
    string copyLowHappinessRangePrompt = _low_happiness_value_range_prompt;
    string copyLowHappinessValueFailure = _low_happiness_value_failure;
    
    // copyLowHappinessValuePrompt and copyLowHappinessRangePrompt both need to contain
    // the highHappinessValue.
    stringstream high_val_stream;
    high_val_stream << fixed << setprecision(1) << highHappinessValue;

    Question_Double qLowHappinessValue{
        4,
        0,
        highHappinessValue,
        copyLowHappinessValuePrompt.insert(
            copyLowHappinessValuePrompt.size()-13,
            high_val_stream.str()),
        _low_happiness_value_type_prompt,
        copyLowHappinessRangePrompt.insert(
            copyLowHappinessRangePrompt.size() - 13,
            high_val_stream.str()),
        _fallback_low_happiness_value,
        copyLowHappinessValueFailure.insert(41, _fallback_low_happiness_value)
    };

    double lowHappinessValue = askUserForDouble(
        ui,
        qLowHappinessValue
    );

    // ask user for drop location.
    // uses _fallback_drop_location if can not get drop location.
    string copyDropLocationFailure = _drop_location_failure;
    copyDropLocationFailure.insert(35, _fallback_drop_location);

    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        _dropLocationOrigPrompt,
        _dropLocationTypePrompt,
        _dropLocationRangePrompt,
        _fallback_drop_location,
        copyDropLocationFailure};

    double locationOfDrop = askUserForDouble(
        ui,
        qHappinessDropLocation
    );

    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        residents.push_back(make_unique<Resident_StepDown>(
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
    Question_Double question
)
{
    return stod(ui.getAnswer(question));
}