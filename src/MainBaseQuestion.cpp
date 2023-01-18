#include "MainBaseQuestion.h"
#include <vector>
#include <string>

bool MainBaseQuestion::askUserToUsePremadeExamples (const UI& ui)
{
    int userResult = ui.menu(
        "\nFirst time here? Maybe just run one of the examples. Type 1 or 2.",
        std::vector<std::string>{"Use an example. ", "Choose my own simulation. "},
        0
    );
    return (0 == userResult); 
}