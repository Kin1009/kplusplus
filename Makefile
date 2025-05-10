# Compiler and flags
CXX := g++
CXXFLAGS := -std=gnu++26 -Wall -Wextra -g
LDFLAGS :=

# Directories
SRC_DIR := .
OBJ_DIR := build
BIN_DIR := bin

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC := $(BIN_DIR)/main

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
