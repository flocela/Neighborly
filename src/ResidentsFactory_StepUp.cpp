#include "ResidentsFactory_StepUp.h"
#include <limits>
#include <sstream>
#include <iomanip>
#include <memory>
#include <iostream>

#include "HappinessFunc_StepUp.h"
#include "Question_Double2.h"
#include "Resident_UsingFunction.h"

using namespace std;

vector<unique_ptr<Resident>> ResidentsFactory_StepUp::createResidents (
    const UI& ui,
    int firstID, 
    int count,
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor //TODO possibley delete, then delete the (void) below
) const 
{   
    stringstream colorStream;
    colorStream << baseColor;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal if can not get happiness value for zero neighbors.
    Question_Double2 qHappinessWithZeroNeighbors{
        1,
        0.0,
        100.0,
        true,
        true,
        happinessGoal,
        insertIntoString(
            _happiness_with_zero_neighbors_prompt,
            charLocationForColor(_happiness_with_zero_neighbors_prompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));

    double lowHappinessFallback = (happinessGoal == 100)? happinessGoal- 1 : happinessGoal;
    // ask user for low happiness value.
    // uses happiness goal if can not get high happiness value.
    Question_Double2 qLowHappinessValue{
        2,
        0,
        100.0,
        true,
        false,
        lowHappinessFallback,
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));


    // ask user for high happiness value.
    // uses fallback high happiness value, if can not get high happiness value.
    Question_Double2 qHighHappinessValue{
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


    // ask user for step-up location.
    // uses _fallback_step_location if can not get step-up location.
    Question_Double2 qHappinessDropLocation{
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

    cout << endl << "StepUp: " << groupNumber << ", " << allowedMovement << ", " <<
    happinessGoal << ", " << happinessWithZeroNeighbors << ", " << highHappinessValue <<
    lowHappinessValue << ", " << locationOfStep << endl;

    // create residents
    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_UsingFunction requires a HappinessFunc unique pointer
        residents.push_back(make_unique<Resident_UsingFunction>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepUp> (
                happinessWithZeroNeighbors,
                lowHappinessValue,
                highHappinessValue,
                locationOfStep
            ),
            "Step Up Resident"
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