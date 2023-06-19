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
    REQUIRE ( "Choose a number between 1 and 10 inclusive. _" == q.getPrompt());
}


TEST_CASE("Question_Int. If answer is not a number, answer is invalid and"
          " getPrompt returns invalid_prompt. ans is 'x' ")
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
    REQUIRE( "I didn't understand your answer. Choose a number in the range [1, 10]. _" ==
             q.getPrompt());
}


TEST_CASE("Question_Int Invalid answer results in fallback answer.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Int q{1,
                      1,
                      10,
                      true,
                      true,
                      5,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE (5 == stoi(q.getAnswer()));
}

TEST_CASE("Question_Int. If answer is not a number, answer is invalid and"
          " getPrompt returns invalid_prompt. ans is '7a' ")
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
    bool ok = q.tryAnswer("7a");
    REQUIRE (false == ok);
    REQUIRE( "I didn't understand your answer. Choose a number in the range [1, 10]. _" ==
             q.getPrompt());
}

TEST_CASE("Question_Int. If answer is not a number, answer is invalid and"
          " getPrompt returns invalid_prompt. ans is 'a7' ")
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
    bool ok = q.tryAnswer("a7");
    REQUIRE (false == ok);
    REQUIRE( "I didn't understand your answer. Choose a number in the range [1, 10]. _" ==
             q.getPrompt());
}

TEST_CASE("Question_Int. White space at beginning of string is valid.")
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
    bool ok = q.tryAnswer(" 2");
    REQUIRE (true == ok);
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE ( 2 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Int. White space at end of string is valid.")
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
    bool ok = q.tryAnswer("2 ");
    REQUIRE (true == ok);
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE ( 2 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
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
    REQUIRE ( 2 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are doubles (with trailing on-zero numbers) are invalid."
          " Try 2.3")
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

TEST_CASE("Question_Int. Answers that are doubles (with trailing non-zero numbers) are invalid."
          " Try .9")
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
    bool ok = q.tryAnswer(".9");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "Nope, that's not an integer, i.e 2, 5, or 199. _" == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are doubles with trailing zeros are valid "
          " as long as there is a number before the decimal. Try 2.0")
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
    bool ok = q.tryAnswer("2.0");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE ( 2 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are doubles with a zero before and after the"
          " decimal are valid. Try 0.0")
{   
    string origPrompt = "Choose a number in the range [0, 10].";
    Question_Int q{1,    // id
                   0,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("0.0");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE ( 0 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range [0, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are doubles with a zeros after the"
          " decimal and no number before the decmial are invalid. Try .0")
{   
    string origPrompt = "Choose a number in the range [0, 10].";
    Question_Int q{1,    // id
                   0,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer(".0");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "I didn't understand your answer. Choose a number in the range [0, 10]. _" 
             == q.getPrompt());
}

TEST_CASE("Question_Int. Answers that are just a decimal are invalid. Try .")
{   
    string origPrompt = "Choose a number in the range [0, 10].";
    Question_Int q{1,    // id
                   0,    // min
                   10,   //max
                   true, // min inclusive
                   true, // max inclusive,
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer(".");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "I didn't understand your answer. Choose a number in the range [0, 10]. _" == q.getPrompt());
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
    REQUIRE ( 1 == stoi(q.getAnswer()));
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
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
    REQUIRE ( 10 == stoi(q.getAnswer()));
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE( "Choose a number in the range [1, 10]. _" == q.getPrompt());
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
    REQUIRE( "I didn't understand your answer. Choose a number in the range (1, 10). _" ==
             q.getPrompt());

    q.tryAnswer("9.9");
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "Nope, that's not an integer, i.e 2, 5, or 199. _" == q.getPrompt());

    q.tryAnswer("11");
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "That integer is not in range. Should be in the range (1, 10). _" == q.getPrompt());

    q.tryAnswer("5");
    REQUIRE( true == q.hasValidAnswer());
    REQUIRE (5 == stoi(q.getAnswer()));
    REQUIRE( "Choose a number in the range (1, 10). _" == q.getPrompt());
}
