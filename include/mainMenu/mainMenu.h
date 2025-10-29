#pragma once

#include "level.h"
#include "quit.h"
#include "start.h"
#include "editor.h"
#include <memory>
#include <iostream>
#include <sstream>
#include <curl/curl.h>

class MainMenu : public sf::Drawable {
private:
    Level levels;
    Start start;
    Editor editor;
    static constexpr int menuWindowSizeX = 794;
    static constexpr int menuWindowSizeY = 800;
    std::vector<std::vector<int>> tileMap;
    std::unique_ptr<sf::RenderWindow> window;

    bool editorWinClose = false;

    sf::Image backgroundImage;
    sf::Sprite backgroundImageSprite;
    sf::Texture backgroundImageTexture;

public:
    int level;

    MainMenu(int levelCount)
        : levels(menuWindowSizeX, menuWindowSizeY, levelCount),
        start(menuWindowSizeX, menuWindowSizeY),
        editor(menuWindowSizeX, menuWindowSizeY, editorWinClose),
        level(-1),
        window(std::make_unique<sf::RenderWindow>(
            sf::VideoMode(menuWindowSizeX, menuWindowSizeY), "Laser Tank", sf::Style::Default)) {

        if (!backgroundImage.loadFromFile("Images/mainMenuImage.png")) {
            throw std::runtime_error("Failed to load main menu background image!");
        }
        if (!backgroundImageTexture.loadFromImage(backgroundImage)) {
            throw std::runtime_error("Failed to load texture!");
        }
        backgroundImageSprite.setTexture(backgroundImageTexture);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(backgroundImageSprite);
        target.draw(levels);
        target.draw(start);
    }

    void run() {
        sf::Time updateLevelTextTime = sf::seconds(0.25);
        sf::Clock clock;
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }

                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    
                    sf::Vector2f mousePos = window->mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    levels.handleClick(mousePos);
                    start.handleClick(mousePos);
                    editor.button.handleClick(mousePos);
                }
            }

            if (start.wasClicked() && levels.level == -1) {
                if (clock.getElapsedTime().asSeconds() >= updateLevelTextTime.asSeconds() / 2) {
                    levels.setTextColor(sf::Color::Red);
                }
                if (clock.getElapsedTime().asSeconds() >= updateLevelTextTime.asSeconds()) {
                    levels.setTextColor(sf::Color::Black);
                    clock.restart();
                }
            }

            if (start.wasClicked() && levels.level != -1) {
                level = levels.level;
                window->close();
                break;
            }
            if(editor.button.wasClicked()) {
                editor.handleClick();
			
            }

            render();
        }
    }


    void render() {
        window->clear(sf::Color::Black);
        window->draw(backgroundImageSprite);
        window->draw(levels);
        window->draw(start);
        window->draw(editor);
        window->display();
    }

    int getChosenLevel() const {
        return level;
    }




};
