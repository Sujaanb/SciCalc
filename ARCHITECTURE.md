# SciCalc Architecture Documentation

## Overview

SciCalc is built using a modular architecture with clear separation of concerns:

```
┌─────────────────────────────────────┐
│      User Interface Layer (UI)      │
│   Interactive menus, input/output   │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│      Calculator Layer               │
│  Main engine, coordinates modules   │
└──────────────┬──────────────────────┘
               │
    ┌──────────┼──────────┐
    │          │          │
┌───▼──┐ ┌────▼────┐ ┌───▼──────┐
│Parser│ │Functions│ │History   │
│      │ │         │ │Management│
└──────┘ └─────────┘ └──────────┘
```

## Module Descriptions

### 1. UI Module (ui.c/ui.h)
**Purpose**: Handle all user interaction and display

**Key Functions**:
- `ui_run_interactive()` - Main interactive loop
- `ui_show_main_menu()` - Display main menu
- `ui_get_input()` - Safe input handling
- `ui_display_result()` - Formatted result output
- `ui_print_colored()` - ANSI color output

**Responsibilities**:
- Menu navigation
- Input validation
- Result formatting
- Color/styling

### 2. Calculator Module (calculator.c/calculator.h)
**Purpose**: Core calculator engine

**Key Functions**:
- `calculator_new()` - Initialize calculator
- `calculator_evaluate()` - Evaluate expressions
- `calculator_set_precision()` - Set output precision
- `calculator_get_last_result()` - Retrieve last result

**Data Structure**:
```c
typedef struct {
    double last_result;     // Previous calculation result
    int precision;          // Output decimal places
    bool show_history;      // Show history flag
    int history_count;      // Number of history entries
} Calculator;
```

### 3. Parser Module (parser.c/parser.h)
**Purpose**: Parse and evaluate mathematical expressions

**Algorithm**: Recursive Descent Parser

**Operator Precedence** (highest to lowest):
1. Parentheses: `()`
2. Functions: `sin()`, `sqrt()`, etc.
3. Exponentiation: `^`
4. Multiplication/Division/Modulo: `*`, `/`, `%`
5. Addition/Subtraction: `+`, `-`

**Example Parsing**:
```
Expression: (2 + 3) * sin(pi/2)

Parse Tree:
        *
       / \
      +   sin
     / \   |
    2   3  /
         / \
        pi  2
```

**Key Functions**:
- `parser_evaluate()` - Main entry point
- `parse_expression()` - Handle +, -
- `parse_term()` - Handle *, /, %
- `parse_exponent()` - Handle ^
- `parse_factor()` - Handle numbers, functions, parentheses

### 4. Functions Module (functions.c/functions.h)
**Purpose**: Library of ~40 mathematical functions

**Categories**:

1. **Basic Arithmetic** (6 functions)
   - add, subtract, multiply, divide, power, modulo

2. **Trigonometric** (6 functions)
   - sin, cos, tan, asin, acos, atan

3. **Logarithmic/Exponential** (5 functions)
   - ln, log10, log2, exp

4. **Root Functions** (3 functions)
   - sqrt, cbrt, abs

5. **Rounding** (3 functions)
   - floor, ceil, round

6. **Statistical** (3 functions)
   - mean, median, std_dev

7. **Combinatorics** (3 functions)
   - factorial, combination, permutation

8. **Constants** (3 values)
   - PI, E, GOLDEN_RATIO

### 5. History Module (history.c/history.h)
**Purpose**: Track calculation history

**Data Structure**:
```c
typedef struct {
    char expression[256];   // Input expression
    double result;          // Calculation result
    time_t timestamp;       // When calculated
} HistoryEntry;

typedef struct {
    HistoryEntry entries[100];  // History array
    int count;                   // Number of entries
    int current_index;           // Current position
} History;
```

**Key Functions**:
- `history_add()` - Add to history
- `history_prev()` - Navigate backward
- `history_next()` - Navigate forward
- `history_display()` - Show all entries
- `history_clear()` - Clear history

## Data Flow

### Basic Calculation Flow

```
User Input
    |
    v
[UI Layer]
  Input validation
    |
    v
[Calculator Layer]
  coordinate evaluation
    |
    v
[Parser]
  Tokenize & parse
    |
    v
[Functions]
  Compute operations
    |
    v
[Result]
    |
    v
[History]
  Record entry
    |
    v
[UI]
  Display result
```

## Error Handling

### Error Types

1. **Domain Errors**
   - `sqrt(-1)` → Returns 0.0
   - `log(0)` → Returns 0.0
   - `asin(2)` → Returns 0.0

2. **Parsing Errors**
   - Invalid expression → Returns false
   - Unmatched parentheses → Returns false
   - Unknown function → Treats as 0

3. **Runtime Errors**
   - Division by zero → Returns 0.0
   - Modulo by zero → Returns 0.0

## Memory Management

- **Stack-based**: Functions use local variables
- **Heap-based**: Calculator, History, and History entries
- **Cleanup**: All allocated memory freed on exit
- **No memory leaks**: Verified with valgrind

## Performance Characteristics

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Parse expression | O(n) | O(d) |
| Basic operation | O(1) | O(1) |
| Transcendental fn | O(1)* | O(1) |
| History lookup | O(1) | O(1) |
| History display | O(n) | O(1) |

*Library functions from math.h

## Extending SciCalc

### Adding a New Function

1. **Header** (functions.h):
```c
double func_myfunction(double x);
```

2. **Implementation** (functions.c):
```c
double func_myfunction(double x) {
    return x * 2;  // Example
}
```

3. **Parser** (parser.c, in `apply_function()`):
```c
if (strcmp(func_name, "myfunction") == 0) 
    return func_myfunction(arg);
```

4. **Tests** (tests/test_functions.c):
```c
ASSERT_EQUAL(func_myfunction(5), 10);
```

### Adding a New Operator

1. **Parser** (parser.c):
```c
if (expr[*pos] == '@') {  // New operator
    (*pos)++;
    double right = parse_exponent(expr, pos);
    result = func_custom_op(result, right);
}
```

2. **Function** (functions.c):
```c
double func_custom_op(double a, double b) {
    return a @ b;  // Implementation
}
```

## Testing Strategy

### Unit Tests
- Test individual functions
- Test parser with various expressions
- Test edge cases and error conditions

### Integration Tests
- Test calculator with parser
- Test with history
- Test UI input/output

### Test Coverage
- Target: >80% code coverage
- Run: `ctest --output-on-failure`

## Build System

### CMake Configuration
- Modular project structure
- Cross-platform support
- Automatic dependency detection
- Installation targets

### Compiler Support
- GCC 7.0+
- Clang 5.0+
- MSVC 2019+

## Future Architecture Improvements

1. **Plugin System**
   - Dynamic function loading
   - User-defined functions

2. **Scripting Engine**
   - Multi-line scripts
   - Variable storage

3. **Graphical Interface**
   - Qt/GTK+ frontend
   - Separate from core engine

4. **WebAssembly Version**
   - Compile to JavaScript
   - Browser-based calculator

5. **Library Mode**
   - Expose as C library
   - Use in other projects
