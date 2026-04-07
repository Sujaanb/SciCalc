CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm
TARGET = scicalc
SOURCES = calculator.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "✓ Build successful! Run with: ./$(TARGET)"

# Compile source files
%.o: %.c calculator.h
	$(CC) $(CFLAGS) -c $< -o $@

# Run the calculator
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned build artifacts"

# Rebuild from scratch
rebuild: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  make         - Compile the calculator"
	@echo "  make run     - Compile and run the calculator"
	@echo "  make clean   - Remove build artifacts"
	@echo "  make rebuild - Clean and compile"
	@echo "  make help    - Show this help message"

.PHONY: all run clean rebuild help
