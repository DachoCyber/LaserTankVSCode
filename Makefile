# ==========================================
# Makefile for LaserTank (VS Code / MinGW)
# Static build, no precompiled headers
# ==========================================

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2 -DNDEBUG -DSFML_STATIC -DCURL_STATICLIB -DWIN32 -static -pipe

# Include directories
INCLUDES := -I"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/include" \
            -I"CURL" \
            -Iinclude \
            -Itinyxml2

# Library directories and static libs
LIBS := -L"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/lib" \
        -L"CURL/lib" \
        -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s \
        -lopengl32 -lfreetype -lwinmm -lgdi32 -lws2_32 -lbcrypt -lcurl -static-libgcc -static-libstdc++

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Source and object files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) tinyxml2/tinyxml2.o

# Target executable
TARGET := LaserTank.exe

# =========================
# Build rules
# =========================

all: dirs $(TARGET)

# Create necessary folders
dirs:
	@if not exist "$(OBJ_DIR)" (mkdir "$(OBJ_DIR)")
	@if not exist "$(BIN_DIR)" (mkdir "$(BIN_DIR)")

# Link step
$(TARGET): $(OBJ)
	@echo [LINK] Linking $(TARGET)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo [C++] Compiling $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build
clean:
	@echo Cleaning...
	-del /Q $(OBJ_DIR)\*.o 2>nul || exit 0
	-del /Q $(TARGET) 2>nul || exit 0

# Run target
run: all
	@echo Running...
	$(TARGET)

.PHONY: all clean run dirs
