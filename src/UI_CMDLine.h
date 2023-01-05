#ifndef GUISTARTINFO_CMDLINEA_H
#define GUISTARTINFO_CMDLINEA_H

#include "UI.h"

class UI_CMDLine: public UI
{
    public:
        UI_CMDLine () = default;
        UI_CMDLine (int maxNumOfTries);
        std::string getAnswer (Question& question) override;
        int menu (std::string prompt, std::vector<std::string> items, int fallBack) override;
        void print (std::string str) override;
    private:
        int _max_num_of_tries = 3;
};

#endif