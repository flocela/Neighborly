#include "catch.hpp"
#include "../src/Question_Int.h"

#include <iostream>

using Catch::Matchers::Contains;
using namespace std;


// TODO can this really run a single test? Delte note. Or maybe put it in instructions
// Run from the command line:
// g++ --std=c++17 -o runme ../src/Question_Int.cpp test_question_int.cpp test_main.o

TEST_CASE("Question_Int getPrompt() returns the origPrompt first.")
{   
    string origPrompt = "Choose a number between 1 and 10 inclusive.";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    REQUIRE ( origPrompt == q.getPrompt());
}


TEST_CASE("Question_Int. If answer is not a number, answer is invalid and"
          " getPrompt returns invalid_prompt.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (false == ok);
    REQUIRE( "I didn't understand your answer. Choose a number in the range [1, 10]." ==
             q.getPrompt());
}

TEST_CASE("Question_Int. Answers starting with '-' are negative numbers.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("-1");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE( "That integer is not in range. Should be in the range . _" != q.getPrompt());
}

TEST_CASE("Question_Int. Answers starting with '+' are positive numbers.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("+2");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE( origPrompt == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are doubles are invalid.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("2.3");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "Nope, that's not an integer, i.e 2, 5, or 199. _" == q.getPrompt());
}

TEST_CASE("Question_Int. Left edge of range determined correctly for an inclusive range.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("1");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
}

TEST_CASE("Question_Int. Right edge of range determined correctly for an inclusive range.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("10");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
}

TEST_CASE("Question_Int. Left edge of range determined correctly for an exclusive range.")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min inclusive
                   false, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("1");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "That integer is not in range. Should be in the range (1, 10). _" == q.getPrompt());
}


TEST_CASE("Question_Int. Right edge of range determined correctly for an exclusive range.")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min inclusive
                   false, // max inclusive,
                   0,
                   origPrompt,
                   "age"};

    bool ok = q.tryAnswer("10");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "That integer is not in range. Should be in the range (1, 10). _" == q.getPrompt());
}

TEST_CASE("Question_Int runs through a sequence of answers.")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Int q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min is exclusive
                   false, // max is exclusive
                   0,
                   origPrompt,
                   "age"};
    q.tryAnswer("nine");
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "I didn't understand your answer. Choose a number in the range (1, 10)." ==
             q.getPrompt());

    q.tryAnswer("9.9");
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "Nope, that's not an integer, i.e 2, 5, or 199. _" == q.getPrompt());

    q.tryAnswer("11");
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "That integer is not in range. Should be in the range (1, 10). _" == q.getPrompt());

    q.tryAnswer("5");
    REQUIRE( true == q.hasValidAnswer());
}
