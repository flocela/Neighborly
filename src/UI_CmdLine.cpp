#include <iostream>
#include <sstream>
#include "UI_CmdLine.h"
#include "Question_Int.h"

using namespace std;

UI_CmdLine:: UI_CmdLine (int maxNumOfTries): _max_num_of_tries{maxNumOfTries}
{}

string UI_CmdLine::getAnswer (Question&& question) const
{
    return getAnswer(question);
}

string UI_CmdLine::getAnswer (Question& question) const
{   
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !question.hasValidAnswer())
    {   cout << question.getPrompt();
        getline(cin >> ws, answer);
        question.tryAnswer(answer);
        tries++;
    }
    if (!question.hasValidAnswer())
    {   
        cout << question.getFailedResponse() << endl;
        return question.getFallback();
    }

    return answer;
}

int UI_CmdLine::menu (
    string prompt,
    vector<string> items, 
    int fallBack,
    string failureResponse
) const
{  
    // Create the original prompt.
    int size = items.size();
    stringstream ssPrompt;
    ssPrompt << prompt << endl;
    for (int ii=0; ii<size; ++ii)
    {
        ssPrompt << ii+1 << ")" << items[ii];
        if (size > 4)
        {
            ssPrompt << endl;
        }
        else
        {
            ssPrompt << " ";
        }
    }
    if (size > 4)
    {
        ssPrompt << "_";
    }
    else
    {
        ssPrompt << endl << "_";
    }
    
    // Create the range in the range prompt. (It has the original prompt appended to it.)
    stringstream ssInRange;
    ssInRange << _menu_range_prompt;
    ssInRange << items.size() << ". _";

    // Create invalid prompt with the number of items to the invalid prompt.
    string invalidPrompt = insertIntoString(
        _menu_invalid_prompt,
        _menu_invalid_prompt.size()-3,
        to_string(size));

    // Create question.
    Question_Int chooseMenuItem{
        1,
        1,
        size,
        true,
        true,
        _fallback_menu_item,
        ssPrompt.str(),
        _menu_type_prompt,
        ssInRange.str(),
        invalidPrompt,
        insertIntoString(
            _menu_item_failure,
            _menu_item_failure.size() - 3,
            to_string(_fallback_menu_item))
    };
    
    // Get answer from user.
    int tries = 0;
    string answer = "xx";
    while (tries < _max_num_of_tries && !chooseMenuItem.hasValidAnswer())
    {   
        cout << chooseMenuItem.getPrompt();
        getline(cin >> ws, answer);
        chooseMenuItem.tryAnswer(answer);
        tries++;
    }

    if (!chooseMenuItem.hasValidAnswer())
    {
        cout << failureResponse << endl;
        return fallBack;
    }

    // Items are numbered starting with one for the user, but items vector is zero-index based.
    return stoi(answer) - 1;
}

std::string UI_CmdLine::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}
