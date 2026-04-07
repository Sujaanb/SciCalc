# SciCalc - Scientific Calculator

A comprehensive, feature-rich scientific calculator written in C with proper error handling and modular design.

## Features

### Basic Arithmetic Operations
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/) with zero-checking
- Modulo (%)
- Power (^)

### Scientific Functions
- **Trigonometric**: sin, cos, tan (supports degrees)
- **Logarithmic**: natural log (ln), base-10 log
- **Exponential**: e^x
- **Other**: square root, absolute value, factorial

### User Experience
- Continuous calculation mode (multiple operations without restarting)
- Comprehensive error handling
- Input validation and buffer clearing
- Help menu with detailed information
- Formatted output with up to 6 significant digits
- Beautiful menu interface

## Compilation

### Using Make (Recommended)
```bash
make
```

### Manual Compilation
```bash
gcc -o scicalc calculator.c -lm
```

The `-lm` flag links the math library.

## Usage

### Running the Calculator
```bash
./scicalc
```

### Basic Examples

**Binary Operations:**
```
Operation: +
First operand: 10
Second operand: 20
Result: 10 + 20 = 30
```

**Unary Operations:**
```
Operation: s
Operand: 45
Result: sin(45°) = 0.707107
```

### Supported Operations

| Key | Operation | Type |
|-----|-----------|------|
| `+` | Add | Binary |
| `-` | Subtract | Binary |
| `*` | Multiply | Binary |
| `/` | Divide | Binary |
| `%` | Modulo | Binary |
| `^` | Power | Binary |
| `s` | Sine (degrees) | Unary |
| `c` | Cosine (degrees) | Unary |
| `t` | Tangent (degrees) | Unary |
| `q` | Square Root | Unary |
| `a` | Absolute Value | Unary |
| `l` | Natural Logarithm | Unary |
| `g` | Log Base 10 | Unary |
| `e` | Exponential (e^x) | Unary |
| `f` | Factorial | Unary |
| `h` | Help | Menu |
| `q` | Quit | Menu |

## File Structure

```
SciCalc/
├── calculator.h      # Header file with function declarations
├── calculator.c      # Main calculator implementation with all functions
├── Project.c         # Original calculator (kept for reference)
├── Makefile          # Build configuration
├── README.md         # This file
└── .gitignore        # Git ignore rules
```

## Code Quality Improvements

### Fixed Issues
- ✅ Fixed division by zero logic flaw
- ✅ Added proper newlines to output
- ✅ Implemented input buffer clearing
- ✅ Added comprehensive error handling
- ✅ Improved input validation

### Architecture
- ✅ Modular design with separate header file
- ✅ Well-documented code with comments
- ✅ Clear function organization
- ✅ Error flag handling for edge cases
- ✅ Buffer overflow prevention

### User Experience
- ✅ Interactive menu system
- ✅ Continuous calculation mode
- ✅ Helpful error messages
- ✅ Optional help menu
- ✅ Better precision handling

## Error Handling

The calculator handles the following error cases:
- Division by zero
- Modulo by zero
- Square root of negative numbers
- Logarithm of non-positive numbers
- Factorial of negative numbers or non-integers
- Invalid numeric input
- Invalid operators

## Building

### Requirements
- GCC compiler
- Standard C library
- Math library (libm)

### Build Commands
```bash
# Compile
make

# Run
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

## Examples

### Example 1: Basic Addition
```
Operation: +
First operand: 5.5
Second operand: 3.2
Result: 5.5 + 3.2 = 8.7
```

### Example 2: Scientific Function
```
Operation: s
Operand: 30
Result: sin(30°) = 0.5
```

### Example 3: Error Handling
```
Operation: /
First operand: 10
Second operand: 0
Error: Division by zero is undefined.
```

## Precision

Results are displayed using 6 significant digits by default for better readability. Internally, calculations maintain full double precision.

## Future Enhancements

Possible future improvements:
- Inverse trigonometric functions (arcsin, arccos, arctan)
- Hyperbolic functions (sinh, cosh, tanh)
- Complex number support
- Expression parsing and evaluation
- Calculation history
- GUI interface
- Radian mode toggle
- Custom precision settings

## License

This project is provided as-is for educational purposes.

## Author

Sujaan Bhattacharyya - [GitHub](https://github.com/Sujaanb)

## Version History

### v2.0 (Current)
- Complete rewrite with modular architecture
- Added 9 scientific functions
- Improved error handling
- Better user interface
- Comprehensive documentation

### v1.0 (Original)
- Basic arithmetic operations
- Simple calculator logic