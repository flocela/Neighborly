#include <iomanip>
#include <regex>
#include <sstream>
#include <stdexcept>

#include <iostream>
#include "Question_Double.h"

using namespace std;

Question_Double::Question_Double (
    int id,
    double min, 
    double max,
    double fallback,
    string origPrompt,
    string wrongTypePrompt, 
    string inRangePrompt,
    string invalidPrompt,
    string failedPrompt
): 
    _ID{id},
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

Question_Double::Question_Double (
    int id,
    double min, 
    double max,
    double fallback,
    string origPrompt,
    string valueName
): _ID{id},
   _min{min},
   _max{max},
   _fallback{fallback},
   _orig_prompt{origPrompt}
{ 
    // setting _invalid_prompt
    _invalid_prompt.insert(33, _orig_prompt);

    // setting _failed_prompt
    stringstream fallbackStream;
    fallbackStream << fixed << setprecision(2) << _fallback;
    _failed_prompt.insert(_failed_prompt.size()-2, fallbackStream.str());
    _failed_prompt.insert(_failed_prompt.size()-1, "as the " + valueName);

    // set current _valid_answer and _next_prompt
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
    {
        stringstream fallbackstream;
        fallbackstream << fixed << setprecision(2) << _fallback;
        return fallbackstream.str();
    }
    return to_string(_answer);
}

string Question_Double::getFallback () const
{
    stringstream fallbackstream;
    fallbackstream << fixed << setprecision(2) << _fallback;
    return fallbackstream.str();
}

string Question_Double::getFailedResponse () const
{  
    return _failed_prompt;
}

bool Question_Double::tryAnswer (string ans)
{   
    double doubleAnswer;
    string rs = "^\\-?\\d*\\.?\\d+$";
    try {
        if (regex_search(ans, regex(rs)) == false)
        {
            throw invalid_argument("string argument can not be converted into a double.");
        }
        
        doubleAnswer = stod(ans);
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
    if (!rangeFunction(_min, _max, doubleAnswer))
    {   
        _next_prompt = &_range_prompt;
        return false;
    }
    _valid_answer = true;
    _answer = doubleAnswer;
    return true;
}