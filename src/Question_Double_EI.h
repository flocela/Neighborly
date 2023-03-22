#ifndef QUESTION_DOUBLE_EI_H
#define QUESTION_DOUBLE_EI_H

#include "Question_Double.h"
#include <iomanip>

// question checks if val is in range, where val is between min (exclusive) and max (inclusive).
class Question_Double_EI : public Question_Double
{
public:
    Question_Double_EI (
        int id,
        double min,
        double max,
        double fallback,
        std::string origPrompt,
        std::string wrongTypePrompt,
        std::string inRangePrompt,
        std::string invalidPrompt,
        std::string failedPrompt
    ): Question_Double{
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
    Question_Double_EI (
        int id,
        double min, 
        double max,
        double fallback,
        std::string origPrompt,
        std::string valueName
    ): Question_Double{id, min, max, fallback, origPrompt, valueName}
    {
        // setting range_prompt
        std::stringstream rangeStream;
        rangeStream << '(';
        rangeStream << std::fixed << std::setprecision(2) << min;
        rangeStream << ',' << ' ';
        rangeStream << std::fixed << std::setprecision(2) << max;
        rangeStream << ']';
        _range_prompt.insert(_range_prompt.size()-3, rangeStream.str()); 
    }
    Question_Double_EI () = delete;
    Question_Double_EI (const Question_Double_EI& o) = default;
    Question_Double_EI (Question_Double_EI&& o) noexcept = default;
    Question_Double_EI& operator= (const Question_Double_EI& o) = default;
    Question_Double_EI& operator= (Question_Double_EI&& o) noexcept = default;

protected:
    bool rangeFunction (double min, double max, double val) const override
    {
        return (val > min && val <= max);
    }
};

#endif