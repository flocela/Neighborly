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

// if user does not reply with an number corresponding to an item, then returns the fallBack.
virtual int menu (std::string prompt, std::vector<std::string> items, int fallBack)const = 0;

virtual std::string getAnswer (Question& question)const  = 0;

virtual void print (std::string str)const  = 0;
};

#endif