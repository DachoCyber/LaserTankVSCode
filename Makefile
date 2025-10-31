# ==========================================
# Makefile for LaserTank (MinGW / VS Code)
# Release build using dynamic SFML (GCC 13.1.0 DW2 32-bit)
# ==========================================

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2 -DNDEBUG -mthreads -pipe

# Include directories
INCLUDES := \
    -I"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/include" \
    -I"CURL"

# Library directories
LIBDIRS := \
    -L"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/lib" \
    -L"CURL/lib"

# Libraries (dynamic linking)
LIBS := \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-network \
    -lopengl32 -lfreetype -lwinmm -lgdi32 -luser32 -ladvapi32 -lshell32 -lws2_32 -lcurl

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj

# Source and object files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) tinyxml2/tinyxml2.o

# Target executable
TARGET := LaserTank.exe

# =========================
# Build rules
# =========================

all: dirs $(TARGET)

# Create build directories
dirs:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"

# Linking
$(TARGET): $(OBJ)
	@echo [LINK] Linking $(TARGET)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBDIRS) $(LIBS)

# Compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo [C++] Compiling $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	@echo Cleaning...
	-del /Q $(OBJ_DIR)\*.o 2>nul || exit 0
	-del /Q $(TARGET) 2>nul || exit 0

run: all
	@echo Running...
	$(TARGET)

.PHONY: all clean run dirs
