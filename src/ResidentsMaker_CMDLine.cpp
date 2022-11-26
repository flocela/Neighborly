#include "ResidentsMaker_CMDLine.h"
#include <iostream>



std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeBaseResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount,
    std::set<BaseColor> colors // these are the colors that the residents can be.
)
{   
    (void) maxResidentCount;
    if (colors.size() < 3)
        throw std::invalid_argument( "colorInfos must have at least 3 colors.");
    initColors(colors);

    std::vector<std::unique_ptr<Resident>> residents;

    auto residentsGroup1 = residentsFactories[0]->createBaseResidents (
         _ui,
        0,
        30,
        0.5,
        1);

    auto residentsGroup2 = residentsFactories[0]->createBaseResidents (
        _ui,
        13,
        50,
        0.5,
        2);

    for (auto& r: residentsGroup1)
        residents.emplace_back(std::move(r));

    for (auto& r: residentsGroup2)
        residents.emplace_back(std::move(r));
    
    return residents;
}

std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount,
    std::set<BaseColor> colors

)
{   
    if (colors.size() < 2)
    {
        initWithBaseColors();
    }
    else
    {
        initColors(colors);
    }

    std::vector<std::unique_ptr<Resident>> residents;
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<_num_of_groups; ++ii)
    {
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;
        if (allowedNumOfResidents <= 0)
            break;

        std::string curBaseName = _colorrs_map[_available_colors[0]][Mood::neutral]._base_name;

        int numOfResidents = askForNumOfResidents(
            allowedNumOfResidents, 
            curBaseName
        );
        
        int choice = askForGroupResidentType(
            curBaseName, 
            residentsFactories
        );

        double happinessGoal = askForHappinessGoalForGroup(curBaseName);

        auto newResidents = residentsFactories[choice]->createResidents(
            _ui,
            numOfResidentsCreated,
            numOfResidents,
            happinessGoal,
            ii
            );

        for (auto& r: newResidents)
            residents.emplace_back(std::move(r));

        numOfResidentsCreated += newResidents.size();
    }
    
    return residents;
}

void ResidentsMaker_CMDLine::initColors (std::set<BaseColor> colors)
{
    for (BaseColor color : colors)
        _available_colors.push_back(color);
}

void ResidentsMaker_CMDLine::initWithBaseColors ()
{
    for (auto& x : _colorrs_map)
    {
        _available_colors.push_back(x.first);
    }
}

ColorInfo ResidentsMaker_CMDLine::askForGroupColor (int groupIdx)
{
    std::vector<std::string> colorStrings = {};
    for (BaseColor color : _available_colors)
        colorStrings.push_back(_colorrs_map[color][Mood::neutral]._base_name);

    std::vector<std::string> number = {" first", " second", " third", " fourth"};
    std::string prompt = _which_group_color_prompt.insert(30, number[groupIdx]);
    int colorIdx = _ui.menu(prompt, colorStrings);
    return _colorrs_map[_available_colors[colorIdx]][Mood::neutral];
}

double ResidentsMaker_CMDLine::askForHappinessGoalForGroup (std::string color)
{
    Question_Double question = createQuestionGroupHappiness(color);
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stod(question.getAnswer());
    else
        throw _group_happiness_failure.insert(56, color + " ");
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
    else
        throw _how_many_residents_failure.insert(48 , color + " ");
}

int ResidentsMaker_CMDLine::askForGroupResidentType (
    std::string color, 
    std::vector<ResidentsFactory*> 
    residentsFactories
)
{
    std::vector<std::string> factoryNames = getFactoryNames(residentsFactories);
    return _ui.menu(_which_type_prompt.insert(24, color + " "), factoryNames);
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
    std::string origPrompt = _how_many_residents_orig_prompt.insert(
        51, 
        color + " "
    );
    origPrompt = origPrompt.insert(
        origPrompt.size() - 3,
        std::to_string(count)
    );

    return Question_Int{
        1,
        1,
        count,
        origPrompt,
        _how_many_residents_type_prompt,
        _how_many_residents_range_prompt
    };
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupHappiness (std::string color)
{
    return Question_Double{
        2,
        0.0,
        1.0,
        _group_happiness_orig_prompt.insert(55, color + " "),
        _group_happiness_range_prompt,
        _group_happiness_range_prompt};
}

std::vector<std::string> ResidentsMaker_CMDLine::getFactoryNames (
    std::vector<ResidentsFactory*> residentsFactories)
{
    std::vector<std::string> residentsFactoryNames = {};
    for (ResidentsFactory* residentFactory: residentsFactories)
    {
        residentsFactoryNames.push_back(residentFactory->toString());
    }
    return residentsFactoryNames;
}






