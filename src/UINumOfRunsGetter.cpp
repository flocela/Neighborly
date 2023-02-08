#include "UINumOfRunsGetter.h"

using namespace std;

int UINumOfRunsGetter::getNumOfRunsFromUser (const UI& ui, int maxNumOfRuns)
{
    Question_Int question = createQuestionForNumOfRuns (maxNumOfRuns);
    return stoi(ui.getAnswer(question));
}

Question_Int UINumOfRunsGetter::createQuestionForNumOfRuns (int maxNumOfRuns)
{
    return Question_Int{
        0,
        0,
        maxNumOfRuns,
        _fallback_num_of_runs,
        _num_of_runs_orig_prompt,
        "number of runs"
    };
}
