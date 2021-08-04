#include "RandSeedMaker_CMDLine.h"

Question_Int RandSeedMaker_CMDLine::createQuestionForSeed ()
{
    return Question_Int{
        0,
        1,
        2147483647,
        _seed_orig_prompt,
        _seed_type_prompt,
        _seed_range_prompt
    };
}

int RandSeedMaker_CMDLine::makeSeedForRand ()
{
    Question_Int question = createQuestionForSeed();
    _ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
        throw _seed_failure_str;
}