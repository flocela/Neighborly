#include "ResidentsFactory_Flat.h"
#include <limits>
#include "Resident_Flat.h"

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
    std::string curColBaseName = _colorrs_map[baseColor][Mood::neutral]._base_name;
    std:: string copyHappinessValueOrig = _happinessValueOrigPrompt;
    copyHappinessValueOrig.insert(134, curColBaseName + " ");
    string copyHappinessFailure = _happinessValueFailure;
    copyHappinessFailure.insert(94, _fallback_happiness_value);

    Question_Double qHappinessValue{
        3,
        0.0,
        100.0,
        copyHappinessValueOrig,
        _happinessValueTypePrompt,
        _happinessValueRangePrompt,
        _fallback_happiness_value,
        copyHappinessFailure
    };

    double happinessValue = askUserForDouble(
        ui,
        qHappinessValue
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
    Question_Int question
)
{
    return stoi(ui.getAnswer(question));
}

double ResidentsFactory_Flat::askUserForDouble (
    UI& ui, 
    Question_Double question
)
{
    return stod(ui.getAnswer(question));
}
