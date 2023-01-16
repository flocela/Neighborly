#ifndef GUISTARTINFO_CMDLINEA_H
#define GUISTARTINFO_CMDLINEA_H

#include "UI.h"

class UI_CMDLine: public UI
{
    public:
        UI_CMDLine () = default;
        UI_CMDLine (int maxNumOfTries);

        int menu (std::string prompt, std::vector<std::string> items, int fallBack) const override;
        std::string getAnswer (Question& question) const override;
        void print (std::string str) const override;
    private:
        int _max_num_of_tries = 3;
};

#endif