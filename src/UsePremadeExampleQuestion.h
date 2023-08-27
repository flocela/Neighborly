#ifndef USE_PREMADE_EXAMPLE_QUESTION__H
#define USE_PREMADE_EXAMPLE__H

#include "UI.h"

// Asks user whether they would like to use the premade examples to create a simulation or
// be asked questions to make a specific simulation.
class UsePremadeExampleQuestion
{
    
public:

    bool askUser (const UI& ui);

};

#endif