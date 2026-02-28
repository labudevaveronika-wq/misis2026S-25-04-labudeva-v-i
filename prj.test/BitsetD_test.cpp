#include "../prj.labs/Bitsetd/BitsetD.hpp"
#include <iostream>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../prj.labs/prj.thirdparty/doctest/doctest.h"
#include <limits>

TEST_CASE("Basic BitsetD functionality") {
    SUBCASE("Constructors") {
        BitsetD empty;
        CHECK(empty.size() == 0);

        BitsetD T1(16, true);
        CHECK(T1.size() == 16);
        CHECK(T1.get(0) == 1);
        CHECK(T1.get(1) == 1);
        CHECK(T1.get(2) == 1);

        BitsetD T2(0b1101110100000000);
        CHECK(T2.size() == 64);
        CHECK(T2.get(0) == 0);
        CHECK(T2.get(8) == 1);
        CHECK(T2.get(15) == 1);
        CHECK(T2.get(63) == 0);

        BitsetD T3(T1);
        CHECK(T1.size() == 16);
        CHECK(T1.get(0) == 1);
        CHECK(T1.get(1) == 1);
        CHECK(T1.get(2) == 1);
    }

    SUBCASE("GET SET") {
        BitsetD T1(8, false);
        CHECK(T1.size() == 8);
        CHECK(T1.get(0) == 0);
        CHECK(T1.get(1) == 0);
        CHECK(T1.get(2) == 0);
        T1.set(1, true);
        CHECK(T1.get(1) == 1);
    }   
}