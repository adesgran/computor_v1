#include "../headers/Equation.hpp"
#include <iterator>
#include <stdexcept>

Equation::Equation(void) { this->content.resize(1); };

Equation::Equation(std::string const &str) {

  this->content.resize(1);

  int count = 0;
  for (std::string::const_iterator it = str.begin(); it < str.end(); it++) {
    if (*it == '=')
      count++;
  }
  if (count > 1)
    throw std::invalid_argument("Wrong Expression (contain multiples '=')");

  if (count == 1) {
    size_t equal_pos = str.find('=');
    std::string first_elem = trimSpaces(str.substr(0, equal_pos));
    std::string second_elem = trimSpaces(str.substr(equal_pos + 1));
    (*this) += this->tokenize(first_elem);
    (*this) -= this->tokenize(second_elem);

  } else {
    (*this) += this->tokenize(str);
  }
};

Equation::~Equation(void){};

Equation::Equation(Equation const &cpy) { *this = cpy; };

Equation &Equation::operator=(Equation const &cpy) {
  this->content = cpy.content;
  return (*this);
};

size_t Equation::polynomial_degree(void) {
  this->resize_content();
  return (this->content.size() > 0 ? this->content.size() - 1 : 0);
}

const std::string Equation::getReducedForm(void) {
  std::string res;
  bool isFirst = true;
  this->resize_content();

  if (this->content.empty()) {
    return "0 = 0";
  } else if (this->content.size() == 1) {
    std::ostringstream oss;
    oss << this->content[0];
    return (oss.str() + " = 0");
  }

  for (size_t i = 0; i < this->content.size(); i++) {
    if (this->content[i] == 0) {
      continue;
    }
    if (isFirst) {
      isFirst = false;
      if (this->content[i] < 0)
        res += "-";
    } else {
      if (this->content[i] < 0)
        res += " - ";
      else
        res += " + ";
    }

    if (i == 0 || (this->content[i] != 1 && this->content[i] != -1)) {
      std::ostringstream oss;
      oss << ABS(this->content[i]);
      res += oss.str();
    }

    if (i > 0) {
      if (this->content[i] != 1 && this->content[i] != -1)
        res += " * X";
      else
        res += "X";

      if (i > 1) {
        std::ostringstream oss;
        oss << (i);
        res += "^" + oss.str();
      }
    }
  }
  res += " = 0";
  return res;
}

void Equation::solve(void) {
  this->resize_content();
  if (this->content.size() < 2) {
    if (this->content.size() != 1 || this->content[0] == 0)
      std::cout << "Each real number is a solution" << std::endl;
    else
      std::cout << "The equation don't get any solutions" << std::endl;
    return;
  }
  if (this->content.size() > 3) {
    std::cout
        << "The polynomial degree is strictly greater than 2, I can't solve."
        << std::endl;
    return;
  }
  if (this->content.size() == 2) {

    std::cout << "The polynomial degree is 1, the solution is:" << std::endl
              << (-1 * this->content[0] / this->content[1]) << std::endl;
    return;
  }
  coeff_type c = this->content[0];
  coeff_type b = this->content[1];
  coeff_type a = 0;
  if (this->content.size() == 3)
    a = this->content[2];
  std::cout << "Equation is of type c + b * X + a * X^2 with : " << std::endl;
  std::cout << "- a = " << a << std::endl;
  std::cout << "- b = " << b << std::endl;
  std::cout << "- c = " << c << std::endl;

  coeff_type delta = (b * b) - (4 * a * c);
  std::cout << "Delta = b * b - 4 * a * c => Delta = " << delta << std::endl;
  if (delta < 0) {
    std::cout << "Discriminant is strictly negative, the equation don't get "
                 "any solution"
              << std::endl;
    return;
  } else if (delta == 0) {
    std::cout << "Discriminant is null, the solution is:" << std::endl;
    std::cout << (-b / (2 * a)) << std::endl;
  } else {
    std::cout << "Discriminant is strictly positive, the two solutions are:"
              << std::endl;
    coeff_type deltaSqrt = babylonianSquareRoot(delta);
    std::cout << "X1 = " << (-b + deltaSqrt) / (2 * a) << std::endl;
    std::cout << "X2 = " << (-b - deltaSqrt) / (2 * a) << std::endl;
  }
}

Equation &Equation::operator+=(const Equation &other) {
  size_t maxSize = std::max(this->content.size(), other.content.size());
  this->content.resize(maxSize);
  for (size_t i = 0; i < other.content.size(); i++)
    this->content[i] += other.content[i];
  return *this;
}

Equation &Equation::operator-=(const Equation &other) {
  size_t maxSize = std::max(this->content.size(), other.content.size());
  this->content.resize(maxSize);
  for (size_t i = 0; i < other.content.size(); i++)
    this->content[i] -= other.content[i];
  return *this;
}

Equation &Equation::operator*=(const Equation &other) {
  this->resize_content();

  if (this->content.empty() || other.content.empty()) {
    this->content.clear();
    return *this;
  }

  Equation eq(other);
  eq.resize_content();

  if (this->content.empty() || eq.content.empty()) {
    this->content.clear();
    return *this;
  }

  content_type res;
  res.resize(this->content.size() + eq.content.size() - 1);

  for (size_t i = 0; i < this->content.size(); i++) {
    for (size_t j = 0; j < eq.content.size(); j++) {
      res[i + j] += this->content[i] * eq.content[j];
    }
  }
  this->content = res;
  this->resize_content();
  return *this;
}

