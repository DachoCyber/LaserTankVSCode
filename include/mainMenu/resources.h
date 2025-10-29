#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>


inline sf::Font globalFont;

inline void loadGlobalFont() {
    if (!globalFont.loadFromFile("Fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font: arial.ttf");
    }
}
