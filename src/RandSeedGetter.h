#ifndef RANDSEEDGETTER_H
#define RANDSEEDGETTER_H

#include <string>
#include "Question_Int.h"
#include "UI_CMDLine.h"

class RandSeedGetter
{
    public:
        int makeSeedForRand ();

    private:
        UI_CMDLine _ui;
        Question_Int createQuestionForSeed ();

        std::string _seed_orig_prompt = 
            "\nWhat will be the seed for the random number generator be in the simulations? "
            " Must be a positive integer. ";
        std::string _seed_type_prompt = 
            "Nope, that's not a positive whole number. ";
        std::string _seed_range_prompt = 
            "That's either too small or too large. Should be less than"
            " 2,147,483,647. ";
        std::string _seed_failure_str = 
            "Could not determine what the random number seed should be from"
            " the user.";

};

#endif