#ifndef UI__H
#define UI__H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Question.h"

// Presents user with menu or question on the command line and retrieves answer.
class UI
{

protected:
    UI () = default;
    UI (const UI& o) = default;
    UI (UI&& o) noexcept = default;
    UI& operator= (const UI& o) = default;
    UI& operator= (UI&& o) noexcept = default;

public:

    virtual ~UI () noexcept = default;

    // Presents the user with a menu of choices and returns the user's response.
    // If user does not reply with an number corresponding to an item, then returns the fallback item.
    virtual int menu (
        std::string prompt,
        std::vector<std::string> items,
        int fallBack,
        std::string failureResponse
    ) const = 0;

    // Presents the user with the question and returns the user's response.
    // If can not get a proper answer from the user, then the question's fallback answer
    // is returned.
    virtual std::string getAnswer (Question& question)const = 0;

    // Presents the user with the question and returns the user's response.
    // If can not get a proper answer from the user, then the question's fallback answer
    // is returned.
    virtual std::string getAnswer (Question&& question) const = 0;

    };

#endif