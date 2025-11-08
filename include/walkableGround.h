#pragma once

#include "tile.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class WalkableGround : public Tile {
public:
    const sf::Texture& texture;
    WalkableGround(int x, int y, const sf::Texture& texture) : Tile(x, y), texture(texture) {
        try {
            walkable = true;
            sprite.setTexture(texture);
            sprite.setPosition(x, y);
            //sprite.setScale(32.f/55.f, 32.f/55.f);
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    int code() override {
        return 1;
    }
    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<WalkableGround>(posX, posY, texture); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
    virtual bool isWalkableGround() {return true;}
    bool fireBullet() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    virtual bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) {
        return false;
    }
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool isWalkable() override {
        return true;
    }
    bool isBulletDestroyable() override {
        return false;
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
    }bool isMirror4() override {
        return false;
    }
    bool isOverlappled() override {
        return true;
    }
    bool isWater() override {
        return false;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
};

