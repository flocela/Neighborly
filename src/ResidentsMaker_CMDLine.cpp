#include "ResidentsMaker_CMDLine.h"
#include <iostream>
#include <iomanip>
#include <sstream>

ResidentsMaker_CMDLine:: ResidentsMaker_CMDLine(const UI_CMDLine& cmdline)
: _ui{cmdline}
{}

ResidentsGroupInfo ResidentsMaker_CMDLine::makeResidents (
    const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories,
    int maxResidentCount,
    int maxNumOfGroupsOfResidents, // currently only two groups allowed.
    std::vector<BaseColor> colors,
    double maxAllowableMovement
)
{   
    _num_of_groups = maxNumOfGroupsOfResidents;
    _num_of_groups = 2; // currently only two groups allowed.
    initColors(colors);
    ResidentsGroupInfo resGroupInfo;
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<_num_of_groups; ++ii)
    {
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;
        if (allowedNumOfResidents <= 0)
            break;

        std::string curColorBaseName = _colorrs_map[_available_colors[ii]][Mood::neutral]._base_name;
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
            resGroupInfo._residents.emplace_back(std::move(r));

        numOfResidentsCreated += newResidents.size();
    }
    
    return resGroupInfo;
}

void ResidentsMaker_CMDLine::initColors (std::vector<BaseColor> colors)
{
    _available_colors = colors;
}

// TODO probably get rid of this, definitely make copy of prompt before changing it.
ColorInfo ResidentsMaker_CMDLine::askForGroupColor (int groupIdx)
{
    std::vector<std::string> colorStrings = {};
    for (BaseColor color : _available_colors)
        colorStrings.push_back(_colorrs_map[color][Mood::neutral]._base_name);

    std::vector<std::string> number = {" first", " second", " third", " fourth"};
    std::string prompt = _which_group_color_prompt.insert(30, number[groupIdx]);
    int colorIdx = _ui.menu(prompt, colorStrings, 0);
    return _colorrs_map[_available_colors[colorIdx]][Mood::neutral];
}

double ResidentsMaker_CMDLine::askForHappinessGoalForGroup (std::string color)
{
    Question_Double question = createQuestionGroupHappinessGoal(color);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
    {
        return std::stod(question.getAnswer());
    }  
    else
    {   std::string failure_message = _group_happiness_failure;
        throw failure_message.insert(56, color + " ");
    }
        
}

double ResidentsMaker_CMDLine::askForAllowedMovementForGroup(
    std::string color, 
    double maxAllowedMovement
)
{
    Question_Double question = createQuestionGroupAllowableMovement(color, maxAllowedMovement);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stod(question.getAnswer());
    else //TODO check this failure prompt puts group color in the right spot
    {
        std::string failure_message = _group_movement_failure;
        throw failure_message.insert(69, color + " ");
    }
        
}

int ResidentsMaker_CMDLine::askForNumOfGroupsOfResidents()
{
    Question_Int question = createQuestionHowManyResidentGroups();
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
       
        throw _how_many_groups_failure;
}

int ResidentsMaker_CMDLine::askForNumOfResidents(int count, std::string color)
{
    Question_Int question = createQuestionHowManyResidents(count, color);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else{
        std::string failure_message = _how_many_residents_failure;
        throw failure_message.insert(48 , color + " ");
    }
        
}

int ResidentsMaker_CMDLine::askForGroupResidentType (
    std::string color, 
    const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
)
{
    std::vector<std::string> factoryNames = getFactoryNames(residentsFactories);
    std::string prompt = _which_type_prompt;
    return _ui.menu(prompt.insert(25, color + " "), factoryNames, 0);
}

Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidentGroups()
{
    return Question_Int{
        0,
        1,
        3, 
        _how_many_groups_orig_prompt,
        _how_many_groups_type_prompt,
        _how_many_groups_range_prompt
    };
}

Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidents (
    int count, 
    std::string color
)
{   
    std::string prompt = _how_many_residents_orig_prompt;
    prompt.insert(
        35, 
        color + " "
    );
    prompt.insert(
        prompt.size() - 3,
        std::to_string(count)
    );
    return Question_Int{
        1,
        1,
        count,
        prompt,
        _how_many_residents_type_prompt,
        _how_many_residents_range_prompt
    };
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupHappinessGoal (std::string color)
{
    std::string orig_prompt = _group_happiness_orig_prompt;
    return Question_Double{
        2,
        0.0,
        100.0,
        orig_prompt.insert(56, color + " "),
        _group_happiness_type_prompt,
        _group_happiness_range_prompt};
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupAllowableMovement (
    std::string color, 
    double maxAllowedMovement
)
{  
    std::string orig_prompt = _group_movement_orig_prompt;
    std::string range_prompt = _group_movement_range_prompt;

    orig_prompt.insert(81, color + " ");
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << maxAllowedMovement;
    std::string str_mov = stream.str();
    orig_prompt.insert(179 + color.size(), str_mov);
    return Question_Double{
        3,
        0.0,
        maxAllowedMovement,
        orig_prompt,
        _group_movement_type_prompt,
        range_prompt.insert(34, str_mov)};
}

std::vector<std::string> ResidentsMaker_CMDLine::getFactoryNames (
    const std::vector<std::unique_ptr<ResidentsFactory>>& residentsFactories
)
{
    std::vector<std::string> residentsFactoryNames = {};
    for (auto& residentFactory: residentsFactories)
    {
        residentsFactoryNames.push_back(residentFactory->residentType());
    }
    return residentsFactoryNames;
}
