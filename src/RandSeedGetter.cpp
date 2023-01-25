#include "RandSeedGetter.h"

using namespace std;
Question_Int RandSeedGetter::createQuestionForSeed ()
{
    string copySeedFailureStr = _seed_failure_str;
    copySeedFailureStr.insert(68, _seed_fallback);
    return Question_Int{
        0,
        1,
        2147483647, // Ask the compiler how big an int is
        _seed_orig_prompt,
        _seed_type_prompt,
        _seed_range_prompt,
        _seed_fallback,
        copySeedFailureStr

    };
}

int RandSeedGetter::makeSeedForRand (const UI& ui)
{
    Question_Int question = createQuestionForSeed();
    ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
        return stoi(_seed_fallback);
}