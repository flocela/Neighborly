#include "UI_CMDLine.h"

#include <iostream>
#include <sstream>

#include "Question_Int.h"

using namespace std;

UI_CMDLine:: UI_CMDLine (int maxNumOfTries) : _max_num_of_tries{maxNumOfTries}
{}

string UI_CMDLine::getAnswer (Question&& question) const
{
    return getAnswer(question);
}

string UI_CMDLine::getAnswer (Question& question) const
{   
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !question.hasValidAnswer())
    {   cout << question.getPrompt();
        getline(cin >> ws, answer);
        question.tryAnswer(answer);
        tries++;
    }
    cout << "answer: " << answer << endl; // TODO delete later, when no longer manual testing
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
    // create the original prompt
    int size = items.size();
    stringstream ssPrompt;
    ssPrompt << prompt << endl;
    for (int ii=0; ii<size; ++ii)
    {
        ssPrompt << ii+1 << ")" << items[ii] << " ";
    }
    ssPrompt << endl;

    // create the in range prompt. (It has the original prompt appended to it.)
    stringstream ssInRange;
    ssInRange << _menu_range_prompt;
    ssInRange << items.size() << ".  ";
    ssInRange << ssPrompt.str();

    Question_Int chooseMenuItem{
        1,
        1,
        size,
        true,
        true,
        _fallback_menu_item,
        ssPrompt.str(),
        _menu_type_prompt + ssPrompt.str(),
        ssInRange.str(),
        _menu_invalid_prompt + ssPrompt.str(),
        insertIntoString(
            _menu_item_failure,
            _menu_item_failure.size() - 3,
            to_string(_fallback_menu_item))
    };
    
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !chooseMenuItem.hasValidAnswer())
    {   cout << chooseMenuItem.getPrompt();
        getline(cin >> ws, answer);
        chooseMenuItem.tryAnswer(answer);
        tries++;
    }

    if (!chooseMenuItem.hasValidAnswer())
    {
        cout << failureResponse << endl;
        return fallBack;
    }
    // items are numbered starting with one for the user, but items vector is zero-index based
    return stoi(answer) - 1;
}

std::string UI_CMDLine::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}
