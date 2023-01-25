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
        _how_many_groups_orig_prompt,
        _how_many_groups_type_prompt,
        _how_many_groups_range_prompt,
        "2",
        copyHowManyGroupsFailure
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
        copyOrigPrompt,
        _how_many_residents_type_prompt,
        copyRangePrompt,
        to_string(count/2),
        copyHowManyResidentsFailure
    };
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupHappinessGoal (string color)
{
    string orig_prompt = _group_happiness_orig_prompt;

    string copyGroupHappinessGoalFailure = _group_happiness_failure;
    copyGroupHappinessGoalFailure.insert(75, _fallback_group_happiness_goal_failure);
    return Question_Double{
        2,
        0.0,
        100.0,
        orig_prompt.insert(56, color + " "),
        _group_happiness_type_prompt,
        _group_happiness_range_prompt,
        _fallback_group_happiness_goal_failure,
        copyGroupHappinessGoalFailure};
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupAllowableMovement (
    string color, 
    double maxAllowedMovement
)
{  
    string orig_prompt = _group_movement_orig_prompt;
    string range_prompt = _group_movement_range_prompt;
    string copyGroupMovementFailure = _group_movement_failure;

    stringstream stream1;
    stream1 << fixed << setprecision(2) << (maxAllowedMovement/4);
    string str_mov = stream1.str();

    copyGroupMovementFailure.insert(64, str_mov);

    orig_prompt.insert(81, color + " ");
    stringstream stream2;
    stream2 << fixed << setprecision(1) << maxAllowedMovement;
    str_mov = stream2.str();
    orig_prompt.insert(179 + color.size(), str_mov);

    return Question_Double{
        3,
        0.0,
        maxAllowedMovement,
        orig_prompt,
        _group_movement_type_prompt,
        range_prompt.insert(34, str_mov),
        to_string(maxAllowedMovement/4),
        copyGroupMovementFailure};
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
