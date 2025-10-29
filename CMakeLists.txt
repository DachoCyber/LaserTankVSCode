cmake_minimum_required(VERSION 3.15)
project(LaserTank LANGUAGES CXX)

# =========================
# Compiler settings
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Build type
# =========================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -DSFML_STATIC -DCURL_STATICLIB -DWIN32 -g -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Wall -DSFML_STATIC -DCURL_STATICLIB -DWIN32 -O2 -DNDEBUG)
endif()

# =========================
# Include directories
# =========================
include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/tinyxml2"
    "SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/include"
    "C:/CURL"
)

# =========================
# Source files
# =========================
set(SOURCES
    bulletInteraction.cpp
    main.cpp
    extractMatrix.cpp
    game.cpp
    map.cpp
    player.cpp
    playerInteraction.cpp
    pullFromLevelsFromServer.cpp
    sfmlWeb.cpp
    tinyxml2/tinyxml2.cpp
)

# =========================
# Libraries
# =========================
link_directories(
    "SFML-2.6.2-windows-gcc-13.1.0-mingw-32-bit(1)/SFML-2.6.2/lib"
    "CURL/lib"
)

set(LIBS
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    sfml-network-s
    opengl32
    freetype
    winmm
    gdi32
    libcurl
)

# =========================
# Executable
# =========================
add_executable(${PROJECT_NAME} ${SOURCES})

# =========================
# Link libraries
# =========================
target_link_libraries(${PROJECT_NAME} ${LIBS})

# =========================
# Custom commands
# =========================
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
