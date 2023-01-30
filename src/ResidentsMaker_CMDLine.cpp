#include "ResidentsMaker_CMDLine.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

ResidentsMaker_CMDLine:: ResidentsMaker_CMDLine(const UI_CMDLine& cmdline)
: _ui{cmdline}
{}

ResidentsGroupInfo ResidentsMaker_CMDLine::makeResidents (
    const vector<unique_ptr<ResidentsFactory>>& residentsFactories,
    int maxResidentCount,
    int maxNumOfGroupsOfResidents, // currently only two groups allowed.
    vector<BaseColor> colors,
    double maxAllowableMovement
)
{   
    _num_of_groups = maxNumOfGroupsOfResidents; // TODO why is _num_of_groups set on line 20 and 21?
    _num_of_groups = 2; // currently only two groups allowed.
    initColors(colors);
    ResidentsGroupInfo resGroupInfo;
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<_num_of_groups; ++ii)
    {
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;
        if (allowedNumOfResidents <= 0)
            break;

        string curColorBaseName = _colorrs_map[_available_colors[ii]][Mood::neutral]._base_name;
        resGroupInfo._base_color_per_group_num.insert({ii, _available_colors[ii]});

        int numOfResidents = askForNumOfResidents(
            allowedNumOfResidents, 
            curColorBaseName
        );
        
        int choice = askForGroupResidentType(
            curColorBaseName, 
            residentsFactories
        );
        
        double allowedMovement = askForAllowedMovementForGroup(
            curColorBaseName,
            maxAllowableMovement
        );

        double happinessGoal = askForHappinessGoalForGroup(curColorBaseName);

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

// TODO probably get rid of this, definitely make copy of prompt before changing it.
// TODO change fallback
ColorInfo ResidentsMaker_CMDLine::askForGroupColor (int groupIdx)
{
    vector<string> colorStrings = {};
    for (BaseColor color : _available_colors)
        colorStrings.push_back(_colorrs_map[color][Mood::neutral]._base_name);

    vector<string> number = {" first", " second", " third", " fourth"};
    string prompt = _which_group_color_prompt.insert(30, number[groupIdx]);
    int colorIdx = _ui.menu(prompt, colorStrings, 0, "something");
    return _colorrs_map[_available_colors[colorIdx]][Mood::neutral];
}

double ResidentsMaker_CMDLine::askForHappinessGoalForGroup (string color)
{
    Question_Double question = createQuestionGroupHappinessGoal(color);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
    {
        return stod(question.getAnswer());
    }  
    else
    {   
        return (stod(question.getFallback()));
    }
        
}

double ResidentsMaker_CMDLine::askForAllowedMovementForGroup(
    string color, 
    double maxAllowedMovement
)
{
    Question_Double question = createQuestionGroupAllowableMovement(color, maxAllowedMovement);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return stod(question.getAnswer());
    else //TODO check this failure prompt puts group color in the right spot
    {
        return (stod(question.getFallback()));
    }
        
}

int ResidentsMaker_CMDLine::askForNumOfGroupsOfResidents()
{
    Question_Int question = createQuestionHowManyResidentGroups();
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return stoi(question.getAnswer());
    else
       
        throw _how_many_groups_failure;
}

int ResidentsMaker_CMDLine::askForNumOfResidents(int count, string color)
{
    Question_Int question = createQuestionHowManyResidents(count, color);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return stoi(question.getAnswer());
    else{
        return stoi(question.getFallback());
    }
        
}

int ResidentsMaker_CMDLine::askForGroupResidentType (
    string color, 
    const vector<unique_ptr<ResidentsFactory>>& residentsFactories
)
{
    vector<string> factoryNames = getFactoryNames(residentsFactories);
    string prompt = _which_type_prompt;

    string copyFallbackResTypeResponse = _fallback_res_type_response;
    copyFallbackResTypeResponse.insert(59, factoryNames[0]);
    return _ui.menu(prompt.insert(25, color + " "), factoryNames, 0, copyFallbackResTypeResponse);
}

// TODO I don't ask this question anymore, if I do, then make fallback an attribute
Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidentGroups()
{
    string copyHowManyGroupsFailure = _how_many_groups_failure;
    copyHowManyGroupsFailure.insert(56, "2");
    return Question_Int{
        0,
        1,
        3,
        1,
        _how_many_groups_orig_prompt,
        "number of groups"
    };
}

Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidents (
    int count, 
    string color
)
{   
    string copyOrigPrompt = _how_many_residents_orig_prompt;
    copyOrigPrompt.insert(
        35, 
        color + " "
    );
    copyOrigPrompt.insert(
        copyOrigPrompt.size() - 3,
        to_string(count)
    );

    string copyRangePrompt = _how_many_residents_range_prompt;
    copyRangePrompt.insert(55, to_string(count));

    string copyHowManyResidentsFailure = _how_many_residents_failure;
    copyHowManyResidentsFailure.insert(68, to_string(count/2));

    return Question_Int{
        1,
        1,
        count,
        count/2,
        copyOrigPrompt,
        "number of residents for the " + color + " group"
    };
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupHappinessGoal (string color)
{
    string orig_prompt = _group_happiness_orig_prompt;
    return Question_Double{
        2,
        0.0,
        100.0,
        _fallback_group_happiness_goal_failure,
        orig_prompt.insert(56, color + " "),
        "happiness goal"};
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupAllowableMovement (
    string color, 
    double maxAllowedMovement
)
{  
    // add group color to origPrompt;
    string origPrompt = insertIntoString(_group_movement_orig_prompt, 81, color + " ");

    // add maximum allowed movement to orig prompt.
    stringstream fallbackMovementStream;
    double fallback = maxAllowedMovement;
    fallbackMovementStream << fixed << setprecision(2) << fallback;
    origPrompt = insertIntoString(origPrompt, 179+color.size(), fallbackMovementStream.str());

    return Question_Double{
        3,
        0.0,
        maxAllowedMovement,
        maxAllowedMovement/4,
        origPrompt,
        "maximum allowed movement"};
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
