#include "SimulatorGetter.h"

#include "CityState_Simple.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"

using namespace std;

SimulatorGetter::SimulatorGetter (City* city, unordered_set<Resident*> residents):
    _city{city},
    _residents{residents},
    _percent_residents_to_move{20},
    _number_of_houses_to_look_at{_city->getNumOfHouses()/5}
    {}

Question_Double_II SimulatorGetter::createQuestionForPercentOfResidentsThatMustMove ()
{
    return Question_Double_II{
        0,
        0.0,
        100.0,
        _percent_residents_to_move,
        _simulator_b_percentage_prompt,
        _simulator_b_percentage_value
    };
}

Question_Int_II SimulatorGetter::createQuestionForNumberOfHousesToChooseFrom ()
{
    return Question_Int_II{
        1,
        1,
        _city->getNumOfHouses(),
        _number_of_houses_to_look_at,
        _simulator_b_number_of_houses_to_choose_from_prompt,
        _simulator_b_number_of_houses_to_choose_from_value
    };
}

unique_ptr<Simulator> SimulatorGetter::getSimulatorFromUser (const UI& ui)
{
    int chosenSimulator = ui.menu(
        _simulator_menu_prompt, 
        _simulator_menu_items,
        _simulator_fallback,
        _simulator_menu_failure_response
    );
    if (chosenSimulator == 0) //Simulator A
    {
        return make_unique<Simulator_Basic_A>(
            _city,
            _residents
        );
    }
    else if (chosenSimulator == 1) // Simulator B
    {
        Question_Double_II qPercentOfResidentsThatMustMove =
            createQuestionForPercentOfResidentsThatMustMove();
        _percent_residents_to_move = stod(ui.getAnswer(qPercentOfResidentsThatMustMove));

        Question_Int_II qNumberOfHousesToChouseFrom = 
            createQuestionForNumberOfHousesToChooseFrom();
        _number_of_houses_to_look_at = 
            stoi(ui.getAnswer(qNumberOfHousesToChouseFrom));
        return make_unique<Simulator_Basic_B>(
            _city,
            _residents,
            _percent_residents_to_move,
            _number_of_houses_to_look_at,
            make_unique<CityState_Simple>(_city)
        );
    }
    else
    {
        return make_unique<Simulator_Basic_B>(
            _city,
            _residents,
            _percent_residents_to_move,
            _number_of_houses_to_look_at,
            make_unique<CityState_Simple>(_city)
        );
    }
    
}