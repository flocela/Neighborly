#ifndef SIMULATION_GETTER__H
#define SIMULATION_GETTER__H

#include <memory>
#include <vector>
#include <unordered_set>
#include "City.h"
#include "Question_Double.h"
#include "Question_Int.h"
#include "Resident.h"
#include "Simulator.h"
#include "UI.h"

// Shows a menu of simulators for user to choose from.
class SimulatorGetter
{

public:

    SimulatorGetter (City* city, std::unordered_set<Resident*> residents);
    SimulatorGetter (const SimulatorGetter& o) = default;
    SimulatorGetter& operator= (const SimulatorGetter& o) = default;
    SimulatorGetter (SimulatorGetter&& o) noexcept = default;
    SimulatorGetter& operator= (SimulatorGetter&& o) noexcept= default;
    ~SimulatorGetter () noexcept = default;

    std::unique_ptr<Simulator> getSimulatorFromUser (const UI& ui);

private:

    City* _city = nullptr;
    std::unordered_set<Resident*> _residents{};
    double _percent_residents_to_move = 20.0;
    size_t _number_of_houses_to_look_at = 5;

    Question_Double createQuestionForPercentOfResidentsThatMustMove ();
    Question_Int createQuestionForNumberOfHousesToChooseFrom ();

    const std::string _simulator_menu_prompt =
        "\nWhich simulator would you like? In each run a percentage of residents are"
        " randomly chosen to move. For each of these residents, a given number of houses are"
        " chosen, and the resident chooses which one makes them happiest. If there are no houses"
        " within the resident's allowable movement distance, then the resident does not move.\n"
        " In Simulator A, if the chosen house does not make them happier than their current house"
        " then the resident does not move.\n In Simulator B, if the chosen house does not meet the"
        " resident's happiness goal then the resident does not move.";
        
    const int _simulator_fallback = 1;
    const std::vector<std::string> _simulator_menu_items = {"Simulator A", "Simulator B"};
    const std::string _simulator_menu_failure_response =
        "Could not tell which simulator you wanted, will choose Simulator B.";

    const std::string _simulator_b_percentage_prompt =
        "At each run a percentage of all residents are chosen to move."
        " What should that percentage be?";
    const std::string _simulator_b_percentage_value =
        "percentage of residents moved per run";

    const std::string _simulator_b_number_of_houses_to_choose_from_prompt =
        "The residents will choose from a number of houses."
        " How many houses should they choose from?";
    const std::string _simulator_b_number_of_houses_to_choose_from_value =
        "number of housese to choose from";

};

#endif