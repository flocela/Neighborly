#ifndef GUISTARTINFO_CMDLINEA_H
#define GUISTARTINFO_CMDLINEA_H

#include "UI.h"

class UI_CMDLine: public UI
{
    public:
        UI_CMDLine () = default;
        UI_CMDLine (int maxNumOfTries);

        int menu (
            std::string prompt,
            std::vector<std::string> items,
            int fallBack,
            std::string failureResponse
        ) const override;
        
        std::string getAnswer (Question& question) const override;
        void print (std::string str) const override; //TODO think about removing print function
    private:
        int _max_num_of_tries = 3;

        // if can not get a menu item chosen from user, then use _fallback_menu_item
        std::string _fallback_menu_item = "1";

        std::string _menu_item_failure = "Could not determine which item was chosen, will be using .";
};

#endif