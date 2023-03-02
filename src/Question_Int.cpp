#include "Question_Int.h"

#include <regex>
#include <stdexcept>
#include <iostream>

using namespace std;

Question_Int::Question_Int (
    int id,
    int min, 
    int max,
    int fallback,
    string origPrompt,
    string wrongTypePrompt, 
    string inRangePrompt,
    string invalidPrompt,
    string failedPrompt
): _ID{id},
   _min{min},
   _max{max},
   _fallback{fallback},
   _orig_prompt{origPrompt},
   _type_prompt{wrongTypePrompt},
   _invalid_prompt{invalidPrompt},
   _failed_prompt{failedPrompt},
   _range_prompt{inRangePrompt}
{
    _next_prompt = &_orig_prompt;
    _valid_answer = false;
}

Question_Int::Question_Int (
    int id,
    int min, 
    int max,
    int fallback,
    string origPrompt,
    string valueName
): _ID{id},
   _min{min},
   _max{max},
   _fallback{fallback},
   _orig_prompt{origPrompt}
{
    // setting _invalid_prompt
    _invalid_prompt.insert(_invalid_prompt.size(), _orig_prompt);

    // setting _failed_prompt
    _failed_prompt.insert(_failed_prompt.size()-9, to_string(fallback));
    _failed_prompt.insert(_failed_prompt.size()-1, valueName);

    //set current _valid_naswer and _next_prompt
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
        return to_string(_fallback);
    return to_string(_answer);
}

string Question_Int::getFallback () const
{
    return to_string(_fallback);
}

string Question_Int::getFailedResponse () const
{   
    return _failed_prompt;
}

bool Question_Int::tryAnswer (string ans)
{  
    int intAnswer = -1;

    string rs = "^\\-?\\d+$";

    try 
    {
        if (regex_search(ans, regex(rs)) == false)
        {
            throw invalid_argument("string argument can not be converted to an integer.");
        }
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
    if (!rangeFunction(_min, _max, intAnswer))
    {   
        _next_prompt = &_range_prompt;
        return false;
    }
    _valid_answer = true;
    _answer = intAnswer;
    return _valid_answer;
}