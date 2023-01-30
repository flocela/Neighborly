#ifndef RANDSEEDGETTER_H
#define RANDSEEDGETTER_H

#include <limits>
#include <string>
#include "Question_Int.h"
#include "UI.h"

class RandSeedGetter
{
    public:
        int makeSeedForRand (const UI& ui);

    private:
        Question_Int createQuestionForSeed ();

        // if can not get a seed for random generator, then use _seed_fallback
        int _seed_fallback = 1;

        std::string _seed_orig_prompt = 
            "\nEnter the seed number for the random number generator in the simulations? "
            " Must be a positive integer. _";
        std::string _seed_type_prompt = 
            "Nope, that's not a positive whole number. _";
        std::string _seed_range_prompt = 
            "That's either too small or too large. Should be less than " + 
            std::to_string(std::numeric_limits<int>::max()) + " . _";
        std::string _seed_failure_str = 
            "Could not determine random number seed from the user, will be using .";

};

#endif