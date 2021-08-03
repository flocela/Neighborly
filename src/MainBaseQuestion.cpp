#include "MainBaseQuestion.h"
#include <vector>
#include <string>

bool MainBaseQuestion::askUserToUsePremadeExamples ()
{
    return ui.menu(
        "First time? Maybe just run one of the examples. ",
        std::vector<std::string>{"Use an example. ", "Choose my own simulation. "}
    ); 
}