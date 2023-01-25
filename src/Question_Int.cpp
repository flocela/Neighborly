#include "Question_Int.h"
#include <stdexcept>

using namespace std;

Question_Int::Question_Int (
    int id,
    int min, 
    int max,
    string origPrompt,
    string wrongTypePrompt, 
    string inRangePrompt,
    string fallback,
    string failedPrompt
): _ID{id},
   _min{min},
   _max{max},
   _orig_prompt{origPrompt},
   _type_prompt{wrongTypePrompt},
   _range_prompt{inRangePrompt},
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
    _valid_answer = false;
}

int Question_Int::getID() const
{
    return _ID;
}

string Question_Int::getPrompt () const
{
    return *_next_prompt;
}

bool Question_Int::hasValidAnswer () const
{   
    return _valid_answer;
}

string Question_Int::getAnswer () const
{
    if (hasValidAnswer() == false)
        return _fallback;
    return to_string(_answer);
}

string Question_Int::getFallback () const
{
    return _fallback;
}

string Question_Int::getFailedResponse () const
{
    return _failed_prompt;
}

bool Question_Int::tryAnswer (string ans)
{   
    int intAnswer;
    try {
        intAnswer = stoi(ans);
    }
    catch(invalid_argument& e)
    {
        _next_prompt = &_type_prompt;
        return false;
    }
    catch(...)
    { 
        _next_prompt = &_invalid_prompt;
        return false;
    }
    if (intAnswer < _min || intAnswer > _max)
    {
        _next_prompt = &_range_prompt;
        return false;
    }
    _valid_answer = true;
    _answer = intAnswer;
    return _valid_answer;
}