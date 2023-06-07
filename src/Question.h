#ifndef QUESTION_H
#define QUESTION_H

#include <string>

// Used to create successive prompts for the user until the user's answer is valid.
// If the user doesn't have a successful answer, then the caller can use the fallback answer.
class Question
{
protected:
    Question () = default;
    Question (const Question& o) = default;
    Question (Question&& o) noexcept = default;
    Question& operator= (const Question& o) = default;
    Question& operator= (Question&& o) noexcept = default;
public:
    virtual ~Question() = default;
    
    // get question's id
    virtual int getID () const = 0;

    // get the appropriate prompt
    virtual std::string getPrompt () const = 0;

    virtual bool hasValidAnswer () const = 0;

    virtual std::string getAnswer () const  = 0;

    // returns the fallback string
    virtual std::string getFallback () const = 0;

    // returns an explanation or what will happen next for the user, since the
    // system could not get a proper answer.
    virtual std::string getFailedResponse () const = 0;

    // returns true if answer is a proper answer.
    virtual bool tryAnswer (std::string answer) = 0;
};

#endif