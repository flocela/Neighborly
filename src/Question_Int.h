#ifndef QUESTION_INT_H
#define QUESTION_INT_H

#include "Question.h"

class Question_Int: public Question
{
public:
    Question_Int (
        int id,
        int min, 
        int max,
        int fallback,
        std::string origPrompt,
        std::string wrongTypePrompt, 
        std::string inRangePrompt,
        std::string invalidPrompt,
        std::string failedPrompt);

    Question_Int (
        int id,
        int min, 
        int max,
        int fallback,
        std::string origPrompt,
        std::string valueName);
        
    Question_Int () = default;
    Question_Int (const Question_Int& obj) = default;
    Question_Int (Question_Int&& obj) noexcept = default;
    Question_Int& operator=(const Question_Int& obj) = default;
    Question_Int& operator=(Question_Int&& obj) noexcept = default;
    ~Question_Int() = default;

    int getID() const override;
    std::string getPrompt () const override;
    bool hasValidAnswer () const  override;
    std::string getAnswer () const override;
    std::string getFallback () const override;
    std::string getFailedResponse () const override;

    bool tryAnswer (std::string answer) override;
    
private:
    int _ID;
    int _min;
    int _max;
    int _fallback;
    int _answer;
    int _valid_answer = false;
    std::string _orig_prompt;
    std::string _type_prompt = "Nope, that's not an integer, i.e 2, 5, or 199. _";
    std::string _range_prompt = "That integer is not in range. Should be between  and . _";
    std::string _invalid_prompt = "I didn't understand your answer.";
    std::string _failed_prompt = "Was unable to understand your answer. To continue, will use  as the .";
    std::string* _next_prompt;
};

#endif