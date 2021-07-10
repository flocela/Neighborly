#include "ResidentsMaker_CMDLine.h"
#include <iostream>



std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeBaseResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount
)
{   
    (void) maxResidentCount;
    initColors();
    std::vector<std::unique_ptr<Resident>> residents;

    auto newResidents = residentsFactories[0]->createBaseResidents(
            _ui,
            0,
            30,
            0.5,
            Color::red);
    for (auto& r: newResidents)
        {
            residents.emplace_back(std::move(r));
        }
    
    auto newResidents2 = residentsFactories[0]->createBaseResidents(
            _ui,
            13,
            50,
            0.5,
            Color::green);
    for (auto& r: newResidents2)
        {
            residents.emplace_back(std::move(r));
        }
    
    return residents;
}

std::vector<std::unique_ptr<Resident>> ResidentsMaker_CMDLine::makeResidents (
    std::vector<ResidentsFactory*> residentsFactories,
    int maxResidentCount
)
{   
    initColors();
    std::vector<std::unique_ptr<Resident>> residents;

    int numOfGroups = askForNumOfGroupsOfResidents();
    
    int numOfResidentsCreated = 0;
    for (int ii=0; ii<numOfGroups; ++ii)
    {
        int allowedNumOfResidents = maxResidentCount - numOfResidentsCreated;
        if (allowedNumOfResidents <= 0)
            break;
        
        ColorInfo color = askForGroupColor(ii);

        int numOfResidents = askForNumOfResidents(
            allowedNumOfResidents, 
            color._my_string
        );
        
        int choice = askForGroupResidentType(
            color._my_string, 
            residentsFactories
        );

        double happinessGoal = askForHappinessGoalForGroup(color._my_string);

        auto newResidents = residentsFactories[choice]->createResidents(
            _ui,
            numOfResidentsCreated,
            numOfResidents,
            happinessGoal,
            color._my_color);

        for (auto& r: newResidents)
        {
            residents.emplace_back(std::move(r));
        }

        numOfResidentsCreated += newResidents.size();
        updateAvailableColors(color);
        std::cout << "ResidentsMaker_CMDLine line 49 residents.size(): " << residents.size() << std::endl;
    }
    
    return residents;
}

void ResidentsMaker_CMDLine::initColors ()
{
    for (ColorInfo color : _the_colors)
    {
        _colors.push_back(color);
    }
}


ColorInfo ResidentsMaker_CMDLine::askForGroupColor (int groupIdx)
{
    std::vector<std::string> colorStrings = {};
    for (ColorInfo color : _colors)
    {
        colorStrings.push_back(color._my_string);
    }
    std::vector<std::string> number = {" first", " second", " third", " fourth"};
    std::string prompt = _which_group_color_prompt.insert(30, number[groupIdx]);
    int colorIdx = _ui.menu(prompt, colorStrings);
    return _colors[colorIdx];
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

int ResidentsMaker_CMDLine::askForGroupResidentType (std::string color, 
                                                     std::vector<ResidentsFactory*> 
                                                        residentsFactories)
{
    std::vector<std::string> factoryNames = getFactoryNames(residentsFactories);
    return _ui.menu(_which_type_prompt.insert(24, color + " "), factoryNames);
}

Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidentGroups()
{
    return Question_Int{0,
                        1,
                        3, 
                        _how_many_groups_orig_prompt,
                        _how_many_groups_type_prompt,
                        _how_many_groups_range_prompt};
}

Question_Int ResidentsMaker_CMDLine::createQuestionHowManyResidents (
    int count, 
    std::string color
)
{   std::string origPromptFinalized = _how_many_residents_orig_prompt.insert(34, color + " ");
    int insertionPoint = origPromptFinalized.size() - 3;
    origPromptFinalized = origPromptFinalized.insert( insertionPoint, std::to_string(count));

    return Question_Int{1,
                        1,
                        count,
                        origPromptFinalized,
                        _how_many_residents_type_prompt,
                        _how_many_residents_range_prompt};
}

Question_Double ResidentsMaker_CMDLine::createQuestionGroupHappiness (std::string color)
{
    return Question_Double{2,
                           0.0,
                           1.0,
                           _group_happiness_orig_prompt.insert(55, color + " "),
                           _group_happiness_range_prompt,
                           _group_happiness_range_prompt};
}

void ResidentsMaker_CMDLine::updateAvailableColors(ColorInfo color)
{
    std::size_t ii = 0;
    for (;ii < _colors.size(); ++ii)
    {
        if (_colors[ii]._my_string == color._my_string)
            break;
    }
    _colors.erase(_colors.begin() + static_cast<int>(ii));
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






