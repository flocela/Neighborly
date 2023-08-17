#include "catch.hpp"
#include "../src/RandIntsMaker.h"

#include <iostream>
#include <unordered_set>

using namespace std;
using Catch::Matchers::Contains;

TEST_CASE("RandIntsMaker:: Well size is zero, returns vector of size zero.")
{   
    RandIntsMaker rI{};
    vector<int> actual = rI.getRandomIntegers(0, 0);

    REQUIRE ( 0 == actual.size());
}

TEST_CASE("RandIntsMaker:: Well size is zero. Quantity is 10")
{   
    RandIntsMaker rI{};

    REQUIRE_THROWS_WITH ( rI.getRandomIntegers(0, 10),
                          Contains("Well size must be at least as large as quantity."));
}

TEST_CASE("RandIntsMaker:: Well size and quanity size are the same, test with 10")
{   
    RandIntsMaker rI{};
    vector<int> actual = rI.getRandomIntegers(10, 10);

    vector<int> inOrder = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


    vector<int> sortedActual = actual;
    sort(sortedActual.begin(), sortedActual.end());

    REQUIRE(inOrder == sortedActual);

    // actual has the numbers in different order than inOrder
    REQUIRE(inOrder != actual);
}

TEST_CASE("RandIntsMaker:: Well size and quanity size are the same, test with 1")
{   
    RandIntsMaker rI{};

    vector<int> expected(1, 0);

    // all the numbers in actual are in inOrder.
    REQUIRE(expected == rI.getRandomIntegers(1, 1));
}

TEST_CASE("RandIntsMaker:: Well size and quanity size are the same, test with 5")
{   
    RandIntsMaker rI{};
    vector<int> actual = rI.getRandomIntegers(5, 5);

    vector<int> inOrder = vector<int>(5);
    for (int ii=0; ii < inOrder.size(); ++ii)
    {
        inOrder[ii] = ii;
    }


    vector<int> sortedActual = actual;
    sort(sortedActual.begin(), sortedActual.end());

    // all the numbers in actual are in inOrder.
    REQUIRE(inOrder == sortedActual);;

    // actual has the numbers in different order than inOrder.
    // There is a change that they will be in order...
    REQUIRE(inOrder != actual);
}


TEST_CASE("RandIntsMaker:: Well size and quanity size are the same, test with 1,000")
{   
    RandIntsMaker rI{};
    vector<int> actual = rI.getRandomIntegers(1000, 1000);

    vector<int> inOrder = vector<int>(1000);
    for (int ii=0; ii < inOrder.size(); ++ii)
    {
        inOrder[ii] = ii;
    }


    vector<int> sortedActual = actual;
    sort(sortedActual.begin(), sortedActual.end());

    // all the numbers in actual are in inOrder.
    REQUIRE(inOrder == sortedActual);

    // actual has the numbers in different order than inOrder.
    // There is a change that they will be in order...
    REQUIRE(inOrder != actual);
}

TEST_CASE("RandIntsMaker:: Well size is larger than quantity")
{   
    RandIntsMaker rI{};
    vector<int> actual = rI.getRandomIntegers(1000, 100);

    unordered_set<int> actualSet{};
    for (int x : actual)
    {
        actualSet.insert(x);
    }

    REQUIRE (100 == actual.size());

    // numbers should range from [0,1000).
    int found = false;
    for (int ii=0; ii<1000; ii+=100)
    {
        found = false;
        for (int jj=ii; jj<ii+100; ++jj)
        {
            if (actualSet.find(jj) != actualSet.end())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            break;
        }
    }
    REQUIRE(found);

    // there should be no duplicates
    REQUIRE(actual.size() == actualSet.size());
}