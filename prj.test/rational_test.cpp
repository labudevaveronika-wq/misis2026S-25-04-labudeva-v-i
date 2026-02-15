#include <iostream>
#include <sstream>
#include <cassert>
#include "../prj.labs/rational/rational.hpp"

void test_constructors() {
    std::cout << "Testing constructors..." << std::endl;

    Rational r1;
    assert(r1.getNumerator() == 0);
    assert(r1.getDenominator() == 1);
    std::cout << "Default constructor: PASS" << std::endl;

    Rational r2(5);
    assert(r2.getNumerator() == 5);
    assert(r2.getDenominator() == 1);
    std::cout << "Single argument constructor: PASS" << std::endl;
    
    Rational r3(6, 8);
    assert(r3.getNumerator() == 3);
    assert(r3.getDenominator() == 4);
    std::cout << "Two argument constructor (positive): PASS" << std::endl;

    Rational r4(3, -9);
    assert(r4.getNumerator() == -1);
    assert(r4.getDenominator() == 3);
    std::cout << "Two argument constructor (negative denominator): PASS" << std::endl;

    Rational r5(-2, -4);
    assert(r5.getNumerator() == 1);
    assert(r5.getDenominator() == 2);
    std::cout << "Two argument constructor (both negative): PASS" << std::endl;
    
    std::cout << "All constructor tests passed!\n" << std::endl;
}

void test_comparisons() {
    std::cout << "Testing comparisons..." << std::endl;
    
    Rational a(1, 3);
    Rational b(2, 6);
    Rational c(1, 4);

    assert(a == b);
    assert(a != c);
    assert(!(a == c));
    assert(!(a != b));
    std::cout << "Equality/inequality: PASS" << std::endl;

    Rational d(1, 2);
    Rational e(1, 3);
    assert(d > e);
    assert(e < d);
    assert(d >= d);
    assert(e <= e);
    assert(d >= e);
    assert(e <= d);
    std::cout << "Order comparisons: PASS" << std::endl;

    Rational zero(0, 1);
    Rational positive(1, 2);
    Rational negative(-1, 2);
    assert(zero < positive);
    assert(negative < zero);
    assert(negative < positive);
    std::cout << "Edge cases: PASS" << std::endl;
    
    std::cout << "All comparison tests passed!\n" << std::endl;
}

void test_arithmetic_operations() {
    std::cout << "Testing arithmetic operations..." << std::endl;

    Rational a(1, 4);
    Rational b(1, 3);
    Rational result1 = a + b;
    assert(result1.getNumerator() == 7);
    assert(result1.getDenominator() == 12);
    std::cout << "Addition: PASS" << std::endl;

    Rational c(3, 4);
    Rational d(1, 2);
    Rational result2 = c - d;
    assert(result2.getNumerator() == 1);
    assert(result2.getDenominator() == 4);
    std::cout << "Subtraction: PASS" << std::endl;
    
    Rational e(2, 3);
    Rational f(3, 4);
    Rational result3 = e * f;
    assert(result3.getNumerator() == 1);
    assert(result3.getDenominator() == 2);
    std::cout << "Multiplication: PASS" << std::endl;
    
    // Division
    Rational g(2, 5);
    Rational h(3, 7);
    Rational result4 = g / h;
    assert(result4.getNumerator() == 14);
    assert(result4.getDenominator() == 15);
    std::cout << "Division: PASS" << std::endl;
    
    std::cout << "All arithmetic tests passed!\n" << std::endl;
}

