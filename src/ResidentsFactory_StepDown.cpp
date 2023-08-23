#include <limits>
#include <sstream>
#include <iomanip>
#include <memory>
#include <iostream>
#include "HappinessFunc_StepDown.h"
#include "Resident_Customizable.h"
#include "ResidentsFactory_StepDown.h"
#include "Question_Double.h"

using namespace std;

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

    // Ask user for happiness value when there are zero neighbors.
    // Uses happiness goal if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        true,
        true,
        happinessGoal, // fallback
        insertIntoString(
            _happinessWithZeroNeighborsPrompt,
            charLocationForColor(_happinessWithZeroNeighborsPrompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));


    // Ask user for high happiness value.
    // Uses happiness goal if can not get high happiness value.
    Question_Double qHighHappinessValue{
        3,
        0.0,
        100.0,
        false,
        true,
        happinessGoal, // fallback
        insertIntoString(
            _high_happiness_value_prompt,
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "high happiness value"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    // Ask user for low happiness value.
    // Uses _fallback_low_happiness_value if can not get low happiness value.
    Question_Double qLowHappinessValue{
        4,
        0,
        highHappinessValue,
        true,
        false,
        _fallback_low_happiness_value, // fallback
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));

    // Ask user for drop location.
    // Uses _fallback_drop_location if can not get drop location.
    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        true,
        false,
        _fallback_drop_location,
        insertIntoString(
            _dropLocationOrigPrompt,
            charLocationForColor(_dropLocationOrigPrompt),
            colorStream.str()),
        "happiness value's drop location"};

    double locationOfDrop = stod(ui.getAnswer(qHappinessDropLocation));

    cout << endl << "Creating " << count << " Step-Down residents:: "
         << "group number: " << groupNumber
         << ", allowed movement: " << allowedMovement
         << ", happiness goal: " << happinessGoal
         << ", happiness w/ zero neighbors: " << happinessWithZeroNeighbors
         << ", higher happiness value: " << highHappinessValue
         << ", lower happiness value: " << lowHappinessValue
         << ", diversity at drop-down: " << locationOfDrop << endl;

    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_Customizable requires a unique pointer of type HappinessFunc.
        residents.push_back(make_unique<Resident_Customizable>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepDown> (
                happinessWithZeroNeighbors,
                highHappinessValue,
                lowHappinessValue,
                locationOfDrop
            )
        ));
    }
    return residents;
}

string ResidentsFactory_StepDown::residentType () const 
{
    return "Step Down Residents";
}

string ResidentsFactory_StepDown::toString ()
{
    return "Step Down Residents Factory";
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
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}