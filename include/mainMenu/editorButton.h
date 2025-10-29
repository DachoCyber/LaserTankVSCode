#pragma once

#include <SFML/Graphics.hpp>
#include "resources.h"

class EditorButton : public sf::Drawable {
private:
    sf::Text editorText;
    bool clicked = false;

    bool editorWinClose;

public:
    sf::RectangleShape editorButton;
    EditorButton(int menuWinSizeX, int menuWinSizeY, bool editorWinClose) {
        editorButton.setPosition(sf::Vector2f(static_cast<float>(menuWinSizeX) * 1 / 3, static_cast<float>(menuWinSizeY) * 20.5 / 32));
        editorButton.setSize(sf::Vector2f(static_cast<float>(menuWinSizeX) * 6 / 15, static_cast<float>(menuWinSizeY) * 3 / 15));
        editorButton.setFillColor(sf::Color::White);

        this->editorWinClose = editorWinClose;

        editorText.setFont(globalFont);
        editorText.setCharacterSize(24);

        editorText.setString("Editor");
        editorText.setFillColor(sf::Color::Black);

        float textWidth = editorText.getLocalBounds().width;
        float textHeight = editorText.getLocalBounds().height;
        editorText.setPosition(
            editorButton.getPosition().x + (editorButton.getSize().x - textWidth) / 2.f,
            editorButton.getPosition().y + (editorButton.getSize().y - textHeight) / 2.f - 5.f
        );
        sf::Color rectColor = editorButton.getFillColor();
        rectColor.a = 0;
        editorButton.setFillColor(rectColor);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(editorButton);
        target.draw(editorText);
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (editorButton.getGlobalBounds().contains(mousePos)) {
            clicked = true;
        }
    }

    bool wasClicked() const {
        return clicked;
    }
};
