#ifndef RATIONAL_RATIONAL_HPP
#define RATIONAL_RATIONAL_HPP

#include <iostream>
#include <sstream>
#include <cstdint>

class Rational {
private:
    int numerator;
    int denominator;

    void normalize();

public:
    Rational();
    Rational(int a);
    Rational(int a, int b);
    ~Rational() = default;

    int getNumerator() const;
    int getDenominator() const;

    bool operator==(const Rational& r) const;
    bool operator!=(const Rational& r) const;
    bool operator>(const Rational& r) const;
    bool operator>=(const Rational& r) const;
    bool operator<(const Rational& r) const;
    bool operator<=(const Rational& r) const;

    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    Rational& operator+=(int rhs);
    Rational& operator-=(int rhs);
    Rational& operator*=(int rhs);
    Rational& operator/=(int rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    std::istream& readFrom(std::istream& istrm);

    static const char separator;
};

// Объявления внешних операторов
Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, int rhs);
Rational operator-(const Rational& lhs, int rhs);
Rational operator*(const Rational& lhs, int rhs);
Rational operator/(const Rational& lhs, int rhs);

Rational operator+(int lhs, const Rational& rhs);
Rational operator-(int lhs, const Rational& rhs);
Rational operator*(int lhs, const Rational& rhs);
Rational operator/(int lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& r);
std::istream& operator>>(std::istream& istrm, Rational& r);

#endif