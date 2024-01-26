#ifndef __EQUATION_HPP__
#define __EQUATION_HPP__

#define ABS(x) ((x) < 0 ? -static_cast<double>(x) : static_cast<double>(x))

#include "../headers/Fraction.hpp"
#include "./equation_utils.hpp"
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Equation {
public:
  Equation(void);
  Equation(std::string const &str);
  ~Equation(void);
  Equation(Equation const &cpy);
  Equation &operator=(Equation const &cpy);

  size_t polynomial_degree(void);
  const std::string getReducedForm(void);
  void solve(void);

  Equation &operator+=(const Equation &other);
  Equation &operator-=(const Equation &other);
  Equation &operator*=(const Equation &other);
  Equation &operator/=(const Equation &other);

  friend Equation operator+(Equation lhs, const Equation &rhs);
  friend Equation operator-(Equation lhs, const Equation &rhs);
  friend Equation operator*(Equation lhs, const Equation &rhs);
  friend Equation operator/(Equation lhs, const Equation &rhs);

protected:
  typedef Fraction coeff_type;
  typedef std::vector<coeff_type> content_type;

private:
  Equation handleOperator(const std::string &str, char op, size_t pos);
  Equation tokenize(std::string const &str);
  content_type content;
  void resize_content(void);
};

#endif