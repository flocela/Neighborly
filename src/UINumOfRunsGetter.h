#ifndef UINUMOFRUNSGETTER__H
#define UINUMOFRUNSGETTER__H

#include <string>
#include "Question_Int.h"
#include "UI.h"

// UINumOfRunsGetter is used to ask the user how many runs are in the simulation.
// Uses the command line interface.
class UINumOfRunsGetter
{ 

public:

    static int getNumOfRunsFromUser (const UI& ui, int maxNumOfRuns);

private:

    // if can not get num of runs from user, then use _fall_back_num_of_runs
    static const int _fallback_num_of_runs;

    static const std::string _num_of_runs_orig_prompt;
    
    static const std::string _num_of_runs_type_prompt;

    static const std::string _num_of_runs_range_prompt;

    static const std::string _num_of_runs_failure_str;

    static Question_Int createQuestionForNumOfRuns (int maxNumOfRuns);

};

#endif