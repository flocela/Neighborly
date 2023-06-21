#include "ResidentsMaker_CMDLine.h"
#include <iomanip>
#include <sstream>
#include <iostream> 
#include "Question_Double.h"
#include "Question_Int.h"

using namespace std;

ResidentsGroupInfo ResidentsMaker_CMDLine::makeResidents (
    const UI& ui,
    const vector<unique_ptr<const ResidentsFactory>>& residentsFactories,
    int maxResidentCount,
    int maxNumOfGroupsOfResidents,
    vector<BaseColor> colors,
    double maxAllowableMovement
)
{   // TODO only 2 groups allowed, so use an adapter class around this class.
    if (maxNumOfGroupsOfResidents > 2)
    {
        _num_of_resident_groups = askForNumOfGroupsOfResidents(ui, maxNumOfGroupsOfResidents);
    }
    else
    {
        _num_of_resident_groups = maxNumOfGroupsOfResidents;
    }
    
    initColors(colors);

    // resGroupInfo is returned after adding residents and colors to it.
    ResidentsGroupInfo resGroupInfo;
    
    int numOfResidentsCreated = 0; // first id is zero.
    for (int ii=0; ii<_num_of_resident_groups; ++ii)
    {
        // set max number of resident spaces left
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;

        if (allowedNumOfResidents <= 0)
            break;

        // set base color
        BaseColor curBaseColor = _available_colors[ii];
        resGroupInfo._base_color_per_group_num.insert({ii+1, curBaseColor});

        stringstream colorStream;
        colorStream << curBaseColor;

        string curColorBaseName = colorStream.str();
        

        // Prompt user for information:

        int numOfResidents = askForNumOfResidents(ui, allowedNumOfResidents, curColorBaseName);
        
        int choice = askForGroupResidentType(ui, curColorBaseName, residentsFactories);
        
        double allowedMovement = askForAllowedMovementForGroup(
            ui, 
            curColorBaseName,
            maxAllowableMovement
        );

        double happinessGoal = askForHappinessGoalForGroup(ui, curColorBaseName);

        vector<unique_ptr<Resident>> newResidents = residentsFactories[choice]->createResidents(
            ui,
            numOfResidentsCreated,
            numOfResidents,
            happinessGoal,
            allowedMovement,
            ii+1,
            _available_colors[ii]
            );

        for (auto& r: newResidents)
            resGroupInfo._residents.emplace_back(move(r));

        numOfResidentsCreated += newResidents.size();
    }
    
    return resGroupInfo;
}

void ResidentsMaker_CMDLine::initColors (vector<BaseColor> colors)
{
    _available_colors = colors;
}


int ResidentsMaker_CMDLine::askForNumOfGroupsOfResidents(const UI& ui, int maxNumOfResidentGroups)
{
    Question_Int question = Question_Int{
        0,
        1,
        maxNumOfResidentGroups,
        true,
        true,
        2,
        _how_many_groups_orig_prompt,
        "number of groups"
    };
    return stoi(ui.getAnswer(question));
}

int ResidentsMaker_CMDLine::askForNumOfResidents(const UI& ui, int count, string color)
{
    // add max number of residents to prompt
    string howManyResidentsPrompt = insertIntoString(
        _how_many_residents_orig_prompt,
        _how_many_residents_orig_prompt.size() - 1,
        to_string(count)
    );

    // create question, add color to prompt
    Question_Int question{
        1,
        1,
        count,
        true,
        true,
        count/2,
        insertIntoString(
            howManyResidentsPrompt,
            charLocationForColor(howManyResidentsPrompt),
            color),
        "number of residents for the " + color + " group"
    };

    return stoi(ui.getAnswer(question));
}

int ResidentsMaker_CMDLine::askForGroupResidentType (
    const UI& ui,
    string color, 
    const vector<unique_ptr<const ResidentsFactory>>& residentsFactories
)
{
    vector<string> factoryNames = getFactoryNames(residentsFactories);

    // insert color into _which_type_prompt and insert first factory name into fallback response.
    return ui.menu(
            insertIntoString(
                _which_type_prompt,
                charLocationForColor(_which_type_prompt),
                color),
            factoryNames,
            0,
            insertIntoString(
                _fallback_res_type_response,
                59,
                factoryNames[0]
            ));
}

double ResidentsMaker_CMDLine::askForAllowedMovementForGroup(
    const UI& ui,
    string color, 
    double maxAllowedMovement
)
{   
    stringstream maxMovementStream;
    maxMovementStream << fixed << setprecision(2) << maxAllowedMovement;
    // add maximum movement to movement prompt
    string movementPrompt = insertIntoString (
        _group_movement_orig_prompt,
        _group_movement_orig_prompt.size() - 1,
        maxMovementStream.str()
    );

    // create question, add color to prompt
    Question_Double question{
        3,
        0.0,
        maxAllowedMovement,
        true,
        true,
        maxAllowedMovement/4,
        insertIntoString(
            movementPrompt,
            charLocationForColor(movementPrompt),
            color
        ),
        "maximum allowed movement"};
    
    return stod(ui.getAnswer(question));
}

double ResidentsMaker_CMDLine::askForHappinessGoalForGroup (const UI& ui, string color)
{
    // create question, add color to prompot
    Question_Double question{
        4,
        0.0,
        100.0,
        true,
        true,
        _fallback_group_happiness_goal_failure,
        insertIntoString(
            _happiness_goal_orig_prompt,
            charLocationForColor(_happiness_goal_orig_prompt),
            color),
        "happiness goal"};
    
    return stod(ui.getAnswer(question));
}

vector<string> ResidentsMaker_CMDLine::getFactoryNames (
    const vector<unique_ptr<const ResidentsFactory>>& residentsFactories
)
{
    vector<string> residentsFactoryNames = {};
    for (auto& residentFactory: residentsFactories)
    {
        residentsFactoryNames.push_back(residentFactory->residentType());
    }
    return residentsFactoryNames;
}

std::string ResidentsMaker_CMDLine::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}

int ResidentsMaker_CMDLine::charLocationForColor (string str)
{
    string target = "the  group";
    auto pos = str.find(target);
    return (int)pos + 4;
}
