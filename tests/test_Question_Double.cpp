#include "catch.hpp"
#include "../src/Question_Double.h"

using Catch::Matchers::Contains;
using namespace std;

TEST_CASE("Question_Double getPrompt() returns the origPrompt first.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    REQUIRE ("Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double If answer is not a number, then is invalid. Get invaid prompt. Try 'x'.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE ( "I didn't understand your answer. _" ==
              q.getPrompt());
}

TEST_CASE("Question_Double Invalid answer results in fallback answer.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("x");
    REQUIRE (false == ok);
    REQUIRE (5 == stod(q.getAnswer()));
}

TEST_CASE("Question_Double If answer is not a number, then is invalid. Get invaid prompt. Try '7a'.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("7a");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE ( "I didn't understand your answer. _" ==
              q.getPrompt());
}

TEST_CASE("Question_Double If answer is not a number, then is invalid. Get invaid prompt. Try 'a7'.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};
    bool ok = q.tryAnswer("a7");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE ( "I didn't understand your answer. _" ==
              q.getPrompt());
}

TEST_CASE("Question_Double. Integers starting with '-' are valid. Try -5.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("-5");
    REQUIRE (ok == true);
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE (-5 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. Integers starting with '+' are valid. Try +5.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("+5");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE (5 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. 0.0 is valid.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("0.0");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE (0 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. .0 is valid.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer(".0");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE (0 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. .7 is valid.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer(".7");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. White space at the begining is valid.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("  3.7");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE (3.7 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. White space at the end is valid.")
{   
    string origPrompt = "Choose a number in the range [-10, 10].";
    Question_Double q{1,
                      -10,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("3.7  ");
    REQUIRE (ok == true);
    REQUIRE (q.hasValidAnswer() == true);
    REQUIRE (3.7 == stod(q.getAnswer()));
    REQUIRE ( "Choose a number in the range [-10, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. Answers starting with '-' are negative numbers.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
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
    REQUIRE ( "That number is not in range. Should be in the range [1.00, 10.00]. _" ==
              q.getPrompt());
}

TEST_CASE("Question_Double. Answers starting with '+' are positive numbers.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("+2.2");
    REQUIRE (true == ok);
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE (2.2 == stod(q.getAnswer()));
    REQUIRE ("Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. Left edge of range determined correctly for an inclusive range.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("1.0");
    REQUIRE (true == ok);
    REQUIRE (1.0 == stod(q.getAnswer()));
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE ("Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. Right edge of range determined correctly for an inclusive range.")
{   
    string origPrompt = "Choose a number in the range [1, 10].";
    Question_Double q{1,
                      1,
                      10,
                      true,
                      true,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("10.0");
    REQUIRE (true == ok);
    REQUIRE (10.0 == stod(q.getAnswer()));
    REQUIRE (true == q.hasValidAnswer());
    REQUIRE ("Choose a number in the range [1, 10]. _" == q.getPrompt());
}

TEST_CASE("Question_Double. Left edge of range determined correctly for an exclusive range..")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,
                      1,
                      10,
                      false,
                      false,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("1.0");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE ("That number is not in range. Should be in the range (1.00, 10.00). _" ==
             q.getPrompt());
}

TEST_CASE("Question_Double. Right edge of range determined correctly for an exclusive range.")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,
                      1,
                      10,
                      false,
                      false,
                      5.0,
                      origPrompt,
                      "age"};

    bool ok = q.tryAnswer("10.0");
    REQUIRE (false == ok);
    REQUIRE (false == q.hasValidAnswer());
    REQUIRE ("That number is not in range. Should be in the range (1.00, 10.00). _" ==
             q.getPrompt());
}

TEST_CASE("Question_Double runs through a sequence of answers.")
{   
    string origPrompt = "Choose a number in the range (1, 10).";
    Question_Double q{1,    // id
                   1,    // min
                   10,   //max
                   false, // min is exclusive
                   false, // max is exclusive
                   0,
                   origPrompt,
                   "age"};
    bool ok = q.tryAnswer("five");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "I didn't understand your answer. _" ==
             q.getPrompt());

    ok = q.tryAnswer("11");
    REQUIRE (false == ok);
    REQUIRE( false == q.hasValidAnswer());
    REQUIRE( "That number is not in range. Should be in the range (1.00, 10.00). _" ==
             q.getPrompt());

    ok = q.tryAnswer("5");
    REQUIRE (true == ok);
    REQUIRE( true == q.hasValidAnswer());
}