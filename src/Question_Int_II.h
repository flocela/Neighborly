#ifndef QUESTION_Int_II_H
#define QUESTION_Int_II_H

#include "Question_Int.h"
#include <sstream>
#include <iostream>

class Question_Int_II: public Question_Int
{
public:
    Question_Int_II (
        int id,
        int min, 
        int max,
        int fallback,
        std::string origPrompt,
        std::string wrongTypePrompt, 
        std::string inRangePrompt,
        std::string invalidPrompt,
        std::string failedPrompt
    ): Question_Int {
        id,
        min, 
        max,
        fallback,
        origPrompt,
        wrongTypePrompt, 
        inRangePrompt,
        invalidPrompt,
        failedPrompt
    }{}

    Question_Int_II (
        int id,
        int min, 
        int max,
        int fallback,
        std::string origPrompt,
        std::string valueName
    ): Question_Int{id, min, max, fallback, origPrompt, valueName}
    {   
        // setting range_prompt
        std::stringstream rangeStream;
        rangeStream << '[';
        rangeStream << min;
        rangeStream << ',' << ' ';
        rangeStream << max;
        rangeStream << ']';
        _range_prompt.insert(_range_prompt.size()-3, rangeStream.str());
    }
        
    Question_Int_II () = default;
    Question_Int_II (const Question_Int_II& obj) = default;
    Question_Int_II (Question_Int_II&& obj) noexcept = default;
    Question_Int_II& operator=(const Question_Int_II& obj) = default;
    Question_Int_II& operator=(Question_Int_II&& obj) noexcept = default;
    ~Question_Int_II() = default;

private:
    int _ID;
    int _min;
    int _max;
    int _fallback;
    int _answer;
    int _valid_answer = false;
    std::string _orig_prompt;
    std::string _type_prompt = "Nope, that's not an integer, i.e 2, 5, or 199. _";
    std::string _invalid_prompt = "I didn't understand your answer.";
    std::string _failed_prompt = "Was unable to understand your answer. To continue, will use  as the .";
    std::string* _next_prompt;

protected:
    bool rangeFunction (int min, int max, int val) const
    {
        return (val >= min && val <= max);
    }
};

#endif