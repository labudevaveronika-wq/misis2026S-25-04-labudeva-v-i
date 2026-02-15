#include <arrayd/arrayd.hpp>
#include <iostream>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <limits>

TEST_CASE("Basic ArrayD functionality") {
    SUBCASE("Constructors") {
        ArrayD empty;
        CHECK(empty.size() == 0);

        ArrayD arr(3);
        CHECK(arr.size() == 3);
        CHECK(arr[0] == 0.0f);
    }

    SUBCASE("Copy and assignment") {
        ArrayD arr1(2);
        arr1[0] = 1.0f;
        arr1[1] = 2.0f;

        ArrayD arr2 = arr1;
        CHECK(arr2[0] == 1.0f);
        CHECK(arr2[1] == 2.0f);

        arr2[0] = 100.0f;
        CHECK(arr1[0] == 1.0f);

        ArrayD arr3;
        arr3 = arr1;
        CHECK(arr3.size() == 2);
    }

    SUBCASE("operator[]") {
        ArrayD arr(3);
        arr[0] = 3.14f;
        CHECK(arr[0] == 3.14f);

        CHECK_THROWS(arr[-1]);
        CHECK_THROWS(arr[10]);

        const ArrayD &carr = arr;
        CHECK(carr[0] == 3.14f);
    }

    SUBCASE("resize()") {
        ArrayD arr(2);
        arr[0] = 1.0f;
        arr[1] = 2.0f;

        arr.resize(4);
        CHECK(arr.size() == 4);
        CHECK(arr[0] == 1.0f);
        CHECK(arr[1] == 2.0f);
        CHECK(arr[2] == 0.0f);
        CHECK(arr[3] == 0.0f);

        arr.resize(1);
        CHECK(arr.size() == 1);
        CHECK(arr[0] == 1.0f);

        CHECK_THROWS(arr.resize(-1));
    }

    SUBCASE("insert()") {
        ArrayD arr(3);
        arr[0] = 1.0f;
        arr[1] = 3.0f;
        arr[2] = 4.0f;

        arr.insert(1, 2.0f);
        CHECK(arr.size() == 4);
        CHECK(arr[0] == 1.0f);
        CHECK(arr[1] == 2.0f);
        CHECK(arr[2] == 3.0f);
        CHECK(arr[3] == 4.0f);

        CHECK_THROWS(arr.insert(-1, 0.0f));
        CHECK_THROWS(arr.insert(10, 0.0f));
    }

    SUBCASE("remove()") {
        ArrayD arr(4);
        arr[0] = 1.0f;
        arr[1] = 2.0f;
        arr[2] = 3.0f;
        arr[3] = 4.0f;

        arr.remove(1);
        CHECK(arr.size() == 3);
        CHECK(arr[0] == 1.0f);
        CHECK(arr[1] == 3.0f);
        CHECK(arr[2] == 4.0f);

        CHECK_THROWS(arr.remove(-1));
        CHECK_THROWS(arr.remove(10));
    }

    SUBCASE("Complex operations") {
        ArrayD arr;

        for (int i = 0; i < 5; ++i) {
            arr.insert(i, static_cast<float>(i + 1));
        }
        CHECK(arr.size() == 5);

        arr.remove(1);
        arr.remove(2);
        CHECK(arr.size() == 3);
        CHECK(arr[0] == 1.0f);
        CHECK(arr[1] == 3.0f);
        CHECK(arr[2] == 5.0f);

        ArrayD arr2 = arr;
        CHECK(arr2.size() == 3);

        arr2.resize(10);
        CHECK(arr2.size() == 10);
    }
}