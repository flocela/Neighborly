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
    bool minInclusive,
    bool maxInclusive,
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
   _min_inclusive{minInclusive},
   _max_inclusive{maxInclusive},
   _fallback{fallback},
   _answer{0.0},
   _valid_answer{false},
   _orig_prompt{origPrompt},
   _invalid_prompt{invalidPrompt},
   _type_prompt{wrongTypePrompt},
   _range_prompt{inRangePrompt},
   _failed_prompt{failedPrompt},
   _next_prompt{&_orig_prompt}
{
    _next_prompt = &_orig_prompt;
    _valid_answer = false;
}

Question_Double::Question_Double (
    int id,
    double min, 
    double max,
    bool minInclusive,
    bool maxInclusive,
    double fallback,
    string origPrompt,
    string valueName
): _ID{id},
   _min{min},
   _max{max},
   _min_inclusive{minInclusive},
   _max_inclusive{maxInclusive},
   _fallback{fallback},
   _answer{0.0},
   _valid_answer{false},
   _orig_prompt{origPrompt}
{ 
    // setting _invalid_prompt
    _invalid_prompt.insert(_invalid_prompt.size() - 2, _orig_prompt);
    
    char minEdge = minInclusive? '[' : '(';
    char maxEdge = maxInclusive? ']' : ')';
    // setting range_prompt
    std::stringstream rangeStream;
    rangeStream << fixed << setprecision(2);
    rangeStream << minEdge << min << ", " << max << maxEdge;
    _range_prompt.insert(_range_prompt.size()-3, rangeStream.str()); 

    // setting _failed_prompt
    stringstream fallbackStream;
    fallbackStream << fixed << setprecision(2) << _fallback;
    _failed_prompt.insert(_failed_prompt.size()-2, fallbackStream.str());
    _failed_prompt.insert(_failed_prompt.size()-1, "as the " + valueName);

    // set _next_prompt to _orig_prompt
    _next_prompt = &_orig_prompt;
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
    double doubleAnswer = -1.0;
    _valid_answer = false;
    // TODO delete these two lines about regex
    //string rs = "^\\-?\\d*\\.?\\d+$";
    string rs = R"!(^[+-]?\d*\.?\d+$)!"; //TODO 72.

    // Determine if ans can be converted to a number.
    try {
        doubleAnswer = stod(ans);
        if (!regex_match(ans, regex(rs)))
        {   cout << "not a double" << endl;
            throw("Not a double.");
        }
    }
    catch(...)
    {
        _next_prompt = &_invalid_prompt;
        return false;
    }

    // Determine if ans is in range.
    if (!rangeFunction(doubleAnswer))
    {   
        _next_prompt = &_range_prompt;
        return false;
    }

    // ans is a valid answer.
    _valid_answer = true;
    _answer = doubleAnswer;
    _next_prompt = &_orig_prompt;
    return _valid_answer;
}

bool Question_Double::rangeFunction (double val) const
{  
    if (_min_inclusive == true)
    {   
        if (val < _min)
        {
            return false;
        }
    }
    else
    {    
        if (val <= _min)
        {
            return false;
        }
    }
    
    if (_max_inclusive == true)
    {
        if (val > _max)
        {
            return false;
        }
    }
    else
    {
        if (val >= _max)
        {
            return false;
        }
    }
    
    return true;
}