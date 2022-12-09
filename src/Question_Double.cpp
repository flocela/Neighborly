#include "Question_Double.h"
#include <stdexcept>

Question_Double::Question_Double (int id,
                                  double min, 
                                  double max,
                                  std::string origPrompt,
                                  std::string wrongTypePrompt, 
                                  std::string inRangePrompt) :
    _ID{id}, _min{min}, _max{max}, _orig_prompt{origPrompt},
    _type_prompt{wrongTypePrompt}, _range_prompt{inRangePrompt}
{
    _next_prompt = &_orig_prompt;
    _valid_answer = false;
}

int Question_Double::getID()
{
    return _ID;
}

std::string Question_Double::getPrompt ()
{
    return *_next_prompt;
}

bool Question_Double::tryAnswer (std::string ans)
{   
    double doubleAnswer;
    try {
        doubleAnswer = std::stod(ans);
    }
    catch(std::invalid_argument& e) // TODO combine these two catches since bodies are the same.
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

bool Question_Double::hasValidAnswer ()
{
    return _valid_answer;
}

std::string Question_Double::getAnswer ()
{
    if (hasValidAnswer() == false)
        throw ("There is no answer yet.");
    return std::to_string(_answer);
}