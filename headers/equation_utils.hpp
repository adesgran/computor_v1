#ifndef __EQUATION_UTILS_HPP__
#define __EQUATION_UTILS_HPP__

#include "./Fraction.hpp"
#include <cctype>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

std::string trimSpaces(const std::string &str);
size_t findOutsideParentheses(const std::string &str, char c);
size_t findClosingParenthesis(const std::string &str, size_t firstParenthesis);
double strToDouble(const std::string &str);
unsigned int strToUInt(const std::string &str);
double babylonianSquareRoot(double x);
double babylonianSquareRoot(const Fraction &x);

#endif