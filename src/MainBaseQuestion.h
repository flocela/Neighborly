#ifndef MAIN_BASE_QUESTION_H
#define MAIN_BASE_QUESTION_H

#include <vector>
#include "UI_CMDLine.h"

class MainBaseQuestion
{
    public:
        bool askUserToUsePremadeExamples ();
    
    private:
        UI_CMDLine ui;

};

#endif