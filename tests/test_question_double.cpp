#include "catch.hpp"
#include "../src/Question_Double.h"

using Catch::Matchers::Contains;

// Run from the command line:
// g++ --std=c++17 -o runme ../src/Question_Double.cpp test_Question_Double.cpp test_main.o

/*
TEST_CASE("Question_Double getPrompt() returns the origPrompt first.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "I need a number between 1 and 10 inclusive.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    REQUIRE ( q.getPrompt() == origPrompt);
}

TEST_CASE("Question_Double If answer is not a number, getPrompt returns inRangePrompt.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE_THAT( q.getPrompt(), Contains(notNumPrompt));
}

TEST_CASE("Question_Double If answer is not in range, getPrompt() returns inRangePrompt.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("32");
    REQUIRE_THAT( q.getPrompt(), Contains(notInRangePrompt));
}

TEST_CASE("Question_Double hasValidAnswer() is false if answer is not a number.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE( q.hasValidAnswer() == false);
}

TEST_CASE("Question_Double hasValidAnswer() is false, when answer is not in range.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("32");
    REQUIRE( q.hasValidAnswer() == false);
}

TEST_CASE("Question_Double hasValidAnswer() is true, when an in range and a decimal.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("2.3");
    REQUIRE( q.hasValidAnswer() == true);
}

TEST_CASE("Question_Double hasValidAnswer() is true, when an in range and an integer.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("2");
    REQUIRE( q.hasValidAnswer() == true);
}

TEST_CASE("Question_Double getAnswer() returns correct answer.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                      1,
                      10,
                      origPrompt,
                      notNumPrompt,
                      notInRangePrompt};
    q.tryAnswer("2");
    REQUIRE( std::stod(q.getAnswer()) == 2.0);
}

TEST_CASE("Question_Double getAnswer() throws an exception if there isn't an appropriate answer yet.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive";
    std::string notNumPrompt = "I need a whole number.";
    std::string notInRangePrompt = "That is not the correct range.";
    Question_Double q{1,
                   1,
                   10,
                   origPrompt,
                   notNumPrompt,
                   notInRangePrompt};
    q.tryAnswer("x");
    REQUIRE_THROWS_WITH( q.getAnswer(), Contains("There is no answer yet."));
}
*/