Equation &Equation::operator/=(const Equation &other) {
  this->resize_content();

  if (this->content.empty() || other.content.empty()) {
    this->content.clear();
    return *this;
  }

  Equation eq(other);
  eq.resize_content();

  if (this->content.empty() || eq.content.empty() || eq.content[0] == 0) {
    throw std::runtime_error("Error: Division by 0 or non-numeric value");
  }

  content_type res;
  res.resize(this->content.size());

  for (size_t i = 0; i < this->content.size(); i++) {
    res[i] = this->content[i] / eq.content[0];
  }
  this->content = res;
  return *this;
}

Equation operator+(Equation lhs, const Equation &rhs) {
  lhs += rhs;
  return lhs;
}

Equation operator-(Equation lhs, const Equation &rhs) {
  lhs -= rhs;
  return lhs;
}

Equation operator*(Equation lhs, const Equation &rhs) {
  lhs *= rhs;
  return lhs;
}

Equation operator/(Equation lhs, const Equation &rhs) {
  lhs /= rhs;
  return lhs;
};

Equation Equation::handleOperator(const std::string &str, char op, size_t pos) {
  if (pos != std::string::npos) {
    const std::string firstPart = trimSpaces(str.substr(0, pos));
    const std::string secondPart = trimSpaces(str.substr(pos + 1));

    if ((op == '+' || op == '*' || op == '/') && (firstPart.length() <= 0)) {
      throw std::runtime_error("Error: Invalid expression forwarding a '" +
                               std::string(1, op) + "' in the context of: '" +
                               str + "'");
    } else if ((op == '+' || op == '*' || op == '/') &&
               (secondPart.length() <= 0 ||
                secondPart.find_first_of("+*/)") == 0)) {
      throw std::runtime_error("Error: Invalid expression following a '" +
                               std::string(1, op) + "' in the context of: '" +
                               str + "'");
    } else if ((op == '-') && (firstPart.length() <= 0)) {
      throw std::runtime_error("Error: Invalid expression forwarding a '" +
                               std::string(1, op) + "' in the context of: '" +
                               str + "'");
    } else if ((op == '-') && (secondPart.length() <= 0 ||
                               secondPart.find_first_of("+-*/)") == 0)) {
      throw std::runtime_error("Error: Invalid expression following a '" +
                               std::string(1, op) + "' in the context of: '" +
                               str + "'");
    }

    Equation res = this->tokenize(firstPart);
    return (op == '+')   ? (res + this->tokenize(secondPart))
           : (op == '-') ? (res - this->tokenize(secondPart))
           : (op == '*') ? (res * this->tokenize(secondPart))
                         : (res / this->tokenize(secondPart));
  }

  return Equation();
};

Equation Equation::tokenize(std::string const &str) {
  Equation res;

  // Check for +,-,*,/ operators outside parentheses
  const char operators[] = {'+', '-', '*', '/'};

  for (const char *op = operators; *op; ++op) {
    size_t pos = findOutsideParentheses(str, *op);
    if (*op == '-' && pos != std::string::npos) {
      const std::string firstPart = trimSpaces(str.substr(0, pos));
      const char c =
          firstPart.empty() ? '(' : firstPart[firstPart.length() - 1];
      const std::string charlist = "(+-*/";
      if (charlist.find(c) != std::string::npos)
        pos = std::string::npos;
    }
    if (pos != std::string::npos)
      return handleOperator(str, *op, pos);
  }

  // Else check for parentheses
  size_t firstParenthesis = str.find_first_of('(');
  if (firstParenthesis != std::string::npos) {
    size_t secondParenthesis = findClosingParenthesis(str, firstParenthesis);
    if (secondParenthesis == std::string::npos)
      throw std::runtime_error(
          "Error: Parenthesis opened but not closed in the context of: '" +
          str + "'");
    const std::string firstPart = trimSpaces(str.substr(0, firstParenthesis));
    const std::string secondPart = trimSpaces(str.substr(
        firstParenthesis + 1, secondParenthesis - firstParenthesis - 1));
    const std::string thirdPart = trimSpaces(str.substr(secondParenthesis + 1));
    res += this->tokenize(secondPart);
    if (firstPart.length() >= 1)
      res *= Equation(firstPart);
    if (thirdPart.length() >= 1)
      res *= Equation(thirdPart);
    return (res);
  }

  // Else check for minus operator without element before
  size_t minusPos = str.find_first_of('-');
  if (minusPos != std::string::npos) {
    const std::string firstPart = trimSpaces(str.substr(0, minusPos));
    const std::string secondPart = trimSpaces(str.substr(minusPos + 1));
    if (!firstPart.empty())
      throw std::runtime_error("Error while processing minus");
    res -= this->tokenize(secondPart);
    return (res);
  }

  // Else
  size_t XPos = str.find_first_of('X');
  if (XPos != std::string::npos) {
    coeff_type coeff = 1;
    if (XPos != 0)
      coeff = strToDouble(str.substr(0, XPos));
    size_t pow = 1;
    if (str.length() > XPos + 1) {
      if (str.length() > XPos + 2 && str[XPos + 1] == '^' &&
          isdigit(str[XPos + 2]))
        pow = strToUInt(str.substr(XPos + 2));
      else
        throw std::runtime_error("Error: Invalid expression : '" + str + "'");
    }
    size_t maxSize = std::max(res.content.size(), pow + 1);
    res.content.resize(maxSize);
    res.content[pow] = coeff;
  } else {
    res.content[0] = strToDouble(str);
  }
  return (res);
}

void Equation::resize_content(void) {
  while (this->content.size() > 1 && this->content.back() == 0) {
    this->content.pop_back();
  }
}
