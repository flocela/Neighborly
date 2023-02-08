#include "ResidentsFactory_Falling.h"
#include <sstream>
#include <iomanip>

#include "HappinessFunc_Falling.h"
#include "Question_Double.h"
#include "Resident_UsingFunction.h"

using namespace std;

string ResidentsFactory_Falling::toString ()
{
    return "Falling Residents Factory";
}

string ResidentsFactory_Falling::residentType () const
{
    return "Falling Residents";
}

vector<unique_ptr<Resident>> ResidentsFactory_Falling::createResidents (
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
    // uses happiness goal if can not get happiness value corresponding to zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        1,
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


    // ask user for high happiness value, corresponding to diversity of 0.0.
    // uses happiness goal if can not get high happiness value.
    Question_Double qHighHappinessValue{
        2,
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


    // ask user for low happiness value, corresponding to diversity of 1.0.
    // uses _fallback_low_happiness_value if can not get low happiness value
    Question_Double qLowHappinessValue{
        3,
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


    // create vector of residents.
    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_UsingFunction requires a HappinessFunc unique pointer
        residents.push_back(make_unique<Resident_UsingFunction>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Falling> (
                happinessWithZeroNeighbors,
                highHappinessValue,
                lowHappinessValue
            ),
            "Falling Resident"
        ));
    }
    return residents;
}

std::string ResidentsFactory_Falling::insertIntoString (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsFactory_Falling::charLocationForColor (string str) const
{
    string target = "For the  residents, enter the";
    auto pos = str.find(target);
    return (int)pos + 8;
}