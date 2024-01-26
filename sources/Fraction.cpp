#include "../headers/Fraction.hpp"

Fraction::Fraction() : numerator(0.0), denominator(1.0) {}

Fraction::Fraction(int i)
    : numerator(static_cast<double>(i)), denominator(1.0) {}

Fraction::Fraction(double d) : numerator(d), denominator(1.0) {}

Fraction::~Fraction() {}

Fraction::Fraction(const Fraction &cpy)
    : numerator(cpy.numerator), denominator(cpy.denominator) {}

Fraction &Fraction::operator=(Fraction const &cpy) {
  this->denominator = cpy.getDenominator();
  this->numerator = cpy.getNumerator();
  return (*this);
}

double Fraction::getNumerator(void) const { return this->numerator; }

double Fraction::getDenominator(void) const { return this->denominator; }

int Fraction::getGCD(int a, int b) const {
  return b == 0 ? a : getGCD(b, a % b);
}

void Fraction::reduce() {
  int gcd = getGCD(static_cast<int>(numerator), static_cast<int>(denominator));
  numerator /= gcd;
  denominator /= gcd;
}

Fraction &Fraction::operator+=(const Fraction &other) {
  numerator = numerator * other.denominator + other.numerator * denominator;
  denominator *= other.denominator;
  return *this;
}

Fraction &Fraction::operator-=(const Fraction &other) {
  numerator = numerator * other.denominator - other.numerator * denominator;
  denominator *= other.denominator;
  return *this;
}

Fraction &Fraction::operator*=(const Fraction &other) {
  numerator *= other.numerator;
  denominator *= other.denominator;
  return *this;
}

Fraction &Fraction::operator/=(const Fraction &other) {
  numerator *= other.denominator;
  denominator *= other.numerator;
  return *this;
}

Fraction operator+(Fraction lhs, const Fraction &rhs) {
  lhs += rhs;
  return lhs;
};
Fraction operator-(Fraction lhs, const Fraction &rhs) {
  lhs -= rhs;
  return lhs;
};
Fraction operator*(Fraction lhs, const Fraction &rhs) {
  lhs *= rhs;
  return lhs;
};
Fraction operator/(Fraction lhs, const Fraction &rhs) {
  lhs /= rhs;
  return lhs;
};

Fraction operator+(const Fraction &frac, int i) { return frac + Fraction(i); }

Fraction operator-(const Fraction &frac, int i) {
  return Fraction(frac) - Fraction(i);
}

Fraction operator*(const Fraction &frac, int i) { return frac * Fraction(i); }

Fraction operator/(const Fraction &frac, int i) {
  return Fraction(frac) / Fraction(i);
}

Fraction operator+(int i, const Fraction &frac) { return frac + Fraction(i); }

Fraction operator-(int i, const Fraction &frac) { return Fraction(i) - frac; }

Fraction operator*(int i, const Fraction &frac) { return frac * Fraction(i); }

Fraction operator/(int i, const Fraction &frac) { return Fraction(i) / frac; }

Fraction operator+(const Fraction &frac, double d) {
  Fraction result = frac;
  result += Fraction(d);
  return result;
}

Fraction operator-(const Fraction &frac, double d) {
  Fraction result = frac;
  result -= Fraction(d);
  return result;
}

Fraction operator*(const Fraction &frac, double d) {
  Fraction result = frac;
  result *= Fraction(d);
  return result;
}

Fraction operator/(const Fraction &frac, double d) {
  Fraction result = frac;
  result /= Fraction(d);
  return result;
}

Fraction operator+(double d, const Fraction &frac) { return frac + d; }

Fraction operator-(double d, const Fraction &frac) {
  return Fraction(d) - frac;
}

Fraction operator*(double d, const Fraction &frac) { return frac * d; }

Fraction operator/(double d, const Fraction &frac) {
  return Fraction(d) / frac;
}

Fraction &Fraction::operator+=(int i) {
  *this += Fraction(i);
  return *this;
}

Fraction &Fraction::operator-=(int i) {
  *this -= Fraction(i);
  return *this;
}

Fraction &Fraction::operator*=(int i) {
  *this *= Fraction(i);
  return *this;
}

Fraction &Fraction::operator/=(int i) {
  *this /= Fraction(i);
  return *this;
}

Fraction &Fraction::operator+=(double d) {
  *this += Fraction(d);
  return *this;
}

Fraction &Fraction::operator-=(double d) {
  *this -= Fraction(d);
  return *this;
}

Fraction &Fraction::operator*=(double d) {
  *this *= Fraction(d);
  return *this;
}

Fraction &Fraction::operator/=(double d) {
  *this /= Fraction(d);
  return *this;
}

std::ostream &operator<<(std::ostream &out, const Fraction &frac) {
  Fraction reduced = frac;
  reduced.reduce();
  out << reduced.getNumerator() *
             (reduced.getDenominator() / ABS(reduced.getDenominator()));
  if (ABS(reduced.getDenominator()) != 1.0) {
    out << "/" << ABS(reduced.getDenominator());
  }
  return out;
}

bool operator<(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) < static_cast<double>(rhs);
}

bool operator<=(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) <= static_cast<double>(rhs);
}

bool operator>(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) > static_cast<double>(rhs);
}

bool operator>=(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) >= static_cast<double>(rhs);
}

bool operator==(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) == static_cast<double>(rhs);
}

bool operator!=(const Fraction &lhs, const Fraction &rhs) {
  return static_cast<double>(lhs) != static_cast<double>(rhs);
}

bool operator<(const Fraction &frac, double d) {
  return static_cast<double>(frac) < d;
}

bool operator<=(const Fraction &frac, double d) {
  return static_cast<double>(frac) <= d;
}

bool operator>(const Fraction &frac, double d) {
  return static_cast<double>(frac) > d;
}

bool operator>=(const Fraction &frac, double d) {
  return static_cast<double>(frac) >= d;
}

bool operator==(const Fraction &frac, double d) {
  return static_cast<double>(frac) == d;
}

bool operator!=(const Fraction &frac, double d) {
  return static_cast<double>(frac) != d;
}

bool operator<(const Fraction &frac, int i) {
  return static_cast<double>(frac) < static_cast<double>(i);
}

bool operator<=(const Fraction &frac, int i) {
  return static_cast<double>(frac) <= static_cast<double>(i);
}

bool operator>(const Fraction &frac, int i) {
  return static_cast<double>(frac) > static_cast<double>(i);
}

bool operator>=(const Fraction &frac, int i) {
  return static_cast<double>(frac) >= static_cast<double>(i);
}

bool operator==(const Fraction &frac, int i) {
  return static_cast<double>(frac) == static_cast<double>(i);
}

bool operator!=(const Fraction &frac, int i) {
  return static_cast<double>(frac) != static_cast<double>(i);
}

Fraction::operator double() const {
  if (denominator == 0) {
    return (numerator < 0) ? -std::numeric_limits<double>::infinity()
                           : std::numeric_limits<double>::infinity();
  }

  return static_cast<double>(numerator) / denominator;
}