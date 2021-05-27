#include "catch.hpp"
#include "../src/Question_Int.h"

using Catch::Matchers::Contains;

#include <iostream>

// Run from the command line:
// g++ --std=c++17 -o runme ../src/Question_Int.cpp test_question_int.cpp test_main.o

TEST_CASE("Question_Int getPrompt() returns the origPrompt first.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "I need a number between 1 and 10 inclusive.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    REQUIRE ( q.getPrompt() == origPrompt);
}

TEST_CASE("Question_Int If answer is not a number, getPrompt returns inRangePrompt.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE_THAT( q.getPrompt(), Contains(notNumPrompt));
}

TEST_CASE("Question_Int If answer is not in range, getPrompt() returns inRangePrompt.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("32");
    REQUIRE_THAT( q.getPrompt(), Contains(notInRangePrompt));
}

TEST_CASE("Question_Int hasValidAnswer() is false if answer is not a number.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE( q.hasValidAnswer() == false);
}

TEST_CASE("Question_Int hasValidAnswer() is false, when answer is not in range.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("32");
    REQUIRE( q.hasValidAnswer() == false);
}

TEST_CASE("Question_Int hasValidAnswer() is true, when an in range, integer answer is given.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("2");
    REQUIRE( q.hasValidAnswer() == true);
}

TEST_CASE("Question_Int getAnswer() returns correct answer.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("2");
    REQUIRE( q.getAnswer() == "2");
}

TEST_CASE("Question_Int getAnswer() throws an exception if there isn't an appropriate answer yet.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Int q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE_THROWS_WITH( q.getAnswer(), Contains("There is no answer yet."));
}