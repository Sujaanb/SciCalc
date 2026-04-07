cmake_minimum_required(VERSION 3.10)
project(SciCalc VERSION 2.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing
enable_testing()

# Main source files
set(SCICALC_SOURCES
    src/main.c
    src/calculator.c
    src/parser.c
    src/functions.c
    src/ui.c
    src/history.c
)

set(SCICALC_HEADERS
    src/calculator.h
    src/parser.h
    src/functions.h
    src/ui.h
    src/history.h
)

# Create executable
add_executable(scicalc ${SCICALC_SOURCES} ${SCICALC_HEADERS})
target_include_directories(scicalc PRIVATE src)
target_link_libraries(scicalc m)  # Link math library

# Test executable
add_executable(scicalc_test
    tests/test_main.c
    tests/test_parser.c
    tests/test_functions.c
    src/parser.c
    src/functions.c
    src/history.c
)
target_include_directories(scicalc_test PRIVATE src tests)
target_link_libraries(scicalc_test m)
add_test(NAME SciCalcTests COMMAND scicalc_test)

# Compiler flags
if(MSVC)
    target_compile_options(scicalc PRIVATE /W4)
    target_compile_options(scicalc_test PRIVATE /W4)
else()
    target_compile_options(scicalc PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(scicalc_test PRIVATE -Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(scicalc PRIVATE -g --coverage)
        target_link_options(scicalc PRIVATE --coverage)
    endif()
endif()

# Installation
install(TARGETS scicalc DESTINATION bin)
