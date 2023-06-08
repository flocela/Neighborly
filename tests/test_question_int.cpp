#include "catch.hpp"
#include "../src/Question_Int.h"

using Catch::Matchers::Contains;

#include <iostream>

// TODO can this really run a single test? Delte note. Or maybe put it in instructions
// Run from the command line:
// g++ --std=c++17 -o runme ../src/Question_Int.cpp test_question_int.cpp test_main.o

TEST_CASE("Question_Int getPrompt() returns the origPrompt first.")
{   
    std::string origPrompt = "Choose a number between 1 and 10 inclusive.";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    REQUIRE ( q.getPrompt() == origPrompt);
}


TEST_CASE("Question_Int. If answer is not a number, answer is invalid and"
          " getPrompt returns invalid_prompt.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() ==
        "I didn't understand your answer. Choose a number in the range [1, 10].");
}

TEST_CASE("Question_Int. Answers starting with '-' are negative numbers.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("-1");
    REQUIRE (ok == false);
    REQUIRE (q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() !=
        "That integer is not in range. Should be in the range . _");
}

TEST_CASE("Question_Int. Answers starting with '+' are positive numbers.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("+2");
    REQUIRE (ok == true);
    REQUIRE( q.hasValidAnswer() == true);
    REQUIRE( q.getPrompt() == origPrompt);
}

TEST_CASE("Question_Int. Answers that are doubles are invalid.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("2.3");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "Nope, that's not an integer, i.e 2, 5, or 199. _");
}

TEST_CASE("Question_Int. Left edge of range determined correctly for an inclusive range.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("1");
    REQUIRE (ok == true);
    REQUIRE( q.hasValidAnswer() == true);
}

TEST_CASE("Question_Int. Right edge of range determined correctly for an inclusive range.")
{   
    std::string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("10");
    REQUIRE (ok == true);
    REQUIRE( q.hasValidAnswer() == true);
}

TEST_CASE("Question_Int. Left edge of range determined correctly for an exclusive range.")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min inclusive
                   false, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("1");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "That integer is not in range. Should be in the range (1, 10). _");
}


TEST_CASE("Question_Int. Right edge of range determined correctly for an exclusive range.")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min inclusive
                   false, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("10");
    REQUIRE (ok == false);
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "That integer is not in range. Should be in the range (1, 10). _");
}

TEST_CASE("Question_Int runs through a sequence of answers.")
{   
    std::string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min is exclusive
                   false, // max is exclusive
                   0,
                   origPrompt,
                   "age"};
    q.tryAnswer("nine");
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() ==
        "I didn't understand your answer. Choose a number in the range (1, 10).");

    q.tryAnswer("9.9");
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "Nope, that's not an integer, i.e 2, 5, or 199. _");

    q.tryAnswer("11");
    REQUIRE( q.hasValidAnswer() == false);
    REQUIRE( q.getPrompt() == "That integer is not in range. Should be in the range (1, 10). _");

    q.tryAnswer("5");
    REQUIRE( q.hasValidAnswer() == true);
}
