#include "ResidentsFactory_Flat.h"
#include <limits>
#include "Resident_UsingFunction.h"
#include <sstream>
#include <iomanip>
#include "HappinessFunc_Flat.h"

using namespace std;
std::string ResidentsFactory_Flat::toString ()
{
    return "Flat Residents Factory";
}

std::string ResidentsFactory_Flat::residentType ()
{
    return "Flat Residents";
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_Flat::createResidents (
    UI& ui,
    int firstID, 
    int count, 
    double happinessGoal,
    double allowedMovement,
    int groupNumber,
    BaseColor baseColor
)
{   
    stringstream goalStream;
    goalStream << fixed << setprecision(2) << happinessGoal;

    // ask user for happiness value when there are zero neighbors.
    // uses happiness goal as fallback, if can not get happiness value for zero neighbors.
    Question_Double qHappinessWithZeroNeighbors{
        3,
        0.0,
        100.0,
        happinessGoal,
        _happinessWithZeroNeighborsPrompt,
        "happiness value with zero neighbors"
    };

    double happinessWithZeroNeighbors = askUserForDouble(ui, qHappinessWithZeroNeighbors);

    // ask for happiness value. It's always the same.
    std::string curColBaseName = _colorrs_map[baseColor][Mood::neutral]._base_name;
    Question_Double qHappinessValue{
        3,
        0.0,
        100.0,
        _fallback_happiness_value,
        insertIntoString(_happinessValueOrigPrompt, 134, curColBaseName + " "),
        "constant happiness value"
    };

    double happinessValue = askUserForDouble(ui, qHappinessValue);

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
                ),
                "Flat Resident"
            )
        );
    }
    return residents;
}

int ResidentsFactory_Flat::askUserForInt ( UI& ui, Question_Int question)
{
    return stoi(ui.getAnswer(question));
}

double ResidentsFactory_Flat::askUserForDouble (UI& ui, Question_Double question)
{
    return stod(ui.getAnswer(question));
}

std::string ResidentsFactory_Flat::insertIntoString (string str, int location, string insert) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}
