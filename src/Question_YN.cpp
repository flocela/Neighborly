#include "Question_YN.h"

Question_YN::Question_YN ( int id,
                           std::string origPrompt):
    _ID{id}, _orig_prompt{origPrompt}
{
    _next_prompt = &_orig_prompt;
}

int Question_YN::getID()
{
    return _ID;
}

std::string Question_YN::getPrompt ()
{
    return *_next_prompt;
}

bool Question_YN::tryAnswer (std::string ans)
{
    if (ans == "YES"  ||
        ans == "Yes"  ||
        ans == "yes"  ||
        ans == "yeah" ||
        ans == "Yeah" ||
        ans == "Y"    || 
        ans == "y")
    {
        _valid_answer = true;
        _answer == "Y";
    }
    else if (ans == "NO"    ||
             ans == "No"    ||
             ans == "no"    ||
             ans == "Nope"  ||
             ans == "nope"  ||
             ans == "N"     ||
             ans == "n")
    {
        _valid_answer = true;
        _answer = "N";
    }
    else
    {
        _next_prompt = &_invalid_prompt;
        _valid_answer = false;
    }
    return _valid_answer;
}

bool Question_YN::hasValidAnswer ()
{
    return _valid_answer;
}

std::string Question_YN::getAnswer ()
{
    if (hasValidAnswer() == false)
        throw ("There is no answer yet.");
    return _answer;
}