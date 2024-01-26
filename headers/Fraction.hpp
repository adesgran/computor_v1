#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

#include <iostream>
#include <limits>
#include <sstream>
#define ABS(x) ((x) < 0 ? -static_cast<double>(x) : static_cast<double>(x))

class Fraction {
public:
  Fraction();
  Fraction(int i);
  Fraction(double d);
  ~Fraction();
  Fraction(const Fraction &cpy);
  Fraction &operator=(Fraction const &cpy);

  double getNumerator(void) const;
  double getDenominator(void) const;

  Fraction &operator+=(const Fraction &other);
  Fraction &operator-=(const Fraction &other);
  Fraction &operator*=(const Fraction &other);
  Fraction &operator/=(const Fraction &other);

  Fraction &operator+=(int i);
  Fraction &operator-=(int i);
  Fraction &operator*=(int i);
  Fraction &operator/=(int i);

  Fraction &operator+=(double d);
  Fraction &operator-=(double d);
  Fraction &operator*=(double d);
  Fraction &operator/=(double d);

  friend std::ostream &operator<<(std::ostream &out, const Fraction &frac);

  operator double() const;

private:
  double numerator;
  double denominator;

  int getGCD(int a, int b) const;
  void reduce(void);
};

Fraction operator+(Fraction lhs, const Fraction &rhs);
Fraction operator-(Fraction lhs, const Fraction &rhs);
Fraction operator*(Fraction lhs, const Fraction &rhs);
Fraction operator/(Fraction lhs, const Fraction &rhs);

Fraction operator+(const Fraction &frac, int i);
Fraction operator-(const Fraction &frac, int i);
Fraction operator*(const Fraction &frac, int i);
Fraction operator/(const Fraction &frac, int i);
Fraction operator+(int i, const Fraction &frac);
Fraction operator-(int i, const Fraction &frac);
Fraction operator*(int i, const Fraction &frac);
Fraction operator/(int i, const Fraction &frac);

Fraction operator+(const Fraction &frac, double d);
Fraction operator-(const Fraction &frac, double d);
Fraction operator*(const Fraction &frac, double d);
Fraction operator/(const Fraction &frac, double d);
Fraction operator+(double d, const Fraction &frac);
Fraction operator-(double d, const Fraction &frac);
Fraction operator*(double d, const Fraction &frac);
Fraction operator/(double d, const Fraction &frac);

bool operator<(const Fraction &lhs, const Fraction &rhs);
bool operator<=(const Fraction &lhs, const Fraction &rhs);
bool operator>(const Fraction &lhs, const Fraction &rhs);
bool operator>=(const Fraction &lhs, const Fraction &rhs);
bool operator==(const Fraction &lhs, const Fraction &rhs);
bool operator!=(const Fraction &lhs, const Fraction &rhs);

bool operator<(const Fraction &frac, double d);
bool operator<=(const Fraction &frac, double d);
bool operator>(const Fraction &frac, double d);
bool operator>=(const Fraction &frac, double d);
bool operator==(const Fraction &frac, double d);
bool operator!=(const Fraction &frac, double d);

bool operator<(const Fraction &frac, int i);
bool operator<=(const Fraction &frac, int i);
bool operator>(const Fraction &frac, int i);
bool operator>=(const Fraction &frac, int i);
bool operator==(const Fraction &frac, int i);
bool operator!=(const Fraction &frac, int i);

#endif
