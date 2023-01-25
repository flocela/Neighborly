#include "Question_YN.h"

using namespace std;

Question_YN::Question_YN (
    int id,
    string origPrompt,
    string fallback,
    string failedPrompt):
    _ID{id},
    _orig_prompt{origPrompt},
    _fallback{fallback}
{
    _invalid_prompt.insert(33, _orig_prompt);
    if (failedPrompt == "")
    {
        _failed_prompt.insert(62, _fallback);
    }
    else
    {
        _failed_prompt = failedPrompt;
    }
    _next_prompt = &_orig_prompt;
}

int Question_YN::getID() const
{
    return _ID;
}

string Question_YN::getPrompt () const
{
    return *_next_prompt;
}

bool Question_YN::hasValidAnswer () const
{
    return _valid_answer;
}

string Question_YN::getAnswer () const
{
    if (hasValidAnswer() == false)
        return _fallback;
    return _answer;
}

string Question_YN::getFallback () const
{
    return _fallback;
}

string Question_YN::getFailedResponse () const
{
    return _failed_prompt;
}

bool Question_YN::tryAnswer (string ans)
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