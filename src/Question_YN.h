#ifndef Question_YN_H
#define Question_YN_H

#include "Question.h"

class Question_YN: public Question
{
public:
    Question_YN ( 
        int id,
        std::string origPrompt,
        std::string fallback,
        std::string failedPrompt
    );
    
    Question_YN () = default;
    Question_YN ( const Question_YN& obj ) = default;
    Question_YN ( Question_YN&& obj) noexcept = default;
    Question_YN& operator= ( const Question_YN& obj) = default;
    Question_YN& operator= ( Question_YN&& obj) noexcept = default;
    ~Question_YN() = default;

    int getID() const override;
    std::string getPrompt () const override;
    bool hasValidAnswer () const override;
    std::string getAnswer () const override;
    std::string getFallback () const override;
    std::string getFailedResponse () const override;
    
    bool tryAnswer (std::string answer) override;

private:
    int _ID;
    std::string _answer;
    bool _valid_answer = false;
    std::string _orig_prompt;
    std::string _invalid_prompt = "I didn't understand your answer. ";
    std::string _fallback;
    std::string _failed_prompt = "I was unable to understand your answer. To continue, will use .";
    std::string* _next_prompt;
    
};

#endif