#ifndef SIMULATION_GETTER_H
#define SIMULATION_GETTER_H

#include <memory>
#include <vector>
#include <unordered_set>
#include "City.h"
#include "Question_Double.h"
#include "Question_Int.h"
#include "Resident.h"
#include "Simulator.h"
#include "UI.h"

class SimulatorGetter
{
public:
    SimulatorGetter (City* city, std::unordered_set<Resident*> residents);
    SimulatorGetter (const SimulatorGetter& o) = default;
    SimulatorGetter& operator= (const SimulatorGetter& o) = default;
    SimulatorGetter (SimulatorGetter&& o) noexcept = default;
    SimulatorGetter& operator= (SimulatorGetter&& o) noexcept= default;
    ~SimulatorGetter() = default;

    std::unique_ptr<Simulator> getSimulatorFromUser (const UI& ui);

private:
    City* _city = nullptr;
    std::unordered_set<Resident*> _residents{};
    double _percent_residents_to_move = 20.;
    int _number_of_houses_to_look_at = 5;

    Question_Double createQuestionForPercentOfResidentsThatMustMove ();
    Question_Int createQuestionForNumberOfHousesToChooseFrom ();

    const std::string _simulator_menu_prompt =
        "\nWhich simulator would you like? In each run of Simulator A, all residents who are unhappy"
        " are given the opportunity to move to a house that will make them happier.\n"
        "In each run of Simulator B, a percentage of residents are randomly chosen and"
        " forced to move. A given number of houses are chosen, and the resident chooses"
        " which one makes them happiest.\n";
    const int _simulator_fallback = 1;
    const std::vector<std::string> _simulator_menu_items = {"Simulator A", "Simulator B"};
    const std::string _simulator_menu_failure_response =
        "Could not tell which simulator you wanted, will choose Simulator B.";

    const std::string _simulator_b_percentage_prompt =
        "Simulator B chooses a percentage of all residents and forces them to move"
        " at each run. What should that percentage be? _";
    const std::string _simulator_b_percentage_value =
        "percentage of residents moved per run";

    const std::string _simulator_b_number_of_houses_to_choose_from_prompt =
        "The chosen residents will choose from a number of houses."
        " How many houses should they choose from? _";
    const std::string _simulator_b_number_of_houses_to_choose_from_value =
        "number of housese to choose from";

};

#endif