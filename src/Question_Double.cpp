#include <stdexcept>
#include "Question_Double.h"

using namespace std;

Question_Double::Question_Double (
    int id,
    double min, 
    double max,
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

int Question_Double::getID () const
{
    return _ID;
}

string Question_Double::getPrompt () const
{
    return *_next_prompt;
}

bool Question_Double::hasValidAnswer () const
{
    return _valid_answer;
}

string Question_Double::getAnswer () const
{
    if (hasValidAnswer() == false)
        return _fallback;
    return to_string(_answer);
}

string Question_Double::getFallback () const
{
    return _fallback;
}

string Question_Double::getFailedResponse () const
{
    return _failed_prompt;
}

bool Question_Double::tryAnswer (string ans)
{   
    double doubleAnswer;
    try {
        doubleAnswer = stod(ans);
    }
    catch(invalid_argument& e) // TODO combine these two catches since bodies are the same.
    {
        _next_prompt = &_type_prompt;
        return false;
    }
    catch(...)
    { 
        _next_prompt = &_invalid_prompt;
        return false;
    }
    if (doubleAnswer < _min || doubleAnswer > _max)
    {
        _next_prompt = &_range_prompt;
        return false;
    }
    _valid_answer = true;
    _answer = doubleAnswer;
    return true;
}