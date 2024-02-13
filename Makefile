# Makefile for your project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++23 -I.
TEST_FLAGS = -I /usr/local/include/gtest/ -c 
LXXFLAGS = -std=c++17 -pthread
GTEST = /usr/lib/libgtest.a

# Valgrind flags
VLAGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Source directory
SRCDIR = interpreter

# Output directory
OUTPUTDIR = build

# Source files
EXCLUDE = $(shell find . -name "*.test.cpp" | sed 's/^\.\///')
SOURCES = $(filter-out $(EXCLUDE), $(wildcard $(SRCDIR)/*.cpp))

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OUTPUTDIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE = my_interpreter
EXECUTABLE_VALGRIND := $(EXECUTABLE)_val

# Default target
all: $(EXECUTABLE)

# Rule to link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Rule to link object files into the executable for valgrind
$(EXECUTABLE_VALGRIND): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -g -ggdb3 $(OBJECTS) -o $@

# Rule to compile each source file into object files
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp | $(OUTPUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test
# Source directory
TESTDIR = tests

# Test source files
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)

# Test object files
TEST_OBJECTS := $(filter-out build/interpreter.o, $(OBJECTS))
TEST_OBJECTS += $(patsubst $(TESTDIR)/%.cpp,$(OUTPUTDIR)/%.o,$(TEST_SOURCES))
TEST_OBJECTS += $(patsubst $(SRCDIR)/%.cpp,$(OUTPUTDIR)/%.o,$(EXCLUDE))

# Tets executable name
TEST_EXECUTABLE = interpreter_tests

# Rule to link object files into the test executable
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TEST_EXECUTABLE) $(TEST_OBJECTS) $(GTEST)

# Rule to compile each source file into object files
$(OUTPUTDIR)/%.o: $(TESTDIR)/%.cpp | $(OUTPUTDIR)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -c $< -o $@

# Create output directory if it doesn't exist
$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

# Run target
run: $(EXECUTABLE)
	@./$(EXECUTABLE) input

# Run target under valgrind
valgrind: $(EXECUTABLE_VALGRIND)
	@valgrind $(VLAGRINDFLAGS) ./$(EXECUTABLE_VALGRIND) input

test: $(TEST_EXECUTABLE)
	@./$(TEST_EXECUTABLE)

# Clean target
clean:
	rm -rf $(OUTPUTDIR) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
