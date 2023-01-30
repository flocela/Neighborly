#include "RandSeedGetter.h"

using namespace std;
Question_Int RandSeedGetter::createQuestionForSeed ()
{
    return Question_Int{
        0,
        1,
        numeric_limits<int>::max(),
        _seed_fallback,
        _seed_orig_prompt,
        "seed number for the random generator"
    };
}

int RandSeedGetter::makeSeedForRand (const UI& ui)
{
    Question_Int question = createQuestionForSeed();
    return stoi(ui.getAnswer(question));
}