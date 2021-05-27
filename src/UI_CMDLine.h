#ifndef GUISTARTINFO_CMDLINEA_H
#define GUISTARTINFO_CMDLINEA_H

#include "UI.h"

class UI_CMDLine: public UI
{
    public:
        std::string getAnswer (Question& question) override;
        int menu (std::string prompt, std::vector<std::string> items) override;
    private:
};

#endif