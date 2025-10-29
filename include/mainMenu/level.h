#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>


#include "resources.h"

class Level : public sf::Drawable {
private:
    sf::RectangleShape levelRectShape;
    sf::RectangleShape paddingMenu;
    bool menuWindowOpen = false;
    int levelCount;
    int menuSizeX;
    int menuSizeY;

    sf::Text levelText;
    sf::Text difficulty;

private:
    int openMenuWindow() {
        menuWindowOpen = true;

        sf::RenderWindow menuWindow(sf::VideoMode(menuSizeX, 250), "Choose Level");
        std::cout << levelCount << std::endl;

        std::vector<sf::RectangleShape> levelButtons(levelCount);
        std::vector<sf::Text> levelTexts(levelCount);
        std::vector<sf::Text> difficulty(levelCount);
        for(int i = 0; i < levelCount; i++) {
            difficulty[i].setFont(globalFont);
            if(i < 2) {
                difficulty[i].setFillColor(sf::Color::Magenta);
                difficulty[i].setString("Easy");
            } else if(i < 4) {
                difficulty[i].setFillColor(sf::Color::Yellow);
                difficulty[i].setString("Medium");
            } else {
                difficulty[i].setFillColor(sf::Color::Red);
                difficulty[i].setString("Red");
            }
            difficulty[i].setCharacterSize(12.f);
        }

        for (int i = 0; i < levelCount; ++i) {
            levelButtons[i].setSize(sf::Vector2f(static_cast<float>(menuSizeX), 50.f));
            levelButtons[i].setFillColor(sf::Color::Black);
            levelButtons[i].setPosition(0.f, static_cast<float>(i * 50));

            levelTexts[i].setFont(globalFont);
            levelTexts[i].setCharacterSize(24);
            levelTexts[i].setString("Level " + std::to_string(i + 1));
            levelTexts[i].setFillColor(difficulty[i].getFillColor());
            levelTexts[i].setPosition(levelButtons[i].getPosition().x + 20.f, levelButtons[i].getPosition().y + 10.f);
            difficulty[i].setPosition(levelButtons[i].getPosition().x + 120.f, levelButtons[i].getPosition().y + 22.f);
        }
        
        int firstLevelFromTop = 0;

        while (menuWindow.isOpen()) {
            sf::Event event;
            while (menuWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    menuWindow.close();
                    menuWindowOpen = false;
                }

                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = menuWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (int i = 0; i < levelButtons.size(); ++i) {
                        if (levelButtons[i].getGlobalBounds().contains(mousePos)) {
                            menuWindow.close();
                            menuWindowOpen = false;
                            level = i + 1;
                            std::cout << level << std::endl;
                            return i;
                        }
                    }
                }
                if(event.type == sf::Event::KeyPressed) {

                    if(event.key.code == sf::Keyboard::Key::Down) {
                        if(firstLevelFromTop < levelCount - 5) {

                            firstLevelFromTop++;
                        }
                    }
                    if(event.key.code == sf::Keyboard::Key::Up) {
                        if(firstLevelFromTop > 0) {

                            firstLevelFromTop--;
                        }
                    }
                }
            }

            menuWindow.clear(sf::Color::White);
            for (int i = firstLevelFromTop, j = 0; i < firstLevelFromTop + 5; ++i, ++j) {

                levelButtons[i].setSize(sf::Vector2f(static_cast<float>(menuSizeX), 50.f));
                levelButtons[i].setFillColor(sf::Color::Black);
                levelButtons[i].setPosition(0.f, static_cast<float>(j * 50));

                levelTexts[i].setFont(globalFont);
                levelTexts[i].setCharacterSize(24);
                levelTexts[i].setString("Level " + std::to_string(i + 1));
                levelTexts[i].setFillColor(difficulty[i].getFillColor());
                levelTexts[i].setPosition(levelButtons[i].getPosition().x + 20.f, levelButtons[i].getPosition().y + 10.f);
                difficulty[i].setPosition(levelButtons[i].getPosition().x + 120.f, levelButtons[i].getPosition().y + 22.f);

                menuWindow.draw(levelButtons[i]);
                menuWindow.draw(levelTexts[i]);
                menuWindow.draw(difficulty[i]);
            }
            menuWindow.display();
        }

        return -1;
    }

public:
    int level;

    Level(int menuWinSizeX, int menuWinSizeY, int levelCount)
        : menuSizeX(menuWinSizeX),
          menuSizeY(menuWinSizeY),
          levelCount(levelCount),
          level(-1)
    {   
        
        levelRectShape.setSize(sf::Vector2f(static_cast<float>(menuSizeX)*6/15, static_cast<float>(menuSizeY)/5));
        levelRectShape.setFillColor(sf::Color::White);
        levelRectShape.setPosition(sf::Vector2f((static_cast<float>(menuSizeX)) / 3, (static_cast<float>(menuSizeY*12)/30)));
        sf::Color rectColor = levelRectShape.getFillColor();
        rectColor.a = 0;
        levelRectShape.setFillColor(rectColor);

        
        
        levelText.setFont(globalFont);
        levelText.setCharacterSize(24.f);
        levelText.setString("Level");


        float textWidth = levelText.getLocalBounds().width;
        float textHeight = levelText.getLocalBounds().height;
        levelText.setFillColor(sf::Color::Black);
        levelText.setPosition(
            levelRectShape.getPosition().x + (levelRectShape.getSize().x - textWidth) / 2.f,
            levelRectShape.getPosition().y + (levelRectShape.getSize().y - textHeight) / 2.f - 5.f
        );
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(levelRectShape);
        target.draw(levelText);
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (levelRectShape.getGlobalBounds().contains(mousePos) && !menuWindowOpen) {
            openMenuWindow();
            menuWindowOpen = true;
        }
    }

    void setTextColor(sf::Color color) {
        levelText.setFillColor(color);
    }
};
