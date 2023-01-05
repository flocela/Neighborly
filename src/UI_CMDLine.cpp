#include "UI_CMDLine.h"
#include <iostream>
#include <sstream>

#include "Question_Int.h"

UI_CMDLine:: UI_CMDLine (int maxNumOfTries)
{
    _max_num_of_tries = maxNumOfTries;
}

std::string UI_CMDLine::getAnswer (Question& question)
{
    int tries = 0;
    std::string answer = "xx";
    while (tries < _max_num_of_tries && !question.hasValidAnswer())
    {   std::cout << question.getPrompt();
        std::cin >> answer;
        question.tryAnswer(answer);
        tries++;
    }
    return answer;
}

int UI_CMDLine::menu (std::string prompt, std::vector<std::string> items) 
{  
    int size = items.size();
    std::stringstream ssPrompt;
    ssPrompt << prompt << std::endl;
    for (int ii=0; ii<size; ++ii)
    {
        ssPrompt << ii+1 << ")" << items[ii] << " ";
    }
    ssPrompt << std::endl;

    std::stringstream ssWrongType;
    ssWrongType << "Please enter a whole number like 2.  ";
    ssWrongType << ssPrompt.str();

    std::stringstream ssInRange;
    ssInRange << "Please enter a number between 1 and ";
    ssInRange << items.size() << ".  ";
    ssInRange << ssPrompt.str();

    Question_Int chooseMenuItem{1,
                                1,
                                size,
                                ssPrompt.str(),
                                ssWrongType.str(),
                                ssInRange.str()};
    
    int tries = 0;
    std::string answer = "xx";
    while (tries < 4 && !chooseMenuItem.hasValidAnswer())
    {   std::cout << chooseMenuItem.getPrompt();
        std::cin >> answer;
        chooseMenuItem.tryAnswer(answer);
        tries++;
    }
    if (tries >= 4)
        throw "User would not choose a menu item properly.";
    
    // items are numbered starting with one for the user, but items vector is zero-index based
    return stoi(answer) - 1;
}

void UI_CMDLine::print (std::string str)
{
    std::cout << str << std::endl;
}
