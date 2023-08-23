#include "CityState_Simple.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"
#include "SimulatorGetter.h"

using namespace std;

SimulatorGetter::SimulatorGetter (City* city, unordered_set<Resident*> residents):
    _city{city},
    _residents{residents},
    _percent_residents_to_move{20},
    _number_of_houses_to_look_at{_city->getNumOfHouses()/5}
    {}

Question_Double SimulatorGetter::createQuestionForPercentOfResidentsThatMustMove ()
{
    return Question_Double{
        0,
        0.0,
        100.0,
        true,
        true,
        _percent_residents_to_move,
        _simulator_b_percentage_prompt,
        _simulator_b_percentage_value
    };
}

Question_Int SimulatorGetter::createQuestionForNumberOfHousesToChooseFrom ()
{
    return Question_Int{
        1,
        1,
        static_cast<int>(_city->getNumOfHouses()),
        true,
        true,
        static_cast<int>(_number_of_houses_to_look_at),
        _simulator_b_number_of_houses_to_choose_from_prompt,
        _simulator_b_number_of_houses_to_choose_from_value
    };
}

unique_ptr<Simulator> SimulatorGetter::getSimulatorFromUser (const UI& ui)
{
    // Choose Simulator_Basic_A or Simulator_Basic_B
    int chosenSimulator = ui.menu(
        _simulator_menu_prompt, 
        _simulator_menu_items,
        _simulator_fallback,
        _simulator_menu_failure_response
    );

    if (chosenSimulator == 0) // Basic_A
    {
        _percent_residents_to_move =
            stod(ui.getAnswer(createQuestionForPercentOfResidentsThatMustMove()));

        _number_of_houses_to_look_at = 
            stoi(ui.getAnswer(createQuestionForNumberOfHousesToChooseFrom()));

        return make_unique<Simulator_Basic_A>(
            _city,
            _residents,
            _percent_residents_to_move,
            _number_of_houses_to_look_at,
            make_unique<CityState_Simple>(_city)
        );
    }
    else if (chosenSimulator == 1) // Basic_B
    {
        _percent_residents_to_move =
            stod(ui.getAnswer(createQuestionForPercentOfResidentsThatMustMove()));

        _number_of_houses_to_look_at = 
            stoi(ui.getAnswer(createQuestionForNumberOfHousesToChooseFrom()));

        return make_unique<Simulator_Basic_B>(
            _city,
            _residents,
            _percent_residents_to_move,
            _number_of_houses_to_look_at,
            make_unique<CityState_Simple>(_city)
        );
    }
    else //default is Basic_B
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