void test_compound_assignment() {
    std::cout << "Testing compound assignment..." << std::endl;

    Rational r1(1, 2);
    r1 += Rational(1, 3);
    assert(r1.getNumerator() == 5);
    assert(r1.getDenominator() == 6);
    std::cout << "+= operator: PASS" << std::endl;
    

    Rational r2(3, 4);
    r2 -= Rational(1, 4);
    assert(r2.getNumerator() == 1);
    assert(r2.getDenominator() == 2);
    std::cout << "-= operator: PASS" << std::endl;

    Rational r3(2, 3);
    r3 *= Rational(3, 2);
    assert(r3.getNumerator() == 1);
    assert(r3.getDenominator() == 1);
    std::cout << "*= operator: PASS" << std::endl;
    
    Rational r4(3, 4);
    r4 /= Rational(2, 3);
    assert(r4.getNumerator() == 9);
    assert(r4.getDenominator() == 8);
    std::cout << "/= operator: PASS" << std::endl;
    
    std::cout << "All compound assignment tests passed!\n" << std::endl;
}

void test_mixed_arithmetic() {
    std::cout << "Testing mixed arithmetic with integers..." << std::endl;
    
    Rational r(2, 3);
    
    assert((r + 2) == Rational(8, 3));
    assert((r - 1) == Rational(-1, 3));
    assert((r * 3) == Rational(2, 1));
    assert((r / 2) == Rational(1, 3));
    std::cout << "Rational op int: PASS" << std::endl;

    assert((2 + r) == Rational(8, 3));
    assert((1 - r) == Rational(1, 3));
    assert((3 * r) == Rational(2, 1));
    assert((2 / r) == Rational(3, 1));
    std::cout << "int op Rational: PASS" << std::endl;

    Rational r2(1, 4);
    r2 += 1;
    assert(r2 == Rational(5, 4));
    
    r2 -= 1;
    assert(r2 == Rational(1, 4));
    
    r2 *= 4;
    assert(r2 == Rational(1, 1));
    
    r2 /= 2;
    assert(r2 == Rational(1, 2));
    std::cout << "Compound assignments with integers: PASS" << std::endl;
    
    std::cout << "All mixed arithmetic tests passed!\n" << std::endl;
}

void test_io_operations() {
    std::cout << "Testing I/O operations..." << std::endl;
    
    Rational r1(3, 5);
    std::ostringstream oss1;
    oss1 << r1;
    assert(oss1.str() == "3/5");
    std::cout << "Output operator: PASS" << std::endl;

    Rational r2;
    std::istringstream iss1("7/8");
    iss1 >> r2;
    assert(r2.getNumerator() == 7);
    assert(r2.getDenominator() == 8);
    std::cout << "Input operator (valid): PASS" << std::endl;
    
    Rational r3;
    std::istringstream iss2("4/6");
    iss2 >> r3;
    assert(r3.getNumerator() == 2);
    assert(r3.getDenominator() == 3);
    std::cout << "Input operator (normalized): PASS" << std::endl;
    
    Rational r4;
    std::istringstream iss3("-3/4");
    iss3 >> r4;
    assert(r4.getNumerator() == -3);
    assert(r4.getDenominator() == 4);
    std::cout << "Input operator (negative): PASS" << std::endl;
    
    std::cout << "All I/O tests passed!\n" << std::endl;
}

void test_edge_cases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    Rational zero;
    assert(zero.getNumerator() == 0);
    assert(zero.getDenominator() == 1);
    
    Rational result1 = zero + Rational(1, 2);
    assert(result1 == Rational(1, 2));
    
    Rational result2 = zero * Rational(3, 4);
    assert(result2 == zero);
    std::cout << "Zero value: PASS" << std::endl;
    
    Rational one(1);
    assert(one.getNumerator() == 1);
    assert(one.getDenominator() == 1);
    
    Rational result3 = one * Rational(5, 7);
    assert(result3 == Rational(5, 7));
    std::cout << "One value: PASS" << std::endl;
    
    std::cout << "All edge case tests passed!\n" << std::endl;
}

void demo_operations() {
    
    Rational a(1, 4);
    Rational b(1, 3);
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;

    std::cout << "a + 2 = " << (a + 2) << std::endl;
    std::cout << "3 * b = " << (3 * b) << std::endl;
    
}

int main() {
    test_constructors();
    test_comparisons();
    test_arithmetic_operations();
    test_compound_assignment();
    test_mixed_arithmetic();
    test_io_operations();
    test_edge_cases();
    return 0;
}
