#include "ResidentsMaker_CMDLine.h"
#include <iostream>



std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeBaseResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount,
    std::set<Color> colors // these are the colors that the residents can be.
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
        Color::red);

    auto residentsGroup2 = residentsFactories[0]->createBaseResidents (
        _ui,
        13,
        50,
        0.5,
        Color::green);

    for (auto& r: residentsGroup1)
        residents.emplace_back(std::move(r));

    for (auto& r: residentsGroup2)
        residents.emplace_back(std::move(r));
    
    return residents;
}

std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount,
    std::set<Color> colors

)
{   
    if (colors.size() < 3)
        throw std::invalid_argument( "colorInfos must have at least 3 colors.");
    initColors(colors);
    std::vector<std::unique_ptr<Resident>> residents;

    int numOfGroups = askForNumOfGroupsOfResidents();
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<numOfGroups; ++ii)
    {
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;
        if (allowedNumOfResidents <= 0)
            break;
        
        ColorInfo colorInfo = askForGroupColor(ii);

        int numOfResidents = askForNumOfResidents(
            allowedNumOfResidents, 
            colorInfo._my_string
        );
        
        int choice = askForGroupResidentType(
            colorInfo._my_string, 
            residentsFactories
        );

        double happinessGoal = askForHappinessGoalForGroup(colorInfo._my_string);

        auto newResidents = residentsFactories[choice]->createResidents(
            _ui,
            numOfResidentsCreated,
            numOfResidents,
            happinessGoal,
            colorInfo._my_color);

        for (auto& r: newResidents)
            residents.emplace_back(std::move(r));

        numOfResidentsCreated += newResidents.size();
        updateAvailableColors(colorInfo._my_color);
    }
    
    return residents;
}

void ResidentsMaker_CMDLine::initColors (std::set<Color> colors)
{
    for (Color color : colors)
        _available_colors.push_back(color);
}

ColorInfo ResidentsMaker_CMDLine::askForGroupColor (int groupIdx)
{
    std::vector<std::string> colorStrings = {};
    for (Color color : _available_colors)
        colorStrings.push_back(_the_color_Infos[color]._my_string);

    std::vector<std::string> number = {" first", " second", " third", " fourth"};
    std::string prompt = _which_group_color_prompt.insert(30, number[groupIdx]);
    int colorIdx = _ui.menu(prompt, colorStrings);
    return _the_color_Infos[_available_colors[colorIdx]];
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
        34, 
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

void ResidentsMaker_CMDLine::updateAvailableColors(Color color)
{
    std::size_t ii = 0;
    for (;ii < _available_colors.size(); ++ii)
    {
        if (_available_colors[ii] == color)
            break;
    }
    _available_colors.erase(_available_colors.begin() + static_cast<int>(ii));
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






