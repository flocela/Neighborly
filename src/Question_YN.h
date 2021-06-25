#ifndef Question_YN_H
#define Question_YN_H

#include "Question.h"

class Question_YN: public Question
{
    public:
        Question_YN ( int id,
                      std::string origPrompt,
                      std::string invalidPrompt);
        
        Question_YN () = default;
        Question_YN ( const Question_YN& obj ) = default;
        Question_YN ( Question_YN&& obj) noexcept = default;
        Question_YN& operator= ( const Question_YN& obj) = default;
        Question_YN& operator= ( Question_YN&& obj) noexcept = default;
        ~Question_YN() = default;

        int getID() override;
        std::string getPrompt () override;
        bool tryAnswer (std::string answer) override;
        bool hasValidAnswer () override;
        std::string getAnswer () override;
    private:
        int _ID;
        std::string _answer;
        bool _valid_answer = false;
        std::string _orig_prompt;
        std::string _invalid_prompt;
        std::string* _next_prompt;
};

#endif