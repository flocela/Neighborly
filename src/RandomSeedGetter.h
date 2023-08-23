#ifndef RANDOMSEEDGETTER__H
#define RANDOMSEEDGETTER__H

#include "Question_Int.h"
#include "UI.h"

// Ask user for a random integer for the random number generator in the simulation.
class RandomSeedGetter
{
public:

    static int getSeedFromUser (const UI& ui);

private:

    static Question_Int createQuestionForSeed ();

    // If can not get a seed for random generator, then use _seed_fallback.
    static const int _seed_fallback;

    static const std::string _seed_orig_prompt;

};

#endif