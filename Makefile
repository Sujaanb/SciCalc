CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O2
LDFLAGS = -lm
TARGET = scicalc
SOURCES = main.c calculator.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "Build complete! Run with: ./$(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Cleaned up build artifacts"

run: $(TARGET)
	./$(TARGET)

help:
	@echo "Available targets:"
	@echo "  make       - Build the calculator"
	@echo "  make run   - Build and run the calculator"
	@echo "  make clean - Remove build artifacts"
	@echo "  make help  - Display this help message"
