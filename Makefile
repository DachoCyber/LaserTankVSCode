# ==========================================
# Makefile for LaserTank (Visual Studio Code)
# ==========================================

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -DSFML_STATIC -DCURL_STATICLIB -DWIN32
INCLUDES := -I"SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)\SFML-2.6.2\include" -I"C:\CURL" -Itinyxml2 -Iinclude

# Libraries
LIBS := -LSFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)\SFML-2.6.2\lib \
        -L"CURL\lib" \
        -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-network-s \
        -lopengl32 -lfreetype -lwinmm -lgdi32 -llibcurl

# Source files
SRC := bulletInteraction.cpp ConsoleApplication5.cpp extractMatrix.cpp \
       game.cpp map.cpp player.cpp playerInteraction.cpp pullFromLevelsFromServer.cpp \
       sfmlWeb.cpp tinyxml2/tinyxml2.cpp

# Object files
OBJ := $(SRC:.cpp=.o)

# Output executable
TARGET := LaserTank.exe

# Build type (default Debug)
CONFIG ?= Debug

ifeq ($(CONFIG),Debug)
    CXXFLAGS += -g -O0
else ifeq ($(CONFIG),Release)
    CXXFLAGS += -O2 -DNDEBUG
endif

# =========================
# Build rules
# =========================

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo Linking...
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo Cleaning...
	del /Q $(OBJ) $(TARGET) 2>nul || true

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
