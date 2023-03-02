#ifndef GUISTARTINFO_CMDLINEA_H
#define GUISTARTINFO_CMDLINEA_H

#include "UI.h"

class UI_CMDLine: public UI
{
public:
    

    // when getting an answer from user (for menu or question) will give the user
    // max number of tries to give a proper response, before using the fallback answer.
    UI_CMDLine (int maxNumOfTries);

    UI_CMDLine () = default;
    UI_CMDLine (const UI_CMDLine& o) = default;
    UI_CMDLine (UI_CMDLine&& o) noexcept = default;
    UI_CMDLine& operator= (const UI_CMDLine& o) = default;
    UI_CMDLine& operator=(UI_CMDLine&& o) noexcept = default;
    ~UI_CMDLine () = default;

    std::string getAnswer (Question& question) const override;

    int menu (
        std::string prompt,
        std::vector<std::string> items,
        int fallBack,
        std::string failureResponse
    ) const override;
    
private:
    int _max_num_of_tries = 3;

    // if can not get a menu item chosen from user, then use _fallback_menu_item
    int _fallback_menu_item = 1;

    std::string _menu_type_prompt = "Please enter a whole number, like 2. ";
    std::string _menu_range_prompt = "Please enter a number between 1 and ";
    std::string _menu_item_failure = "Could not determine which item was chosen, will be using .";
    std::string _menu_invalid_prompt = "Could not determine which item was chosen. Please enter a"
        " number between 1 and . _";

    // inserts additional string at location
    std::string insertIntoString (
        std::string str, 
        int location,
        std::string insert) const;
};

#endif