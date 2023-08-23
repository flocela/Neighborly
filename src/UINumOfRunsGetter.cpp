#include "UINumOfRunsGetter.h"

using namespace std;

const int UINumOfRunsGetter::_fallback_num_of_runs = 20;

const std::string UINumOfRunsGetter::_num_of_runs_orig_prompt = 
        "\nHow many runs should the simulation have? Must be a positive number.";

int UINumOfRunsGetter::getNumOfRunsFromUser (const UI& ui, int maxNumOfRuns)
{
    Question_Int question = createQuestionForNumOfRuns (maxNumOfRuns);
    return stoi(ui.getAnswer(question));
}

Question_Int UINumOfRunsGetter::createQuestionForNumOfRuns (int maxNumOfRuns)
{
    return Question_Int{
        0,
        1,
        maxNumOfRuns,
        true,
        true,
        _fallback_num_of_runs,
        _num_of_runs_orig_prompt,
        "number of runs"
    };
}
