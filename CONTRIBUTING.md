# Contributing to SciCalc

Thank you for your interest in contributing to SciCalc! This document provides guidelines and instructions for contributing.

## Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on ideas, not individuals
- Help others learn and grow

## Getting Started

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/SciCalc.git`
3. Create a branch: `git checkout -b feature/your-feature-name`
4. Make your changes
5. Test your changes: `make test`
6. Commit with clear messages: `git commit -m "Add feature: ..."` 
7. Push to your fork: `git push origin feature/your-feature-name`
8. Open a Pull Request

## Development Setup

### Requirements
- GCC or Clang compiler
- GNU Make
- Optional: Valgrind for memory checking
- Optional: cppcheck for static analysis

### Building

```bash
make              # Build the project
make test         # Run tests
make debug        # Debug build with symbols
make memcheck     # Check for memory leaks
make analyze      # Static code analysis
```

## Code Style

### Naming Conventions
- Functions: `snake_case` (e.g., `calc_add`)
- Variables: `snake_case` (e.g., `result_value`)
- Constants: `UPPER_CASE` (e.g., `MAX_HISTORY`)
- Types: `PascalCase` (e.g., `CalculationResult`)

### Formatting
- Use 4 spaces for indentation
- Maximum line length: 100 characters
- Use `clang-format` for automatic formatting: `make format`

### Documentation
- Add Doxygen-style comments to all functions
- Document parameters and return values
- Explain complex algorithms

### Example Function

```c
/**
 * @brief Calculate the sum of two numbers
 * @param num1 First number
 * @param num2 Second number
 * @return CalculationResult structure with result and error code
 * 
 * This function adds two floating-point numbers and checks for overflow.
 */
CalculationResult calc_add(double num1, double num2) {
    double result = num1 + num2;
    
    if (fabs(result) > DBL_MAX) {
        return create_result(0, ERR_OVERFLOW, "Addition result overflow");
    }
    
    return create_result(result, ERR_SUCCESS, NULL);
}
```

## Testing

- Write tests for all new features
- Ensure tests pass before submitting PR
- Aim for high code coverage
- Test edge cases and error conditions

### Running Tests

```bash
make test         # Run all unit tests
```

### Writing Tests

Add tests to `tests/test_calculator.c`:

```c
void test_my_feature(void) {
    printf("  Testing: my_feature");
    CalculationResult result = my_function(5.0);
    ASSERT_EQUAL(result.value, 10.0, EPSILON);
}
```

## Commit Messages

Use clear, descriptive commit messages:

```
[ADD] New feature: trigonometric functions
[FIX] Division by zero error handling
[IMPROVE] Performance optimization
[DOCS] Update README with examples
[TEST] Add unit tests for parser
[REFACTOR] Reorganize code structure
[RELEASE] Version 1.0.0 release
```

## Pull Requests

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] New feature
- [ ] Bug fix
- [ ] Documentation
- [ ] Performance improvement

## Testing
- [ ] Unit tests added
- [ ] All tests passing
- [ ] Memory check passed
- [ ] No compiler warnings

## Checklist
- [ ] Code follows style guidelines
- [ ] Comments added for complex code
- [ ] Documentation updated
- [ ] No hardcoded values
```

## Adding New Operations

### Steps

1. Add function prototype to `include/calculator.h`
2. Implement in `src/calculator.c`
3. Add tests to `tests/test_calculator.c`
4. Update `include/parser.h` with operation type if needed
5. Document in README.md
6. Run `make test memcheck analyze`

### Example: Adding Square Operation

**Header (calculator.h)**:
```c
CalculationResult calc_square(double num);
```

**Implementation (calculator.c)**:
```c
CalculationResult calc_square(double num) {
    double result = num * num;
    return create_result(result, ERR_SUCCESS, NULL);
}
```

**Test (test_calculator.c)**:
```c
printf("  Testing: square(5) = 25");
CalculationResult result = calc_square(5.0);
ASSERT_EQUAL(result.value, 25.0, EPSILON);
```

## Reporting Issues

### Issue Template

```markdown
## Description
Clear description of the issue

## Steps to Reproduce
1. Build with `make`
2. Run `./bin/scicalc`
3. Enter operation: ...

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Environment
- OS: Linux/macOS/Windows
- Compiler: GCC/Clang version
- Build command: make/make debug
```

## Review Process

1. Code review by maintainers
2. Automated tests must pass
3. Feedback addressed
4. Approval and merge

## Recognition

Contributors will be acknowledged in:
- CONTRIBUTORS.md file
- GitHub contributors page
- Release notes

## Questions?

Open an issue or contact: sujaan@example.com

---

Thank you for contributing to SciCalc! 🚀