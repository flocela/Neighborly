#ifndef UINUMOFRUNSGETTER_H
#define UINUMOFRUNSGETTER_H

#include <string>
#include "Question_Int.h"
#include "UI_CMDLine.h"

/* UINumOfRunsGetter is used to ask the user how many runs should the simulation run.
   Uses the command line interface */
class UINumOfRunsGetter
{

public:
    int getNumOfRunsFromUser ();

private:
    UI_CMDLine _ui;

    // TODO max number of runs is determined by space in printergraphic
    // really, there is no max number of runs, but waiting for max_integer number of runs would be
    // a very long time
    int _max_num_of_runs = 200;

    // if can not get num of runs from user, then use _fall_back_num_of_runs
    std::string _fallback_num_of_runs = "20";

    Question_Int createQuestionForNumOfRuns ();

    std::string _num_of_runs_orig_prompt = 
        "\n How many runs should the simulation have? Must be a positive number. _";
    
    std::string _num_of_runs_type_prompt = 
        "Nope, that's not a positive whole number. _";

    std::string _num_of_runs_range_prompt = 
        "That's either too small or too large. Can not be less than"
            " 2,147,483,646. But really should be no more than 200. _";

    std::string _num_of_runs_failure_str = 
        "Could not determine the number of runs, will be using .";

};

#endif