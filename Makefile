# SciCalc - Production Ready Scientific Calculator Makefile
# Author: Sujaan Bhattacharyya
# Version: 1.0.0

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c99 -D_POSIX_C_SOURCE=200809L
DEBUG_FLAGS = -g -O0 -DDEBUG
LDFLAGS = -lm
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = tests
BIN_DIR = bin

# Source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/calculator.c $(SRC_DIR)/parser.c $(SRC_DIR)/utils.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TEST_SOURCES = $(TEST_DIR)/test_calculator.c $(SRC_DIR)/calculator.c $(SRC_DIR)/parser.c $(SRC_DIR)/utils.c
TEST_OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
TEST_BIN = $(BIN_DIR)/test_scicalc

# Executable
TARGET = $(BIN_DIR)/scicalc

# Default target
all: clean $(TARGET)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Build successful! Executable: $@"

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Test target
test: clean $(TEST_SOURCES)
	@echo "Building tests..."
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(TEST_BIN) $(TEST_SOURCES) $(LDFLAGS) -lm
	@echo "Running tests..."
	@$(TEST_BIN)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "✓ Debug build complete"

# Memory check with valgrind
memcheck: debug
	@echo "Running memory check..."
	valgrind $(VALGRIND_FLAGS) $(TARGET)

# Static analysis
analyze:
	@echo "Running static analysis..."
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_DIR) $(INCLUDE_DIR)

# Code formatting
format:
	@echo "Formatting code..."
	clang-format -i $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h
	@echo "✓ Code formatted"

# Install (copy to system)
install: $(TARGET)
	@echo "Installing SciCalc..."
	install -D -m 755 $(TARGET) /usr/local/bin/scicalc
	@echo "✓ Installed to /usr/local/bin/scicalc"

# Uninstall
uninstall:
	@echo "Uninstalling SciCalc..."
	rm -f /usr/local/bin/scicalc
	@echo "✓ Uninstalled"

# Run the calculator
run: $(TARGET)
	./$(TARGET)

# Generate documentation
docs:
	@echo "Generating Doxygen documentation..."
	doxygen Doxyfile 2>/dev/null || echo "Doxygen not installed. Skipping documentation generation."

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "✓ Clean complete"

# Distclean - remove everything including documentation
distclean: clean
	@echo "Removing documentation..."
	rm -rf docs/
	@echo "✓ Distclean complete"

# Help
help:
	@echo "SciCalc Makefile targets:"
	@echo "  make all      - Build the calculator (default)"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make test     - Build and run unit tests"
	@echo "  make run      - Build and run the calculator"
	@echo "  make memcheck - Run memory leak check with valgrind"
	@echo "  make analyze  - Run static code analysis"
	@echo "  make format   - Format code with clang-format"
	@echo "  make install  - Install to /usr/local/bin"
	@echo "  make uninstall- Uninstall from system"
	@echo "  make docs     - Generate Doxygen documentation"
	@echo "  make distclean- Remove all generated files"
	@echo "  make help     - Show this help message"

.PHONY: all clean debug test run memcheck analyze format install uninstall docs distclean help