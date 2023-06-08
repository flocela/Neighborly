#ifndef QUESTION_DOUBLE_2_H
#define QUESTION_DOUBLE_2_H

#include "Question.h"

class Question_Double2: public Question
{
protected:
    
    Question_Double2 (const Question_Double2& obj) = default;
    Question_Double2 (Question_Double2&& obj) noexcept = default;
    Question_Double2& operator=(const Question_Double2& obj) = default;
    Question_Double2& operator=(Question_Double2&& obj) noexcept = default;
public:
    Question_Double2 () = delete;
    virtual ~Question_Double2() = default;

    Question_Double2 (
        int id,
        double min, 
        double max,
        bool minInclusive, // true if min range value is inclusive, false if exclusive
        bool maxInclusive, // true if max range value is inclusive, false if exclusive
        double fallback, // fallback value to return as answer, if can't get a double from user.
        std::string origPrompt,
        std::string wrongTypePrompt, 
        std::string inRangePrompt,
        std::string invalidPrompt,
        std::string failedPrompt);
    
    Question_Double2 (
        int id,
        double min, 
        double max,
        bool minInclusive, // true if min range value is inclusive, false if exclusive
        bool maxInclusive, // true if max range value is inclusive, false if exclusive
        double fallback,
        std::string origPrompt,
        std::string valueName);

    int getID() const override;
    std::string getPrompt () const override;
    bool hasValidAnswer () const override;
    std::string getAnswer () const override;
    std::string getFallback () const override;
    std::string getFailedResponse () const override;

    bool tryAnswer (std::string answer) override;

private:
    int _ID = 0;
    double _min = 0.0;
    double _max = 0.0;
    bool _min_inclusive = true; // true if min range value is inclusive, false if exclusive
    bool _max_inclusive = true; // true if max range value is inclusive, false if exclusive
    double _fallback = 0.0;
    double _answer = 0.0;
    bool _valid_answer = false;
    std::string _orig_prompt = "";
    std::string _invalid_prompt = "I didn't understand your answer. _";
    // TODO delete _type_prompt. it's a number should work.
    std::string _type_prompt = "Nope, that's not a number, i.e. 0.2, or 13.0. _";
    std::string  _range_prompt = "That number is not in range. Should be in the range . _"; 
    std::string _failed_prompt = "Was unable to understand your answer. To continue, will use  .";
    std::string* _next_prompt;

    bool rangeFunction (double val) const;
    
       
};

#endif