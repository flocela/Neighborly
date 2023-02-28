#ifndef RANDSEEDGETTER_H
#define RANDSEEDGETTER_H

#include <limits>
#include <string>
#include "Question_Int_II.h"
#include "UI.h"

class RandSeedGetter
{
    public:
        int makeSeedForRand (const UI& ui);

    private:
        Question_Int_II createQuestionForSeed ();

        // if can not get a seed for random generator, then use _seed_fallback
        int _seed_fallback = 1;

        std::string _seed_orig_prompt = 
            "\nEnter the seed number for the random number generator in the simulations. "
            " Must be a positive integer. _";

};

#endif