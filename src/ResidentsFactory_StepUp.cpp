#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include "HappinessFunc_StepUp.h"
#include "Question_Double.h"
#include "Resident_Customizable.h"
#include "ResidentsFactory_StepUp.h"

using namespace std;

vector<unique_ptr<Resident>> ResidentsFactory_StepUp::createResidents (
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
        1,
        0.0,
        100.0,
        true,
        true,
        happinessGoal, // fallback
        insertIntoString(
            _happiness_with_zero_neighbors_prompt,
            charLocationForColor(_happiness_with_zero_neighbors_prompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));

    double lowHappinessFallback = (happinessGoal == 100)? happinessGoal- 1 : happinessGoal;
    
    // Ask user for low happiness value.
    // Uses happiness goal if can not get high happiness value.
    Question_Double qLowHappinessValue{
        2,
        0,
        100.0,
        true,
        false,
        lowHappinessFallback, // fallback
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));


    // Ask user for high happiness value.
    // Uses fallback high happiness value, if can not get high happiness value.
    Question_Double qHighHappinessValue{
        3,
        lowHappinessValue,
        100.0,
        false,
        true,
        _fallback_high_happiness_value,
        insertIntoString(
            _high_happiness_value_prompt,
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "high happiness value"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    // Ask user for step-up location.
    // Uses _fallback_step_location if can not get step-up location.
    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        true,
        false,
        _fallback_step_location,
        insertIntoString(
            _stepup_location_prompt,
            charLocationForColor(_stepup_location_prompt),
            colorStream.str()),
        "happiness value's step-up location"};

    double locationOfStep = stod(ui.getAnswer(qHappinessDropLocation));

    cout << endl << "Creating " << count << " Step-Up residents:: "
         << "group number: " << groupNumber
         << ", allowed movement: " << allowedMovement
         << ", happiness goal: " << happinessGoal
         << ", happiness w/ zero neighbors: " << happinessWithZeroNeighbors
         << ", higher happiness value: " << highHappinessValue
         << ", lower happiness value: " << lowHappinessValue
         << ", diversity at drop-down: " << locationOfStep << endl;

    // Create residents.
    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_Customizable requires a unique_pointer of type HappinessFunc.
        residents.push_back(make_unique<Resident_Customizable>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepUp> (
                happinessWithZeroNeighbors,
                lowHappinessValue,
                highHappinessValue,
                locationOfStep
            )
        ));
    }
    return residents;
}

string ResidentsFactory_StepUp::residentType ()const 
{
    return "Step Up Residents";
}

string ResidentsFactory_StepUp::toString ()
{
    return "Step Up Residents Factory";
}

std::string ResidentsFactory_StepUp::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsFactory_StepUp::charLocationForColor (string str) const 
{
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}