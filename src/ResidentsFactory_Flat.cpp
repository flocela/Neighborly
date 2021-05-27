#include "ResidentsFactory_Flat.h"
#include <limits>
#include "Resident_Flat.h"

std::string ResidentsFactory_Flat::toString ()
{
    return "Flat Residents Factory";
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_Flat::createResidents (
                                                            UI& ui, 
                                                            int firstID,
                                                            int count,
                                                            Color color)
{   
    Question_Double qHappinessGoal{1,
                                   0.0,
                                   1.0,
                                   _happinessGoalOrigPrompt,
                                   _happinessGoalTypePrompt,
                                   _happinessGoalRangePrompt};

    double happinessGoal = askUserForDouble(ui,
                                            qHappinessGoal,
                                            _happinessGoalFailure);
    
    return createResidents(ui, firstID, count, happinessGoal, color);
}

std::vector<std::unique_ptr<Resident>> ResidentsFactory_Flat::createResidents (
                                                            UI& ui,
                                                            int firstID, 
                                                            int count, 
                                                            double happinessGoal, 
                                                            Color color)
{   
    Question_Double qMovement{2,
                              0.0,
                              std::numeric_limits<double>::max(),
                              _movmentOrigPrompt,
                              _movementTypePrompt,
                              _movemenRangePrompt};

    Question_Double qHappinessValue{3,
                                     0.0,
                                     1.0,
                                     _happinessValueOrigPrompt,
                                     _happinessValueTypePrompt,
                                     _happinessValueRangePrompt};
    
    double movement = askUserForDouble(ui,
                                       qMovement,
                                       _movementRangeFailure);

    double happinessValue = askUserForDouble(ui,
                                             qHappinessValue,
                                             _happinessValueFailure);

    std::vector<std::unique_ptr<Resident>> residents = {};
    for ( int ii=0; ii<count; ++ii)
    {
        residents.push_back(
            std::make_unique<Resident_Flat>(firstID+ii,
                                            color,
                                            movement,
                                            happinessGoal,
                                            happinessValue));
    }
    return residents;
}

int ResidentsFactory_Flat::askUserForInt (UI& ui, 
                                              Question_Int question, 
                                              std::string failureString)
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

double ResidentsFactory_Flat::askUserForDouble (UI& ui, 
                                                 Question_Double question, 
                                                 std::string failureString)
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
