#include "complex.hpp"


Complex operator-(const Complex & lhs, const Complex & rhs);



Complex::Complex(const double real)
    : Complex(real, 0.0)
{
}

Complex::Complex(const double real, const double imaginary)
    : re(real)
    , im(imaginary)
{
}





Complex operator+(const Complex& lhs, const Complex& rhs)
{ 
    Complex sum(lhs);
    sum += rhs;
    return sum;
}
Complex operator+(const Complex &lhs, const double rhs)
{
    return Complex(rhs) += lhs;
}
Complex operator+(const double lhs, const Complex &rhs)
{
    return Complex(lhs) + rhs;
}






Complex operator-(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}
Complex operator-(const Complex &lhs, const double rhs)
{
    return Complex(rhs) -= lhs;
}
Complex operator-(const double lhs, const Complex &rhs)
{
    return Complex(lhs) -= rhs;
}






Complex operator*(const Complex &lhs, const Complex &rhs)
{
    return Complex(rhs) *= lhs;
}
Complex operator*(const Complex &lhs, const double rhs)
{
    return Complex(rhs) *= lhs;
}
Complex operator*(const double lhs, const Complex &rhs)
{
    return Complex(lhs) *= rhs;
}





Complex operator/(const Complex& lhs, const Complex& rhs)
{
    return Complex(lhs) /= rhs;
}
Complex operator/(const Complex& lhs, const double rhs)
{
    return Complex(lhs) /= rhs;
}
Complex operator/(const double lhs, const Complex& rhs)
{
    return Complex(rhs) /= lhs;
}





Complex& Complex::operator+=(const Complex& rhs)
{ 
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

Complex &Complex::operator*=(const Complex &rhs)
{ 
    re *= rhs.re;
    im *= rhs.im;
    return *this;
}

Complex& Complex::operator*=(const double rhs)
{
    re *= rhs;
    im *= rhs;
    return *this;    
}

Complex &Complex::operator/=(const Complex &rhs)
{
    re /= rhs.re;
    im /= rhs.im;
    return *this;
}

Complex &Complex::operator/=(const double rhs)
{
    if (rhs != 0) {
        re /= rhs;
        return *this;
    }
    else {
        throw std::invalid_argument("You cant divide by zero");
    }
}









std::ostream& Complex::writeTo(std::ostream& ostrm) const
{
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}
std::istream & Complex::readFrom(std::istream & istrm)
{ 
    char leftBrace(0);
    double real(0.0);
    char comma(0);
    double imaganary(0.0);
    char rightBrace(0);
    istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;
    if (istrm.good()) {
        if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma)
            && (Complex::rightBrace == rightBrace)) {
            re = real;
            im = imaganary;
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}

