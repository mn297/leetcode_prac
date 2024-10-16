# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -std=c++17

# Source file
# SRC = src/38_count_and_say.cpp
# SRC = src/bits_manipulation.cpp
SRC = src/minstack.cpp

# Output executable name
OUT = leetcode.out

# Default target to build the program
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Run the program
run: $(OUT)
	./$(OUT)

# Clean the generated files
clean:
	rm -f $(OUT)
