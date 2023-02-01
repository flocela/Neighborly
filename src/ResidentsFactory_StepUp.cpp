#include "ResidentsFactory_StepUp.h"
#include <limits>
#include <sstream>
#include <iomanip>
#include <memory>

#include "HappinessFunc_StepUp.h"
#include "Resident_UsingFunction.h"

using namespace std;

string ResidentsFactory_StepUp::toString ()
{
    return "Step Up Residents Factory";
}

string ResidentsFactory_StepUp::residentType ()
{
    return "Step Up Residents";
}

vector<unique_ptr<Resident>> ResidentsFactory_StepUp::createResidents (
    UI& ui,
    int firstID, 
    int count,
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor //TODO possibley delete, then delete the (void) below
)
{   
    stringstream colorStream;
    colorStream << baseColor;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        1,
        0.0,
        100.0,
        happinessGoal,
        insertIntoString(
            _happiness_with_zero_neighbors_prompt,
            charLocationForColor(_happiness_with_zero_neighbors_prompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));


    // ask user for low happiness value.
    // uses happiness goal if can not get high happiness value.
    Question_Double qLowHappinessValue{
        2,
        0,
        100.0,
        happinessGoal,
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));


    // ask user for high happiness value.
    // uses fallback high happiness value, if can not get high happiness value.
    Question_Double qHighHappinessValue{
        3,
        lowHappinessValue,
        100.0,
        _fallback_high_happiness_value,
        insertIntoString(
            _high_happiness_value_prompt,
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "high happiness value"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    // ask user for drop location.
    // uses _fallback_drop_location if can not get drop location.
    Question_Double qHappinessDropLocation{
        5,
        0.0,
        1.0,
        _fallback_drop_location,
        insertIntoString(
            _stepup_location_prompt,
            charLocationForColor(_stepup_location_prompt),
            colorStream.str()),
        "happiness value's drop location"};

    double locationOfDrop = stod(ui.getAnswer(qHappinessDropLocation));


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
                highHappinessValue,
                lowHappinessValue,
                locationOfDrop
            ),
            "Step Up Resident"
        ));
    }
    return residents;
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

int ResidentsFactory_StepUp::charLocationForColor (string str)
{
    string target = "For the  residents, enter the";
    auto pos = str.find(target);
    return (int)pos + 8;
}