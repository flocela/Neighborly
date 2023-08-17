#include "ResidentsFactory_Falling.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "HappinessFunc_Falling.h"
#include "Question_Double.h"
#include "Resident_Customizable.h"

using namespace std;

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
        true,
        true,
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
        false,
        true,
        happinessGoal,
        insertIntoString(
            _high_happiness_value_prompt, 
            charLocationForColor(_high_happiness_value_prompt),
            colorStream.str()),
        "higher happiness value"
    };

    double highHappinessValue = stod(ui.getAnswer(qHighHappinessValue));


    // ask user for low happiness value, corresponding to diversity of 1.0.
    // uses _fallback_low_happiness_value if can not get low happiness value
    Question_Double qLowHappinessValue{
        3,
        0,
        highHappinessValue,
        true,
        false,
        _fallback_low_happiness_value,
        insertIntoString(
            _low_happiness_value_prompt,
            charLocationForColor(_low_happiness_value_prompt),
            colorStream.str()),
        "lower happiness value"
    };

    double lowHappinessValue = stod(ui.getAnswer(qLowHappinessValue));

    cout << endl << "Creating " << count << " Falling residents::  " 
         << "group number: " << groupNumber 
         << ", allowed movement: " << allowedMovement 
         << ", happiness goal: " << happinessGoal 
         << ", happiness w/ zero neighbors: " << happinessWithZeroNeighbors 
         << ", higher happiness value: " << highHappinessValue 
         << ", lower happiness value: " << lowHappinessValue << endl;
    // create vector of residents.
    vector<unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        // Resident_Customizable requires a HappinessFunc unique pointer
        residents.push_back(make_unique<Resident_Customizable>(
            firstID+ii,
            groupNumber,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Falling> (
                happinessWithZeroNeighbors,
                highHappinessValue,
                lowHappinessValue
            )
        ));
    }
    
    return residents;
}

string ResidentsFactory_Falling::residentType () const
{
    return "Falling Residents";
}

string ResidentsFactory_Falling::toString ()
{
    return "Falling Residents Factory";
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
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}