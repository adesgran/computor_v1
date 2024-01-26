#include "../headers/equation_utils.hpp"

std::string trimSpaces(const std::string &str) {
  std::string res;

  size_t start = str.find_first_not_of(' ');
  size_t end = str.find_last_not_of(' ');

  if (start != std::string::npos && end != std::string::npos) {
    res = str.substr(start, end - start + 1);
  }

  return res;
}

size_t findOutsideParentheses(const std::string &str, char c) {
  int nestingLevel = 0;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      nestingLevel++;
    } else if (str[i] == ')') {
      nestingLevel--;
    } else if (str[i] == c && nestingLevel == 0) {
      return i;
    }

    if (nestingLevel < 0) {
      throw std::runtime_error("Error: Unbalanced parentheses.");
    }
  }

  if (nestingLevel != 0) {
    throw std::runtime_error("Error: Unbalanced parentheses.");
  }

  return std::string::npos;
}

size_t findClosingParenthesis(const std::string &str, size_t firstParenthesis) {
  size_t res = std::string::npos;
  int nestingLevel = 1;
  for (size_t i = firstParenthesis + 1; i < str.length(); i++) {
    if (str[i] == '(')
      nestingLevel++;
    else if (str[i] == ')')
      nestingLevel--;
    if (nestingLevel == 0)
      return i;
  }
  return (res);
}

double strToDouble(const std::string &str) {
  char *endptr;
  double res = std::strtod(str.c_str(), &endptr);

  if (!((endptr == str.c_str() + str.length()) && (str.length() > 0)))
    throw std::runtime_error("Error: '" + str +
                             "' is an invalid input for a double");
  return (res);
}

unsigned int strToUInt(const std::string &str) {
  char *endptr;
  unsigned long res = std::strtoul(str.c_str(), &endptr, 10);

  if (!((endptr == str.c_str() + str.length()) && (str.length() > 0) &&
        (res <= UINT_MAX)))
    throw std::runtime_error("Error: '" + str +
                             "' is an invalid input for an unsigned int");
  return static_cast<unsigned int>(res);
}

double babylonianSquareRoot(double x) {
  if (x < 0.0) {
    throw std::runtime_error(
        "Error: Cannot compute square root of a negative number");
  }

  double guess = x / 4.0;

  for (int i = 0; i < 1000; ++i) {
    guess = 0.5 * (guess + x / guess);
  }

  return guess;
}

double babylonianSquareRoot(const Fraction &x) {
  double doubleX = static_cast<double>(x);

  return babylonianSquareRoot(doubleX);
}