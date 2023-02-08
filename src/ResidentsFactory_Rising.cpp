#include "ResidentsFactory_Rising.h"
#include <sstream>
#include <iomanip>

#include "HappinessFunc_Rising.h"
#include "Question_Double.h"
#include "Resident_UsingFunction.h"

using namespace std;

string ResidentsFactory_Rising::toString ()
{
    return "Rising Residents Factory";
}

string ResidentsFactory_Rising::residentType () const 
{
    return "Rising Down Residents";
}

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

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal if can not get happiness value for zero neighbors.
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

    // ask user for low happiness value.
    // uses happiness goal if can not get low happiness value from user.
    Question_Double qLowHappinessValue{
        2,
        0,
        100,
        happinessGoal,
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "low happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));

    // ask user for high happiness value.
    // uses _fallback_high_happiness_value if can not get a high happiness value from user.
    Question_Double qHighHappinessValue{
        3,
        lowHappinessValue,
        100.0,
        _fallback_high_happiness_value,
        insertIntoString(
            _high_happiness_value_prompt,
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "happiness goal"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_UsingFunction requires a HappinessFunc unique pointer
        residents.push_back(make_unique<Resident_UsingFunction>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Rising> (
                happinessWithZeroNeighbors,
                highHappinessValue,
                lowHappinessValue
            ),
            "Rising Resident"
        ));
    }
    return residents;
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
    string target = "For the  residents, enter the";
    auto pos = str.find(target);
    return (int)pos + 8;
}