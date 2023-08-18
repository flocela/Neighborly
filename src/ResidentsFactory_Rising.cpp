#include <iomanip>
#include <iostream>
#include <sstream>

#include "HappinessFunc_Rising.h"
#include "Question_Double.h"
#include "Resident_Customizable.h"
#include "ResidentsFactory_Rising.h"

using namespace std;

vector<unique_ptr<Resident>> ResidentsFactory_Rising::createResidents (
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
            _happinessWithZeroNeighborsPrompt,
            charLocationForColor(_happinessWithZeroNeighborsPrompt),
            colorStream.str()),
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = stod(ui.getAnswer(qHappinessWithZeroNeighbors));

    // Ask user for low happiness value.
    // Uses happiness goal if can not get low happiness value from user.
    Question_Double qLowHappinessValue{
        2,
        0,
        100,
        true,
        false,
        happinessGoal, // fallback
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));

    // Usk user for high happiness value.
    // Uses _fallback_high_happiness_value if can not get a high happiness value from user.
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
        "happiness goal"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));

    cout << endl << "Creating " << count << " Rising residents:: " 
         << "group number: " << groupNumber
         << ", allowed movement: " << allowedMovement
         << ", happiness goal: " << happinessGoal 
         << ", happiness w/zero neighbors: " << happinessWithZeroNeighbors
         << ", lower happiness value: " << lowHappinessValue
         << ", higher happiness value: " << highHappinessValue << endl;

    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_Customizable requires a unique pointer of type HappinessFunc.
        residents.push_back(make_unique<Resident_Customizable>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Rising> (
                happinessWithZeroNeighbors,
                lowHappinessValue,
                highHappinessValue
            )
        ));
    }
    return residents;
}

string ResidentsFactory_Rising::residentType () const 
{
    return "Rising Residents";
}

string ResidentsFactory_Rising::toString ()
{
    return "Rising Residents Factory";
}

std::string ResidentsFactory_Rising::insertIntoString (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsFactory_Rising::charLocationForColor (string str) const 
{
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}