#include "RandomSeedGetter.h"

using namespace std;

const int RandomSeedGetter::_seed_fallback = 1;

const string RandomSeedGetter::_seed_orig_prompt = 
    "\nEnter the seed number for the random number generator in the simulation. "
    " Must be a positive integer.";

int RandomSeedGetter::getSeedFromUser (const UI& ui)
{
    Question_Int question = createQuestionForSeed();
    return stoi(ui.getAnswer(question));
}

Question_Int RandomSeedGetter::createQuestionForSeed ()
{
    return Question_Int{
        0,
        1,
        numeric_limits<int>::max(),
        true, 
        true,
        _seed_fallback,
        _seed_orig_prompt,
        "seed number for the random generator"
    };
}
