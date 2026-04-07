# SciCalc v2.0 - Scientific Calculator

[![Build Status](https://github.com/Sujaanb/SciCalc/workflows/CI%2FCD/badge.svg)](https://github.com/Sujaanb/SciCalc/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A powerful, modular scientific calculator built in C with support for advanced mathematical operations, expression parsing, calculation history, and an interactive menu system.

## Features

### ✨ Core Functionality
- **Expression Parser**: Supports complex mathematical expressions with proper operator precedence
- **Advanced Math**: Trigonometric, logarithmic, exponential, and statistical functions
- **Constants**: π (pi), e, and φ (golden ratio)
- **Calculation History**: Track and recall previous calculations
- **Custom Precision**: Adjustable output precision (1-15 decimal places)
- **Interactive UI**: User-friendly menu system with color support

### 📚 Supported Operations

**Basic Arithmetic**
```
+   Addition
-   Subtraction
*   Multiplication
/   Division
^   Exponentiation
%   Modulo
```

**Trigonometric Functions (in radians)**
```
sin(x), cos(x), tan(x)
asin(x), acos(x), atan(x)
sin_deg(x), cos_deg(x), tan_deg(x)  # Degree input
```

**Logarithmic & Exponential**
```
ln(x)       - Natural logarithm
log(x)      - Base 10 logarithm
log2(x)     - Base 2 logarithm
log10(x)    - Base 10 logarithm
exp(x)      - Exponential function
```

**Advanced Functions**
```
sqrt(x)     - Square root
cbrt(x)     - Cube root
abs(x)      - Absolute value
floor(x)    - Floor function
ceil(x)     - Ceiling function
round(x)    - Round to nearest integer
factorial(x) - Factorial
```

**Statistical & Combinatorics**
```
C(n,k)      - Combinations
P(n,k)      - Permutations
mean()      - Mean of dataset
median()    - Median of dataset
std_dev()   - Standard deviation
```

## Installation

### Prerequisites
- CMake 3.10+
- GCC, Clang, or MSVC compiler
- Linux/macOS/Windows

### Build from Source

```bash
# Clone the repository
git clone https://github.com/Sujaanb/SciCalc.git
cd SciCalc

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# (Optional) Install
sudo make install
```

### Run Tests
```bash
cmake ..
make
ctest
```

## Usage

### Interactive Mode
```bash
./bin/scicalc
```

Then select option 1 for interactive calculator.

### Examples

```
calc> 2 + 3
Result = [5.000000]

calc> sin(pi/2)
Result = [1.000000]

calc> sqrt(16)
Result = [4.000000]

calc> (5 + 3) * 2
Result = [16.000000]

calc> 2 ^ 10
Result = [1024.000000]

calc> log(100)
Result = [2.000000]

calc> factorial(5)
Result = [120.000000]
```

### Interactive Commands

```
help     - Display help menu
history  - Show calculation history
last     - Display last result
clear    - Clear history
quit     - Exit calculator
```

## Project Structure

```
SciCalc/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── src/
│   ├── main.c              # Main entry point
│   ├── calculator.c/h      # Calculator engine
│   ├── parser.c/h          # Expression parser
│   ├── functions.c/h       # Mathematical functions
│   ├── ui.c/h              # User interface
│   └── history.c/h         # History management
├── tests/
│   ├── test_main.c         # Main test suite
│   ├── test_parser.c       # Parser tests
│   └── test_functions.c    # Function tests
├── docs/
│   └── Doxyfile            # Documentation config
└── .github/
    └── workflows/
        └── ci.yml          # CI/CD pipeline
```

## Architecture

### Modular Design

- **Calculator Engine**: Core evaluation logic
- **Expression Parser**: Recursive descent parser with operator precedence
- **Functions Module**: ~40 mathematical functions
- **UI System**: Interactive menu and input handling
- **History Manager**: Track calculation history

### Design Patterns

- **Separation of Concerns**: Each module handles specific responsibility
- **Error Handling**: Graceful handling of domain errors
- **Memory Management**: Proper allocation and deallocation
- **Modular Testing**: Independent test cases for each module

## Development

### Adding New Functions

1. Declare in `src/functions.h`
2. Implement in `src/functions.c`
3. Register in parser `src/parser.c`
4. Add test in `tests/test_functions.c`

### Building with Debug Info
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Performance

- **Parser**: O(n) where n is expression length
- **Operations**: O(1) for basic, O(log n) for logarithmic
- **History**: O(1) access, O(n) display

## Limitations

- Expression length limited to 256 characters
- History limited to 100 entries
- Floating-point precision follows C's double type
- No complex number support (yet)
- No matrix operations (yet)

## Future Enhancements

- [ ] Complex number support
- [ ] Matrix operations
- [ ] Graphing capabilities
- [ ] GUI version (Qt/GTK+)
- [ ] Web version (WebAssembly)
- [ ] Custom function definitions
- [ ] Scripting support
- [ ] Unit conversion tools

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

### Development Setup

```bash
git clone https://github.com/Sujaanb/SciCalc.git
cd SciCalc
mkdir build && cd build
cmake ..
make
ctest
```

## License

MIT License - see LICENSE file for details

## Author

**Sujaan Bhattacharyya**
- GitHub: [@Sujaanb](https://github.com/Sujaanb)
- Location: Kolkata, India

## Changelog

### v2.0.0 (Current)
- Complete rewrite with modular architecture
- Expression parser with operator precedence
- Extended mathematical functions library
- Interactive menu system
- Calculation history
- Comprehensive test suite
- CMake build system
- Color-coded UI

### v1.0.0 (Original)
- Basic arithmetic operations
- Simple CLI interface

## Support

If you find this project helpful, please:
- ⭐ Star the repository
- 🐛 Report issues
- 💡 Suggest improvements
- 🤝 Contribute code

## FAQ

**Q: How do I use degrees instead of radians?**
A: Use the `_deg` suffixed functions: `sin_deg(90)` instead of `sin(pi/2)`

**Q: Can I save my history?**
A: Currently, history is stored in memory during a session. Export feature coming soon.

**Q: What's the maximum precision?**
A: You can set precision up to 15 decimal places.

**Q: Is this suitable for production?**
A: SciCalc is suitable for educational and general use. For critical scientific applications, consider established libraries like GNU Scientific Library.

---

**Last Updated**: March 2026
