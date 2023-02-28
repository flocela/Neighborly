#ifndef QUESTION_DOUBLE_H
#define QUESTION_DOUBLE_H

#include "Question.h"

class Question_Double: public Question
{
public:
    Question_Double (
        int id,
        double min, 
        double max,
        double fallback, // fallback value to return as answer, if can't get a double from user.
        std::string origPrompt,
        std::string wrongTypePrompt, 
        std::string inRangePrompt,
        std::string invalidPrompt,
        std::string failedPrompt);
    
    Question_Double (
        int id,
        double min, 
        double max,
        double fallback,
        std::string origPrompt,
        std::string valueName);

    Question_Double () = default;
    Question_Double (const Question_Double& obj) = default;
    Question_Double (Question_Double&& obj) noexcept = default;
    Question_Double& operator=(const Question_Double& obj) = default;
    Question_Double& operator=(Question_Double&& obj) noexcept = default;
    ~Question_Double() = default;

    int getID() const override;
    std::string getPrompt () const override;
    bool hasValidAnswer () const override;
    std::string getAnswer () const override;
    std::string getFallback () const override;
    std::string getFailedResponse () const override;

    bool tryAnswer (std::string answer) override;

private:
    int _ID;
    double _min;
    double _max;
    double _fallback;
    double _answer;
    bool   _valid_answer = false;
    std::string _orig_prompt;
    std::string _type_prompt = "Nope, that's not a number, i.e. 0.2, or 13.0. _"; 
    std::string _invalid_prompt = "I didn't understand your answer. _";
    std::string _failed_prompt = "Was unable to understand your answer. To continue, will use  .";
    std::string* _next_prompt;

protected:
    virtual bool rangeFunction (double min, double max, double val) const = 0;
    std::string  _range_prompt = "That number is not in range. Should be in the range. _";
       
};

#endif