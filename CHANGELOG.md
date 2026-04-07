# Changelog

All notable changes to this project will be documented in this file.

## [2.0.0] - 2026-03-26

### Added
- Complete rewrite with modular architecture
- Expression parser with proper operator precedence
- Support for complex mathematical expressions with parentheses
- Extended mathematical functions library (~40 functions)
- Trigonometric functions (sin, cos, tan, asin, acos, atan)
- Logarithmic functions (ln, log10, log2, exp)
- Advanced functions (sqrt, cbrt, factorial, combinations, permutations)
- Statistical functions (mean, median, standard deviation)
- Interactive menu system with color-coded UI
- Calculation history with navigation
- Customizable precision (1-15 decimal places)
- CMake build system for cross-platform support
- Comprehensive test suite
- GitHub Actions CI/CD pipeline
- Detailed documentation (README, architecture guide, build instructions)
- Contributing guidelines
- MIT License

### Changed
- Migrated from single-file C program to modular architecture
- Improved error handling with graceful fallbacks
- Better input validation and user feedback
- Refactored user interface with menu system

### Fixed
- Division by zero handling
- Domain errors in mathematical functions
- Input buffer overflow risks

### Security
- Added bounds checking for arrays
- Safe string handling
- Input validation

## [1.0.0] - 2023-05-14

### Initial Release
- Basic arithmetic operations (+, -, *, /)
- Power operation (^)
- Simple CLI interface
- Basic error handling for division by zero

---

## Versioning

This project follows [Semantic Versioning](https://semver.org/)

## Future Releases

### [2.1.0] - Planned
- GUI version using Qt/GTK+
- Complex number support
- Matrix operations
- Unit conversion
- Script mode with variable definitions

### [3.0.0] - Future
- WebAssembly compilation
- Mobile app (React Native)
- Cloud API
- Advanced graphing capabilities
- Integration with scientific libraries
