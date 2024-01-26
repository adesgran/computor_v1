#include "../headers/Equation.hpp"
#include <iostream>
#include <ostream>
#include <string>

int main(int ac, char **av) {
  if (ac != 2)
    std::cout << "1 Argument needed" << std::endl;

  try {
    Equation e(av[1]);
    if (e.polynomial_degree() <= 0) {
      std::cout << "Error: Input is not a polynome" << std::endl;
    }
    std::cout << "Reduced form : " << e.getReducedForm() << std::endl;
    std::cout << "Polynomial degree: " << e.polynomial_degree() << std::endl;
    e.solve();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return (0);
}
