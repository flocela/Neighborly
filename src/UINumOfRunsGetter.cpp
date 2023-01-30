#include "UINumOfRunsGetter.h"

using namespace std;

int UINumOfRunsGetter::getNumOfRunsFromUser ()
{
    Question_Int question = createQuestionForNumOfRuns ();
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
    {
        throw _num_of_runs_failure_str;
    }
    

}

Question_Int UINumOfRunsGetter::createQuestionForNumOfRuns ()
{
    return Question_Int{
        0,
        0,
        _max_num_of_runs, // TODO ask the compiler how big an int is
        _fallback_num_of_runs,
        _num_of_runs_orig_prompt,
        "number of runs"
    };
}
