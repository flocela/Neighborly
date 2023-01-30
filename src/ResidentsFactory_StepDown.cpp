#include "ResidentsFactory_StepDown.h"
#include <limits>
#include <sstream>
#include <iomanip>
#include <memory>
#include "HappinessFunc_StepDown.h"
#include "Resident_UsingFunction.h"

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
    BaseColor baseColor //TODO possibley delete, then delete the (void) below
)
{   (void) baseColor;

    stringstream goalStream;
    goalStream << fixed << setprecision(2) << happinessGoal;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal (from goalStream) if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        happinessGoal,
        _happinessWithZeroNeighborsPrompt,
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = askUserForDouble(ui, qHappinessWithZeroNeighbors);

    // ask user for high happiness value.
    // uses happiness goal (from goalStream) if can not get high happiness value.
    Question_Double qHighHappinessValue{
        3,
        0.0,
        100.0,
        happinessGoal,
        _high_happiness_value_prompt,
        "happiness goal"
    };

    double highHappinessValue = askUserForDouble(
        ui,
        qHighHappinessValue
    );

    // ask user for low happiness value.
    // uses _fallback_low_happiness_value if can not get low happiness value
    stringstream high_val_stream;
    high_val_stream << fixed << setprecision(1) << highHappinessValue;

    Question_Double qLowHappinessValue{
        4,
        0,
        highHappinessValue,
        _fallback_low_happiness_value,
        insertIntoString(
            _low_happiness_value_prompt,
            _low_happiness_value_prompt.size()-13,
            high_val_stream.str()),
        "low happiness value"
    };

    double lowHappinessValue = askUserForDouble(
        ui,
        qLowHappinessValue
    );

    // ask user for drop location.
    // uses _fallback_drop_location if can not get drop location.
    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        _fallback_drop_location,
        _dropLocationOrigPrompt,
        "happiness value's drop location"};

    double locationOfDrop = askUserForDouble(ui, qHappinessDropLocation);

    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_UsingFunction requires a HappinessFunc unique pointer
        residents.push_back(make_unique<Resident_UsingFunction>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepDown> (
                happinessWithZeroNeighbors,
                highHappinessValue,
                lowHappinessValue,
                locationOfDrop
            ),
            "Step Down Resident"
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

std::string ResidentsFactory_StepDown::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}