#ifndef QUESTION_H
#define QUESTION_H

#include <string>

class Question
{
    public:
        Question () = default;
        Question ( const Question& obj ) = default;
        Question ( Question&& obj) noexcept = default;
        Question& operator= ( const Question& obj) = default;
        Question& operator= ( Question&& obj) noexcept = default;
        virtual ~Question() = default;

        virtual int getID () = 0;
        virtual std::string getPrompt () = 0;
        virtual bool tryAnswer (std::string answer) = 0;
        virtual bool hasValidAnswer () = 0;
        virtual std::string getAnswer () = 0;
    private:
};

#endif