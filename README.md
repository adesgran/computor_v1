# Computor_V1

## Description
Computor_V1 is a simple polynomial equation solver.

## Usage
1. **Clone the repository:**
    ```bash
    git clone https://github.com/adesgran/computor_v1.git
    cd computor_v1
    ```

2. **Build the project:**
    ```bash
    make
    ```

3. **Run the program with an equation:**
    ```bash
    ./computor "2X^2 - 3X + 6 = 0"
    ```
    Replace the equation with your own polynomial equation.

4. **Clean up build files:**
    ```bash
    make clean
    ```

## Supported Equations
The program supports equations of the form `aX^2 + bX + c = dX^2 + eX + f`.

## Notes
- Ensure you have a C++ compiler installed on your system.
- The makefile generates an executable named 'computor'.

## License
This project is licensed under the [MIT License](LICENSE).
