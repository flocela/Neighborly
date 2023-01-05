#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Question.h"

class UI
{
    public:
        virtual int menu (std::string prompt, std::vector<std::string> items) = 0;
        virtual std::string getAnswer (Question& question) = 0;
        virtual void print (std::string str) = 0;
};

#endif