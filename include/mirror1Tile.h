#pragma once

#include "tile.h"
#include <iostream>


class Mirror1Tile : public Tile {

    private:
        const sf::Texture* texturePtr;
    public:
        Mirror1Tile(int x, int y, const sf::Texture& mirrorTex) : Tile(x, y) {
            walkable = false;
            texturePtr = &mirrorTex;
            sprite.setTexture(*texturePtr);
            sprite.setPosition(x, y);
        }
    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<Mirror1Tile>(posX, posY, *texturePtr); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
    int code() override {
        return 4;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
        return false;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool isWalkable() override {
        return false;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    bool isBulletMovable() override {
        return true;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isMirror1() override {
        return true;
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
    int getMirrorType() override {
        return 1;
    }
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    bool isWater() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
};