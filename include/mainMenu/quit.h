#pragma once

#include <SFML/Graphics.hpp> 


class Quit : public sf::Drawable {
private:

    sf::RectangleShape quitRectShape;
public:

    Quit(int menuWinSizeX, int menuWinSizeY) {
        quitRectShape.setPosition(sf::Vector2f(static_cast<float>(menuWinSizeX)*11/15, static_cast<float>(menuWinSizeY)*11/15));
        quitRectShape.setSize(sf::Vector2f(static_cast<float>(menuWinSizeX)*6/15, static_cast<float>(menuWinSizeY)*3/15));
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(quitRectShape);
    }
};