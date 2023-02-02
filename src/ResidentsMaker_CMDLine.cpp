#include "ResidentsMaker_CMDLine.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

ResidentsMaker_CMDLine::ResidentsMaker_CMDLine(const UI_CMDLine& cmdline)
: _ui{cmdline}
{}

ResidentsMaker_CMDLine::ResidentsMaker_CMDLine(ResidentsMaker&& orig) noexcept:
_num_of_resident_groups{move(orig._num_of_resident_groups)},
_ui{}
{
    
}

ResidentsGroupInfo ResidentsMaker_CMDLine::makeResidents (
    const vector<unique_ptr<ResidentsFactory>>& residentsFactories,
    int maxResidentCount,
    int maxNumOfGroupsOfResidents, // currently only two groups allowed.
    vector<BaseColor> colors,
    double maxAllowableMovement
)
{   
    if (maxNumOfGroupsOfResidents > 2)
    {
        _num_of_resident_groups = askForNumOfGroupsOfResidents(maxNumOfGroupsOfResidents);
    }
    else
    {
        _num_of_resident_groups = maxNumOfGroupsOfResidents;
    }
    
    initColors(colors);

    // will return resGroupInfo after adding residents and colors to it.
    ResidentsGroupInfo resGroupInfo;
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<_num_of_resident_groups; ++ii)
    {
        // set max number of resident spaces left
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;

        if (allowedNumOfResidents <= 0)
            break;

        // set base color
        BaseColor curBaseColor = _available_colors[ii];
        resGroupInfo._base_color_per_group_num.insert({ii, curBaseColor});

        stringstream colorStream;
        colorStream << curBaseColor;

        string curColorBaseName = colorStream.str();
        

        // Prompt user for information:

        int numOfResidents = askForNumOfResidents(allowedNumOfResidents, curColorBaseName);
        
        int choice = askForGroupResidentType(curColorBaseName, residentsFactories);
        
        double allowedMovement = askForAllowedMovementForGroup(
            curColorBaseName,
            maxAllowableMovement
        );

        double happinessGoal = askForHappinessGoalForGroup(curColorBaseName);

        // create residents
        auto newResidents = residentsFactories[choice]->createResidents(
            _ui,
            numOfResidentsCreated,
            numOfResidents,
            happinessGoal,
            allowedMovement,
            ii,
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

double ResidentsMaker_CMDLine::askForHappinessGoalForGroup (string color)
{
    // create question, add color to prompot
    Question_Double question{
        2,
        0.0,
        100.0,
        _fallback_group_happiness_goal_failure,
        insertIntoString(
            _group_happiness_orig_prompt,
            charLocationForColor(_group_happiness_orig_prompt),
            color),
        "happiness goal"};
    
    return stod(_ui.getAnswer(question));
}

double ResidentsMaker_CMDLine::askForAllowedMovementForGroup(
    string color, 
    double maxAllowedMovement
)
{   
    // add max movement to movement prompt
    string movementPrompt = insertIntoString (
        _group_movement_orig_prompt,
        _group_movement_orig_prompt.size() - 3,
        to_string(maxAllowedMovement)
    );

    // create question, add color to prompt
    Question_Double question{
        3,
        0.0,
        maxAllowedMovement,
        maxAllowedMovement/4,
        insertIntoString(
            movementPrompt,
            charLocationForColor(movementPrompt),
            color
        ),
        "maximum allowed movement"};
    
    return stod(_ui.getAnswer(question));
}

int ResidentsMaker_CMDLine::askForNumOfGroupsOfResidents(int maxNumOfResidentGroups)
{
    Question_Int question = Question_Int{
        0,
        1,
        maxNumOfResidentGroups,
        2,
        _how_many_groups_orig_prompt,
        "number of groups"
    };
    return stoi(_ui.getAnswer(question));
}

int ResidentsMaker_CMDLine::askForNumOfResidents(int count, string color)
{
    // add max number of residents to prompt
    string howManyResidentsPrompt = insertIntoString(
        _how_many_residents_orig_prompt,
        _how_many_residents_orig_prompt.size() - 3,
        to_string(count)
    );

    // create question, add color to prompt
    Question_Int question{
        1,
        1,
        count,
        count/2,
        insertIntoString(
            howManyResidentsPrompt,
            charLocationForColor(howManyResidentsPrompt),
            color),
        "number of residents for the " + color + " group"
    };

    return stoi(_ui.getAnswer(question));
}

int ResidentsMaker_CMDLine::askForGroupResidentType (
    string color, 
    const vector<unique_ptr<ResidentsFactory>>& residentsFactories
)
{
    vector<string> factoryNames = getFactoryNames(residentsFactories);

    // insert color into _which_type_prompt and insert first factory name into fallback response.
    return _ui.menu(
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

vector<string> ResidentsMaker_CMDLine::getFactoryNames (
    const vector<unique_ptr<ResidentsFactory>>& residentsFactories
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
