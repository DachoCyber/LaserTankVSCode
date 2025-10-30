# ==========================================
# Makefile for LaserTank (VS Code / MinGW)
# ==========================================

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -DSFML_STATIC -DCURL_STATICLIB -DWIN32 -pipe
INCLUDES := -I"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/include" \
            -I"CURL" \
            -Iinclude \
            -Itinyxml2

# Libraries
LIBS := -L"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/lib" \
        -L"CURL/lib" \
        -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s \
        -lopengl32 -lfreetype -lwinmm -lgdi32 -lcurl

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Sources and objects
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) tinyxml2/tinyxml2.o

# Target executable
TARGET := $(BIN_DIR)/LaserTank.exe

# Precompiled header
PCH := include/pch.h
PCH_GCH := $(OBJ_DIR)/pch.h.gch

# Build configuration
CONFIG ?= Debug

ifeq ($(CONFIG),Debug)
    CXXFLAGS += -g -O0
else ifeq ($(CONFIG),Release)
    CXXFLAGS += -O2 -DNDEBUG
endif

# =========================
# Build rules
# =========================

all: dirs $(PCH_GCH) $(TARGET)

# Create necessary folders
dirs:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

# Precompiled header rule
$(PCH_GCH): $(PCH)
	@echo [PCH] Building precompiled header...
	$(CXX) $(CXXFLAGS) $(INCLUDES) -x c++-header $(PCH) -o $(PCH_GCH)

# Link
$(TARGET): $(OBJ)
	@echo [LINK] Linking $(TARGET)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(PCH_GCH)
	@echo [C++] Compiling $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) -include $(PCH) -c $< -o $@

# Clean
clean:
	@echo Cleaning...
	-del /Q $(OBJ_DIR)\*.o 2>nul || exit 0
	-del /Q $(PCH_GCH) 2>nul || exit 0
	-del /Q $(TARGET) 2>nul || exit 0

run: all
	@echo Running...
	$(TARGET)

.PHONY: all clean run dirs
