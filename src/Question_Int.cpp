#include "Question_Int.h"
#include <stdexcept>
#include <iostream>

Question_Int::Question_Int (int id,
                            int min, 
                            int max,
                            std::string origPrompt,
                            std::string wrongTypePrompt, 
                            std::string inRangePrompt) :
    _ID{id}, _min{min}, _max{max}, _orig_prompt{origPrompt},
    _type_prompt{wrongTypePrompt}, _range_prompt{inRangePrompt}
{
    _next_prompt = &_orig_prompt;
    _valid_answer = false;
}

int Question_Int::getID()
{
    return _ID;
}

std::string Question_Int::getPrompt ()
{
    return *_next_prompt;
}

bool Question_Int::tryAnswer (std::string ans)
{   
    int intAnswer;
    try {
        intAnswer = std::stoi(ans);
    }
    catch(std::invalid_argument& e)
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

bool Question_Int::hasValidAnswer ()
{   
    return _valid_answer;
}

std::string Question_Int::getAnswer ()
{
    if (hasValidAnswer() == false)
        throw ("There is no answer yet.");
    return std::to_string(_answer);
}