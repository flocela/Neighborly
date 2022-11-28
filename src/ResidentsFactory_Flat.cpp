#include "ResidentsFactory_Flat.h"
#include <limits>
#include "Resident_Flat.h"

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
    std::string curColBaseName = _colorrs_map[baseColor][Mood::neutral]._base_name;
    _happinessValueOrigPrompt.insert(132, curColBaseName + " ");
    Question_Double qHappinessValue{
        3,
        0.0,
        100.0,
        _happinessValueOrigPrompt,
        _happinessValueTypePrompt,
        _happinessValueRangePrompt
    };

    double happinessValue = askUserForDouble(
        ui,
        qHappinessValue,
        _happinessValueFailure
    );
    std::vector<std::unique_ptr<Resident>> residents = {};

    for ( int ii=0; ii<count; ++ii)
    {
        residents.push_back(
            std::make_unique<Resident_Flat>(
                firstID+ii,
                groupNumber,
                allowedMovement,
                happinessGoal,
                happinessValue
        ));
    }
    return residents;
}

int ResidentsFactory_Flat::askUserForInt (
    UI& ui, 
    Question_Int question, 
    std::string failureString
)
{
    ui.getAnswer(question);
    if (question.hasValidAnswer())
    {
        return std::stoi(question.getAnswer());
    }
    else
    {
        throw failureString;
    }
}

double ResidentsFactory_Flat::askUserForDouble (
    UI& ui, 
    Question_Double question, 
    std::string failureString
)
{
    ui.getAnswer(question);
    if (question.hasValidAnswer())
    {   
        return std::stod(question.getAnswer());
    }
    else
    {
        throw failureString;
    }
}
