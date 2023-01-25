#include "UI_CMDLine.h"
#include <iostream>
#include <sstream>

#include "Question_Int.h"

using namespace std;

UI_CMDLine:: UI_CMDLine (int maxNumOfTries)
{
    _max_num_of_tries = maxNumOfTries;
}

string UI_CMDLine::getAnswer (Question& question) const
{
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !question.hasValidAnswer())
    {   cout << question.getPrompt();
        cin >> answer;
        question.tryAnswer(answer);
        tries++;
    }
    cout << "UICMD line : " << answer << ", " << question.getFallback() << endl;
    if (!question.hasValidAnswer())
    {
        cout << question.getFailedResponse() << endl;
        return question.getFallback();
    }
    return answer;
}

int UI_CMDLine::menu (
    string prompt,
    vector<string> items, 
    int fallBack,
    string failureResponse
) const
{  
    int size = items.size();
    stringstream ssPrompt;
    ssPrompt << prompt << endl;
    for (int ii=0; ii<size; ++ii)
    {
        ssPrompt << ii+1 << ")" << items[ii] << " ";
    }
    ssPrompt << endl;

    stringstream ssWrongType;
    ssWrongType << "Please enter a whole number like 2.  ";
    ssWrongType << ssPrompt.str();

    stringstream ssInRange;
    ssInRange << "Please enter a number between 1 and ";
    ssInRange << items.size() << ".  ";
    ssInRange << ssPrompt.str();

    string copyMenuItemFailure = _menu_item_failure;
    copyMenuItemFailure.insert(57, _fallback_menu_item);

    Question_Int chooseMenuItem{
        1,
        1,
        size,
        ssPrompt.str(),
        ssWrongType.str(),
        ssInRange.str(),
        _fallback_menu_item,
        copyMenuItemFailure};
    
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !chooseMenuItem.hasValidAnswer())
    {   cout << chooseMenuItem.getPrompt();
        cin >> answer;
        chooseMenuItem.tryAnswer(answer);
        tries++;
    }

    if (tries >= _max_num_of_tries)
    {
        cout << failureResponse << endl;
        return fallBack;
    }
    // items are numbered starting with one for the user, but items vector is zero-index based
    return stoi(answer) - 1;
}

void UI_CMDLine::print (string str) const
{
    cout << str << endl;
}
