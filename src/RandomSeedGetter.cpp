#include "RandomSeedGetter.h"

#include <limits>

using namespace std;

const int RandomSeedGetter::_seed_fallback = 1;

const string RandomSeedGetter::_seed_orig_prompt = 
    "\nEnter the seed number for the random number generator in the simulation. "
    " Must be a positive integer. _";

int RandomSeedGetter::getSeedFromUser (const UI& ui)
{
    Question_Int_II question = createQuestionForSeed();
    return stoi(ui.getAnswer(question));
}

Question_Int_II RandomSeedGetter::createQuestionForSeed ()
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
