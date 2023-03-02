#include "RandSeedGetter.h"

using namespace std;

int RandSeedGetter::makeSeedForRand (const UI& ui)
{
    Question_Int_II question = createQuestionForSeed();
    return stoi(ui.getAnswer(question));
}

Question_Int_II RandSeedGetter::createQuestionForSeed ()
{
    return Question_Int_II{
        0,
        1,
        numeric_limits<int>::max(),
        _seed_fallback,
        _seed_orig_prompt,
        "seed number for the random generator"
    };
}
