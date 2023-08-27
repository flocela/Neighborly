#include <string>
#include <vector>
#include "UsePremadeExampleQuestion.h"

using namespace std;

bool UsePremadeExampleQuestion::askUser (const UI& ui)
{
    int userResult = ui.menu(
        "\nFirst time here? Maybe just run one of the examples. Type 1 or 2.",
        vector<string>{"Use an example. ", "Choose my own simulation. "},
        0,
        "Could not tell if you wanted to use the examples, will be using the examples."
    );
    return (0 == userResult); 
}