#include "UINumOfRunsGetter.h"

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
        2147483647, // TODO ask the compiler how big an int is
        _num_of_runs_orig_prompt,
        _num_of_runs_type_prompt,
        _num_of_runs_range_prompt
    };
}
