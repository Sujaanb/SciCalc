# SciCalc - Scientific Calculator

A feature-rich scientific calculator written in C with improved code quality, error handling, and user experience.

## Features

### Basic Operations
- ✅ Addition (+)
- ✅ Subtraction (-)
- ✅ Multiplication (*)
- ✅ Division (/) with proper error handling
- ✅ Power/Exponentiation (^)

### Scientific Operations
- ✅ Square Root (sqrt)
- ✅ Trigonometric Functions (sin, cos, tan) - input in radians
- ✅ Natural Logarithm (log)
- ✅ Factorial (fact) - supports 0-20

### Additional Features
- ✅ Calculation History - view all previous calculations
- ✅ Input Validation - safe and robust input handling
- ✅ Proper Error Handling - division by zero, invalid operations, etc.
- ✅ User-Friendly Interface - clear menus and prompts
- ✅ Interactive Loop - perform multiple calculations without restarting

## Building the Project

### Prerequisites
- GCC compiler or any C99-compliant compiler
- Make (optional, but recommended)

### Build Instructions

**Using Makefile (recommended):**
```bash
make
./scicalc
```

**Or manually:**
```bash
gcc -Wall -Wextra -pedantic -std=c99 -O2 -o scicalc main.c calculator.c -lm
./scicalc
```

## Usage

Upon running the calculator, you'll see a main menu:

```
=== SciCalc - Scientific Calculator ===
Basic Operations:
  + : Addition
  - : Subtraction
  * : Multiplication
  / : Division
  ^ : Power
Advanced Options:
  s : Scientific Operations
  h : Show History
  q : Quit
====================================
Enter operation:
```

### Example 1: Basic Addition
```
Enter operation: +
Enter first operand: 10
Enter second operand: 20
Result: 10.00 + 20.00 = 30.00
```

### Example 2: Scientific Operations
```
Enter operation: s
=== Scientific Operations ===
  sqrt : Square Root
  sin  : Sine (in radians)
  cos  : Cosine (in radians)
  tan  : Tangent (in radians)
  log  : Natural Logarithm
  fact : Factorial
  back : Return to Main Menu
=============================
Enter operation: sqrt
Enter number: 16
Result: sqrt(16.00) = 4.00
```

### Example 3: View History
```
Enter operation: h
=== Calculation History ===
1. 10.00 + 20.00 = 30.00
2. sqrt(16.00) = 4.00
3. 2.00 ^ 3.00 = 8.00
===========================
```

## Error Handling

The calculator properly handles:
- **Division by zero** - displays error message instead of crashing
- **Invalid operators** - prompts user to enter valid input
- **Invalid input for scientific operations** - square root of negative numbers, log of non-positive numbers
- **Factorial limits** - prevents overflow by limiting factorial to 0-20
- **Input buffer overflow** - safe string handling with proper buffer sizes

## Code Structure

```
SciCalc/
├── calculator.h      # Header file with function declarations
├── calculator.c      # Implementation of calculator functions
├── main.c           # Main program loop and user interface
├── Makefile         # Build configuration
├── README.md        # This file
└── LICENSE          # MIT License
```

### Key Improvements from Original Version

1. **Modular Design** - Separated concerns into multiple files
2. **Proper Error Handling** - Uses error codes and proper validation
3. **Better User Interface** - Clear menus and informative prompts
4. **Code Documentation** - Comprehensive doxygen-style comments
5. **Input Validation** - Safe input handling with buffer overflow protection
6. **History Tracking** - View all previous calculations
7. **Interactive Loop** - Continue calculations without restarting
8. **Compilation Flags** - Wall, Wextra, pedantic for better code quality

## Compilation Flags Explained

- `-Wall` - Enable all common warnings
- `-Wextra` - Enable extra warnings for even better code quality
- `-pedantic` - Enforce strict C99 standard
- `-std=c99` - Use C99 standard
- `-O2` - Optimization level 2 for better performance
- `-lm` - Link with math library (required for math functions)

## Future Improvements

- [ ] Memory register operations (M+, M-, MR, MC)
- [ ] Batch mode for processing multiple operations from file
- [ ] More trigonometric functions (asin, acos, atan)
- [ ] Hyperbolic functions (sinh, cosh, tanh)
- [ ] Unit tests using CUnit framework
- [ ] GUI version using GTK or Qt
- [ ] Complex number support
- [ ] Reverse Polish Notation (RPN) mode

## Testing

To test the calculator, try these operations:

```bash
# Addition
10 + 5 = 15

# Complex calculation
(2 + 3) * 4 = 20 (Note: This requires entering 2+3 first, then multiplying by 4)

# Trigonometry (remember to use radians, not degrees)
sin(π/2) ≈ 1 (use 1.5708 for π/2)

# Factorial
5! = 120
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

Sujaan Bhattacharyya

## Contributing

Feel free to fork this repository and submit pull requests for any improvements!

## Troubleshooting

**Issue:** Compilation error about undefined reference to `sin`, `cos`, etc.
**Solution:** Make sure you're linking with the math library using `-lm` flag.

**Issue:** Calculator crashes on invalid input
**Solution:** The latest version has proper input validation. If you're using the old version, please update to the improvements branch.

**Issue:** Factorial returns 0 for numbers > 20
**Solution:** This is by design to prevent overflow. Factorials grow very quickly and 20! is already 2.4 × 10^18.
