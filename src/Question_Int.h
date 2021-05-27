#ifndef QUESTION_INT_H
#define QUESTION_INT_H

#include "Question.h"

class Question_Int: public Question
{
    public:
        Question_Int (int id,
                      int min, 
                      int max,
                      std::string origPrompt,
                      std::string wrongTypePrompt, 
                      std::string inRangePrompt);
        Question_Int () = default;
        Question_Int (const Question_Int& obj) = default;
        Question_Int (Question_Int&& obj) noexcept = default;
        Question_Int& operator=(const Question_Int& obj) = default;
        Question_Int& operator=(Question_Int&& obj) noexcept = default;
        ~Question_Int() = default;

        int getID() override;
        std::string getPrompt () override;
        bool tryAnswer (std::string answer) override;
        bool hasValidAnswer () override;
        std::string getAnswer () override;
        
    private:
        int _ID;
        int _min;
        int _max;
        int _answer;
        int _valid_answer = false;
        std::string _orig_prompt;
        std::string _type_prompt;
        std::string _range_prompt;
        std::string _invalid_prompt = "I didn't understand your answer.";
        std::string* _next_prompt;
};

#endif