# Makefile for your project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++23 -I.

# Valgrind flags
VLAGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

# Source directory
SRCDIR = interpreter

# Output directory
OUTPUTDIR = build

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OUTPUTDIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE = my_interpreter

# Default target
all: $(EXECUTABLE)

# Rule to link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Rule to link object files into the executable for valgrind
$(EXECUTABLE_VALGRIND): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -ggdb3 $(OBJECTS) -o $@

# Rule to compile each source file into object files
$(OUTPUTDIR)/%.o: $(SRCDIR)/%.cpp | $(OUTPUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create output directory if it doesn't exist
$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

# Run target
run: $(EXECUTABLE)
	@./$(EXECUTABLE) input

# Run target under valgrind
valgrind: $(EXECUTABLE_VALGRIND)
	@valgrind $(VLAGRINDFLAGS) ./$(EXECUTABLE) input


# Clean target
clean:
	rm -rf $(OUTPUTDIR) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
