#ifndef RANDOMSEEDGETTER_H
#define RANDOMSEEDGETTER_H

#include "Question_Int.h"
#include "UI.h"

class RandomSeedGetter
{
    public:
        static int getSeedFromUser (const UI& ui);

    private:
        static Question_Int createQuestionForSeed ();

        // If can not get a seed for random generator, then use _seed_fallback
        static const int _seed_fallback;

        static const std::string _seed_orig_prompt;

};

#endif