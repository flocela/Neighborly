#include "ResidentsFactory_StepDown.h"

#include <limits>
#include <sstream>
#include <iomanip>
#include <memory>

#include "HappinessFunc_StepDown.h"
#include "Resident_UsingFunction.h"
#include "Question_Double.h"

using namespace std;

string ResidentsFactory_StepDown::toString ()
{
    return "Step Down Residents Factory";
}

string ResidentsFactory_StepDown::residentType () const 
{
    return "Step Down Residents";
}

vector<unique_ptr<Resident>> ResidentsFactory_StepDown::createResidents (
    const UI& ui,
    int firstID, 
    int count,
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor
) const 
{   
    stringstream colorStream;
    colorStream << baseColor;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        happinessGoal,
        insertIntoString(
            _happinessWithZeroNeighborsPrompt,
            charLocationForColor(_happinessWithZeroNeighborsPrompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));


    // ask user for high happiness value.
    // uses happiness goal if can not get high happiness value.
    Question_Double qHighHappinessValue{
        3,
        0.0,
        100.0,
        happinessGoal,
        insertIntoString(
            _high_happiness_value_prompt,
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "happiness goal"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    // ask user for low happiness value.
    // uses _fallback_low_happiness_value if can not get low happiness value
    Question_Double qLowHappinessValue{
        4,
        0,
        highHappinessValue,
        _fallback_low_happiness_value,
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));

    // ask user for drop location.
    // uses _fallback_drop_location if can not get drop location.
    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        _fallback_drop_location,
        insertIntoString(
            _dropLocationOrigPrompt,
            charLocationForColor(_dropLocationOrigPrompt),
            colorStream.str()),
        "happiness value's drop location"};

    double locationOfDrop = stod(ui.getAnswer(qHappinessDropLocation));

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

std::string ResidentsFactory_StepDown::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsFactory_StepDown::charLocationForColor (string str) const 
{
    string target = "For the  residents, enter the";
    auto pos = str.find(target);
    return (int)pos + 8;
}