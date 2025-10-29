#pragma once

#include "tile.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class DestructibleBlock : public Tile {
private:
    sf::Texture destructibleBlockTex;
    sf::Sprite destructibleBlockSprite;
    const sf::Texture& texture;
public:
    DestructibleBlock(int x, int y,const sf::Texture& texture) :Tile(x, y), texture(texture) {
        try {
            walkable = false;
            sprite.setTexture(texture);
            sprite.setPosition(x, y);
            sprite.setScale(32.f/53.f, 32.f/55.f);
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    int code() override {
        return 3;
    }
    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<DestructibleBlock>(posX, posY, texture); // Copy constructor
    return clone;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool isWalkable() override {
        return false;
    }
    bool isBulletDestroyable() override {
        return true;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isBulletMovable() override {
        return false;
    }
    virtual int getMirrorType() {
        return 0;
    }
    bool isMirror1() override {
        return false;
    }
    bool isMirror2() override {
        return false;
    }
    bool isMirror3() override {
        return false;
    }
    bool isMirror4() override {
        return false;
    }
    bool isOverlappled() override {
        return false;
    }
    bool killPlayerTile(int playerPosX, int playerPosY) override {
        return posX == playerPosX && posY == playerPosY;
    }
    bool isWater() override {
        return false;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
};

