#include "UINumOfRunsGetter.h"

using namespace std;

const int UINumOfRunsGetter::_fallback_num_of_runs = 20;

const std::string UINumOfRunsGetter::_num_of_runs_orig_prompt = 
        "\n How many runs should the simulation have? Must be a positive number. _";
    
const std::string UINumOfRunsGetter::_num_of_runs_type_prompt = 
        "Nope, that's not a positive whole number. _";

const std::string UINumOfRunsGetter::_num_of_runs_range_prompt = 
        "That's either too small or too large. Can not be less than"
            " 2,147,483,646. But really should be no more than 200. _";
        
const std::string UINumOfRunsGetter::_num_of_runs_failure_str = 
        "Could not determine the number of runs, will be using .";

int UINumOfRunsGetter::getNumOfRunsFromUser (const UI& ui, int maxNumOfRuns)
{
    Question_Int_II question = createQuestionForNumOfRuns (maxNumOfRuns);
    return stoi(ui.getAnswer(question));
}

Question_Int_II UINumOfRunsGetter::createQuestionForNumOfRuns (int maxNumOfRuns)
{
    return Question_Int_II{
        0,
        1,
        maxNumOfRuns,
        _fallback_num_of_runs,
        _num_of_runs_orig_prompt,
        "number of runs"
    };
}
