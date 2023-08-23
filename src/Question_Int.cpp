#include <regex>
#include <stdexcept>
#include <iostream>
#include "Question_Int.h"

using namespace std;

Question_Int::Question_Int (
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
): 
    _ID{id},
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
{}

Question_Int::Question_Int (
    int id,
    int min, 
    int max,
    bool minInclusive,
    bool maxInclusive,
    int fallback,
    string origPrompt,
    string valueName
): 
    _ID{id},
    _min{min},
    _max{max},
    _min_inclusive{minInclusive},
    _max_inclusive{maxInclusive},
    _fallback{fallback},
    _answer{-1},
    _valid_answer{false},
    _orig_prompt{origPrompt}
{
    // setting _orig_prompt
    _orig_prompt.insert(_orig_prompt.size(), " _");

    // setting range_prompt
    char minEdge = minInclusive? '[' : '(';
    char maxEdge = maxInclusive? ']' : ')';
    
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

    // set _next_prompt to _orig_prompt
    _next_prompt = &_orig_prompt;
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
    _valid_answer = false;
    _answer = -1;
    
    // finds a digit. finds a digit with a dot. finds a digit with a dot and trailing zeros.
    string rs1 = R"!(^\s*[+-]?\d+(\.[0]*)?\s*$)!";

    // finds a dot. finds a dot with trailing zeros.
    string rs2 = R"!(^\s*[+-]?\.[0]*\s*$)!";

    // finds a digit with a dot with trailing non-zero numbers.
    // find a dot with trailing non-zero numbers.
    string rs3 = R"!(^\s*[+-]?\d*(\.[0-9]+)+\s*$)!";

    if (regex_search(ans, regex(rs1)) == true)
    {
        int tempIntAnswer = stoi(ans);
        if (!rangeFunction(tempIntAnswer))
        {   
            _next_prompt = &_range_prompt;
            return _valid_answer;
        }
        else
        {
            _valid_answer = true;
            _answer = tempIntAnswer;
            _next_prompt = &_orig_prompt;

            return _valid_answer;
        }  
    }

    if (regex_search(ans, regex(rs2)) == true)
    {
        _next_prompt = &_invalid_prompt;
        return _valid_answer;  
    }

    if (regex_search(ans, regex(rs3)) == true)
    {
        _next_prompt = &_type_prompt;
        return _valid_answer;  
    }

    _next_prompt = &_invalid_prompt;
    return false;
    
}

bool Question_Int::rangeFunction (int val) const
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