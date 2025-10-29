#pragma once

#include <SFML/Graphics.hpp>
#include "resources.h"

class Start : public sf::Drawable {
private:
    sf::RectangleShape startButton;
    sf::Text startText;
    bool clicked = false;

public:
    Start(int menuWinSizeX, int menuWinSizeY) {
        startButton.setPosition(sf::Vector2f(static_cast<float>(menuWinSizeX) * 1 / 3, static_cast<float>(menuWinSizeY) * 1 / 6));
        startButton.setSize(sf::Vector2f(static_cast<float>(menuWinSizeX) * 6 / 15, static_cast<float>(menuWinSizeY) * 3 / 15));
        startButton.setFillColor(sf::Color::White);

        startText.setFont(globalFont);
        startText.setCharacterSize(24);
        startText.setString("Start");
        startText.setFillColor(sf::Color::Black);

        float textWidth = startText.getLocalBounds().width;
        float textHeight = startText.getLocalBounds().height;
        startText.setPosition(
            startButton.getPosition().x + (startButton.getSize().x - textWidth) / 2.f,
            startButton.getPosition().y + (startButton.getSize().y - textHeight) / 2.f - 5.f
        );
        sf::Color rectColor = startButton.getFillColor();
        rectColor.a = 0;
        startButton.setFillColor(rectColor);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(startButton);
        target.draw(startText);
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (startButton.getGlobalBounds().contains(mousePos)) {
            clicked = true;
        }
    }

    bool wasClicked() const {
        return clicked;
    }
};
