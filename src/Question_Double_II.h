#ifndef QUESTION_DOUBLE_II_H
#define QUESTION_DOUBLE_II_H

#include "Question_Double.h"

// question checks if answer is in range, where minimum and maximum numbers are both inclusive.
class Question_Double_II : public Question_Double
{
public:
    Question_Double_II (
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

    Question_Double_II (
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
        rangeStream << '[';
        rangeStream << std::fixed << std::setprecision(2) << min;
        rangeStream << ',' << ' ';
        rangeStream << std::fixed << std::setprecision(2) << max;
        rangeStream << ']';
        _range_prompt.insert(_range_prompt.size()-3, rangeStream.str()); 
    }

    Question_Double_II () = delete;
    Question_Double_II (const Question_Double_II& o) = default;
    Question_Double_II (Question_Double_II&& o) noexcept = default;
    Question_Double_II& operator= (const Question_Double_II& o) = default;
    Question_Double_II& operator= (Question_Double_II&& o) noexcept = default;
    ~Question_Double_II () = default;

    bool rangeFunction (double min, double max, double val) const override
    {
        return (val >= min && val <= max);
    }
};

#endif