#ifndef UI_CMDLINE__H
#define UI_CMDLINE__H

#include "UI.h"

class UI_CmdLine: public UI
{

public:
    
    // When getting an answer from user (for menu or question) will give the user a
    // max number of tries to give a proper response, before using the fallback answer.
    UI_CmdLine (int maxNumOfTries);

    UI_CmdLine () = default;
    UI_CmdLine (const UI_CmdLine& o) = default;
    UI_CmdLine (UI_CmdLine&& o) noexcept = default;
    UI_CmdLine& operator= (const UI_CmdLine& o) = default;
    UI_CmdLine& operator=(UI_CmdLine&& o) noexcept = default;
    ~UI_CmdLine () noexcept = default;

    std::string getAnswer (Question&& question) const override;
    std::string getAnswer (Question& question) const override;

    int menu (
        std::string prompt,
        std::vector<std::string> items,
        int fallBack,
        std::string failureResponse
    ) const override;
    
private:

    int _max_num_of_tries = 3;

    // If can not get a menu item chosen from user, then use _fallback_menu_item.
    int _fallback_menu_item = 1;

    std::string _menu_type_prompt = "Please enter a whole number, like 2._ ";
    std::string _menu_range_prompt = "Please enter a number between 1 and ";
    std::string _menu_item_failure = "Could not determine which item was chosen, will be using .";
    std::string _menu_invalid_prompt = "Could not determine which item was chosen. Please enter a"
        " number between 1 and . _";

    // Inserts additional string at location.
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
};

#endif