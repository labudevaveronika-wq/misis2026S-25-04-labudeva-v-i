#include <numeric>
#include <cmath>
#include <stdexcept>
#include "rational.hpp"

// Вспомогательная функция для НОД
int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Конструкторы
Rational::Rational() : numerator(0), denominator(1) {}
Rational::Rational(int a) : numerator(a), denominator(1) {}
Rational::Rational(int a, int b) : numerator(a), denominator(b) { 
    if (b == 0) throw std::invalid_argument("Denominator cannot be zero");
    normalize();
}

// Геттеры
int Rational::getNumerator() const { return numerator; }
int Rational::getDenominator() const { return denominator; }

// Нормализация дроби
void Rational::normalize() {
    if (denominator == 0) {
        throw std::invalid_argument("Zero denominator in Rational");
    }
    
    // Обработка знаков
    if ((denominator < 0) && (numerator < 0)) {
        denominator = std::abs(denominator);
        numerator = std::abs(numerator);
    }
    else if (denominator < 0) {
        numerator = -numerator;
        denominator = std::abs(denominator);
    }
    
    // Сокращение дроби
    const int g = gcd(numerator, denominator);  // Используем нашу функцию gcd
    if (g != 0) {
        numerator /= g;
        denominator /= g;
    }
}

// Операторы сравнения
bool Rational::operator==(const Rational& r) const {
    return (numerator == r.numerator) && (denominator == r.denominator);
}

bool Rational::operator!=(const Rational& r) const {
    return (numerator != r.numerator) || (denominator != r.denominator);
}

bool Rational::operator>(const Rational& r) const {
    return ((numerator * r.denominator) > (r.numerator * denominator));
}

bool Rational::operator>=(const Rational& r) const {
    return ((numerator * r.denominator) >= (r.numerator * denominator));
}

bool Rational::operator<(const Rational& r) const {
    return ((numerator * r.denominator) < (r.numerator * denominator));
}

bool Rational::operator<=(const Rational& r) const {
    return ((numerator * r.denominator) <= (r.numerator * denominator));
}

// Составные операторы с Rational
Rational& Rational::operator+=(const Rational& rhs) {
    numerator = numerator * rhs.denominator + rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    numerator = numerator * rhs.denominator - rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    numerator *= rhs.denominator;
    denominator *= rhs.numerator;
    normalize();
    return *this;
}

// Составные операторы с int
Rational& Rational::operator+=(int rhs) {
    return *this += Rational(rhs);
}

Rational& Rational::operator-=(int rhs) {
    return *this -= Rational(rhs);
}

Rational& Rational::operator*=(int rhs) {
    return *this *= Rational(rhs);
}

Rational& Rational::operator/=(int rhs) {
    return *this /= Rational(rhs);
}

// Ввод/вывод
std::ostream& Rational::writeTo(std::ostream& ostrm) const {
    ostrm << numerator << separator << denominator;
    return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm) {
    int num, den;
    char sep;
    istrm >> num >> sep >> den;
    if (istrm && sep == separator) {
        numerator = num;
        denominator = den;
        normalize();
    } else {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

// Внешние операторы ввода/вывода
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return r.writeTo(os);
}

std::istream& operator>>(std::istream& istrm, Rational& r) {
    return r.readFrom(istrm);
}

// Внешние арифметические операторы
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational operator+(const Rational& lhs, int rhs) {
    return lhs + Rational(rhs);
}

Rational operator-(const Rational& lhs, int rhs) {
    return lhs - Rational(rhs);
}

Rational operator*(const Rational& lhs, int rhs) {
    return lhs * Rational(rhs);
}

Rational operator/(const Rational& lhs, int rhs) {
    return lhs / Rational(rhs);
}

Rational operator+(int lhs, const Rational& rhs) {
    return Rational(lhs) + rhs;
}

Rational operator-(int lhs, const Rational& rhs) {
    return Rational(lhs) - rhs;
}

Rational operator*(int lhs, const Rational& rhs) {
    return Rational(lhs) * rhs;
}

Rational operator/(int lhs, const Rational& rhs) {
    return Rational(lhs) / rhs;
}

// Статическая переменная
const char Rational::separator = '/';

