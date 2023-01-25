#include "RandSeedGetter.h"

using namespace std;
Question_Int RandSeedGetter::createQuestionForSeed ()
{
    string copySeedFailureStr = _seed_failure_str;
    copySeedFailureStr.insert(68, _seed_fallback);

    return Question_Int{
        0,
        1,
        numeric_limits<int>::max(),
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
    return stoi(ui.getAnswer(question));
}