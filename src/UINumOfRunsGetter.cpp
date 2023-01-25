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
    string copyNumOfRunsFailure = _num_of_runs_failure_str;
    copyNumOfRunsFailure.insert(54, _fallback_num_of_runs);
    return Question_Int{
        0,
        0,
        _max_num_of_runs, // TODO ask the compiler how big an int is
        _num_of_runs_orig_prompt,
        _num_of_runs_type_prompt,
        _num_of_runs_range_prompt,
        _fallback_num_of_runs,
        copyNumOfRunsFailure
    };
}
