#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "bullet.h"
#include "direction.h" 
#include "map.h"

class Tank : public sf::Drawable {
public:
    Tank(int startX, int startY, int windowSizeX, int windowSizeY);
    virtual ~Tank() = default; 

    void setDir(Direction dir);
    Direction getDir() const;

    void setShouldKillPlayer() {
        shouldKillPlayer = true;
    }
    bool getShouldKillPlayer();

    void update(sf::Time, sf::Time);
    sf::Vector2i getGridPosition() const;
    void setGridPosition(sf::Vector2i);

    bool validMove(int x, int y) const;
    
    void loadTextureFromImage();
    void updateSpritePosition();
    void deleteBullet();

    bool deleteAdjBlockIfExists(Map& tileMap); /// Do not fire bullet
    void fireBullet();
    Bullet* getBullet() const {return  bullet;}
    bool bulletInScreen() const;
    bool getShouldFireBullet() const {return shouldFireBullet;}


    void movePlayer(int x, int y) {
        sprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
    } 

    int getPositionX() const {return sprite.getPosition().x;}
    int getPositionY() const {return sprite.getPosition().y;}

private:

    bool shouldKillPlayer = false;

    bool shouldFireBullet;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    Bullet* bullet = nullptr;

    sf::Image tankImg;
    sf::Texture texture;
    sf::Sprite sprite;

    Direction dir;
    sf::Vector2i gridPos;
    bool moveQueued = false;
    const int tileSize = 32;

    int windowSizeX, windowSizeY;
};
