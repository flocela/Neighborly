#include "catch.hpp"
#include "../src/Question_Double.h"

using Catch::Matchers::Contains;

//TODO get rid of this line
// Run from the command line:
// g++ --std=c++17 -o runme ../src/Question_Double.cpp test_Question_Double.cpp test_main.o

TEST_CASE("Question_Double getPrompt() returns the origPrompt first.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    REQUIRE ( q.getPrompt() == origPrompt);
}

TEST_CASE("Question_Double If answer is not a number, then is invalid. Get invaid prompt.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE ( q.getPrompt() == "I didn't understand your answer. Choose a number in the range [1, 10]. _");
}

TEST_CASE("Question_Double. Answers starting with '-' are negative numbers.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("-2.0");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE ( q.getPrompt() == "That number is not in range. Should be in the range [1.00, 10.00]. _");
}

TEST_CASE("Question_Double. Answers starting with '+' are positive numbers.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("+2.0");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE ( q.getPrompt() == origPrompt);
}

TEST_CASE("Question_Double. Left edge of range determined correctly for an inclusive range.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("1.0");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
}

TEST_CASE("Question_Double. Right edge of range determined correctly for an inclusive range.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("10.0");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
}

TEST_CASE("Question_Double. Left edge of range determined correctly for an exclusive range..")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,
                      1,
                      10,
                      false,
                      false,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("1.0");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE ( q.getPrompt() == "That number is not in range. Should be in the range (1.00, 10.00). _");
}

TEST_CASE("Question_Double. Right edge of range determined correctly for an exclusive range.")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,
                      1,
                      10,
                      false,
                      false,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("10.0");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE ( q.getPrompt() == "That number is not in range. Should be in the range (1.00, 10.00). _");
}

TEST_CASE("Question_Double runs through a sequence of answers.")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min is exclusive
                   false, // max is exclusive
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("five");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() ==
        "I didn't understand your answer. Choose a number in the range (1, 10). _");

    ok = q.tryAnswer("11");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "That number is not in range. Should be in the range (1.00, 10.00). _");

    q.tryAnswer("5");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == true);
}