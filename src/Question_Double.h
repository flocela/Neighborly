#ifndef QUESTION_DOUBLE_H
#define QUESTION_DOUBLE_H

#include "Question.h"

class Question_Double: public Question
{
    public:
        Question_Double (int id,
                         double min, 
                         double max,
                         std::string origPrompt,
                         std::string wrongTypePrompt, 
                         std::string inRangePrompt);
        Question_Double () = default;
        Question_Double (const Question_Double& obj) = default;
        Question_Double (Question_Double&& obj) noexcept = default;
        Question_Double& operator=(const Question_Double& obj) = default;
        Question_Double& operator=(Question_Double&& obj) noexcept = default;
        ~Question_Double() = default;

        int getID() override;
        std::string getPrompt () override;
        bool tryAnswer (std::string answer) override;
        bool hasValidAnswer () override;
        std::string getAnswer () override;
        
    private:
        int _ID;
        double _min;
        double _max;
        double _answer;
        bool   _valid_answer = false;
        std::string  _orig_prompt;
        std::string  _type_prompt;
        std::string  _range_prompt;
        std::string  _invalid_prompt = "I didn't understand your answer.";
        std::string* _next_prompt;
};

#endif