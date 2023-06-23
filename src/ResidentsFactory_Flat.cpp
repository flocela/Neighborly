#include "ResidentsFactory_Flat.h"

#include <iomanip>
#include <limits>
#include <sstream>
#include <iostream>

#include "HappinessFunc_Flat.h"
#include "Resident_UsingFunction.h"
#include "Question_Double.h"
#include "Question_Int.h"

using namespace std;

std::vector<std::unique_ptr<Resident>> ResidentsFactory_Flat::createResidents (
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
    // uses happiness goal as fallback, if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        3,
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


    // ask for happiness value. It's always the same.
    Question_Double qHappinessValue{
        3,
        0.0,
        100.0,
        true,
        true,
        _fallback_happiness_value,
        insertIntoString(
            _happinessValueOrigPrompt,
            charLocationForColor(_happinessValueOrigPrompt),
            colorStream.str()),
        "constant happiness value"
    };

    double happinessValue = stod(ui.getAnswer(qHappinessValue));

    cout << endl << "Creating " << count << " Flat residents:: " 
         << "group number: " << groupNumber
         << ", allowed movement: " << allowedMovement
         << ", happiness goal: " << happinessGoal
         << ", happiness w/ zero neighbors: " <<happinessWithZeroNeighbors
         << ", happiness value: " << happinessValue << endl;

    // create residents
    std::vector<std::unique_ptr<Resident>> residents = {};

    for ( int ii=0; ii<count; ++ii)
    {
        residents.push_back(
            std::make_unique<Resident_UsingFunction>(
                firstID+ii,
                groupNumber,
                allowedMovement,
                happinessGoal,
                make_unique<HappinessFunc_Flat>(
                    happinessWithZeroNeighbors,
                    happinessValue
                )
            )
        );
    }
    return residents;
}

std::string ResidentsFactory_Flat::residentType () const 
{
    return "Flat Residents";
}

std::string ResidentsFactory_Flat::toString ()
{
    return "Flat Residents Factory";
}

std::string ResidentsFactory_Flat::insertIntoString (string str, int location, string insert) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsFactory_Flat::charLocationForColor (string str) const 
{
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}
