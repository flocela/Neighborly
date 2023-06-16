#ifndef QUESTION_INT_H
#define QUESTION_INT_H

#include "Question.h"
#include <memory> // TODO delete <memory>
#include <string> // TODO delte <string>
// Creates successive prompts until a proper answer is given.
// A proper answer is an integer.
// It is within the range detailed in the constructor.
class Question_Int: public Question
{
protected:
    Question_Int (const Question_Int& obj) = default;
    Question_Int (Question_Int&& obj) noexcept = default;
    Question_Int& operator=(const Question_Int& obj) = default;
    Question_Int& operator=(Question_Int&& obj) noexcept = default;

public:
    Question_Int () = delete;
    virtual ~Question_Int () noexcept = default;

    Question_Int (
        int id,  // identifier for this question
        int min, // the minimum of the range of allowable integers
        int max, // the maximum of the range of allowable integers
        bool minInclusive, // true if the range's minimum integer is inclusive, false otherwise
        bool maxInclusive, // true if the range's maximum integer is inclusive, false otherwise
        int fallback, // a fallback integer. can always be retrieved,
                      //but presumably retrieved when user does not provide an integer in range
        std::string origPrompt, // first prompt
        std::string wrongTypePrompt, // prompt detailing that the answer was a nu
        std::string inRangePrompt, // prompt detailing that the answer was not in range
        std::string invalidPrompt, // prompt detailing that the answer was not 
        std::string failedPrompt);

    Question_Int (
        int id,
        int min, 
        int max,
        bool minInclusive,
        bool maxInclusive,
        int fallback,
        std::string origPrompt,
        std::string valueName);
        
    int getID() const override;
    std::string getPrompt () const override;
    bool hasValidAnswer () const  override;
    std::string getAnswer () const override;
    std::string getFallback () const override;
    std::string getFailedResponse () const override;

    bool tryAnswer (std::string answer) override;

private:
    int _ID = 0;
    int _min = 0;
    int _max = 0;
    int _min_inclusive = true;
    int _max_inclusive = true;
    int _fallback = 0;
    int _answer = -1;
    int _valid_answer = false;
    std::string _orig_prompt = "";
    std::string _invalid_prompt = "I didn't understand your answer.";
    std::string _type_prompt = "Nope, that's not an integer, i.e 2, 5, or 199. _";
    std::string _range_prompt = "That integer is not in range. Should be in the range . _";
    std::string _failed_prompt = "Was unable to understand your answer. To continue, will use  as the .";
    std::string* _next_prompt = &_orig_prompt;
    
    bool rangeFunction (int val) const;  

};

#endif