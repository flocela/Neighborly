#include "Question_Int2.h"

#include <regex>
#include <stdexcept>
#include <iostream>

using namespace std;

Question_Int2::Question_Int2 (
    int id,
    int min, 
    int max,
    bool minInclusive,
    bool maxInclusive,
    int fallback,
    string origPrompt,
    string wrongTypePrompt, 
    string inRangePrompt,
    string invalidPrompt,
    string failedPrompt
): _ID{id},
   _min{min},
   _max{max},
   _min_inclusive{minInclusive},
   _max_inclusive{maxInclusive},
   _fallback{fallback},
   _answer{-1},
   _valid_answer{false},
   _orig_prompt{origPrompt},
   _invalid_prompt{invalidPrompt},
   _type_prompt{wrongTypePrompt},
   _range_prompt{inRangePrompt},
   _failed_prompt{failedPrompt},
   _next_prompt{&_orig_prompt}
{
}

Question_Int2::Question_Int2 (
    int id,
    int min, 
    int max,
    bool minInclusive,
    bool maxInclusive,
    int fallback,
    string origPrompt,
    string valueName
): _ID{id},
   _min{min},
   _max{max},
   _min_inclusive{minInclusive},
   _max_inclusive{maxInclusive},
   _fallback{fallback},
   _answer{-1},
   _valid_answer{false},
   _orig_prompt{origPrompt}
{
    // setting _invalid_prompt
    _invalid_prompt.insert(_invalid_prompt.size(), " ");
    _invalid_prompt.insert(_invalid_prompt.size(), _orig_prompt);

    char minEdge = minInclusive? '[' : '(';
    char maxEdge = maxInclusive? ']' : ')';
    // setting range_prompt
        std::stringstream rangeStream;
        rangeStream << minEdge;
        rangeStream << min;
        rangeStream << ',' << ' ';
        rangeStream << max;
        rangeStream << maxEdge;
        _range_prompt.insert(_range_prompt.size()-3, rangeStream.str()); 

    // setting _failed_prompt
    _failed_prompt.insert(_failed_prompt.size()-9, to_string(fallback));
    _failed_prompt.insert(_failed_prompt.size()-1, valueName);

    _next_prompt = &_orig_prompt;
}

int Question_Int2::getID() const
{
    return _ID;
}

string Question_Int2::getPrompt () const
{
    return *_next_prompt;
}

bool Question_Int2::hasValidAnswer () const
{   
    return _valid_answer;
}

string Question_Int2::getAnswer () const
{
    if (hasValidAnswer() == false)
        return to_string(_fallback);
    return to_string(_answer);
}

string Question_Int2::getFallback () const
{
    return to_string(_fallback);
}

string Question_Int2::getFailedResponse () const
{   
    return _failed_prompt;
}

bool Question_Int2::tryAnswer (string ans)
{  
    int intAnswer = -1;
    _valid_answer = false;

    // Determine if ans can be converted to a number.
    try 
    {
        intAnswer = stoi(ans);
    }
    catch(...)
    {   
        _next_prompt = &_invalid_prompt;
        return false;
    }

    // ans string should represent an integer not a double.
    string rs = "^[+-]?\\d+$";
    if (regex_search(ans, regex(rs)) == false)
    {
        _next_prompt = &_type_prompt;
        return false;  
    }
    
    // Determine if ans is in range.
    if (!rangeFunction(intAnswer))
    {   
        _next_prompt = &_range_prompt;
        return false;
    }
    
    // ans is a valid answer.
    _valid_answer = true;
    _answer = intAnswer;
    _next_prompt = &_orig_prompt;
    return _valid_answer;
}

bool Question_Int2::rangeFunction (int val) const
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