#pragma once

#include "tile.h"
#include <iostream>


class Mirror4Tile : public Tile {

    private:
        const sf::Texture* texturePtr;
    public:
        Mirror4Tile(int x, int y, const sf::Texture& mirrorTex) : Tile(x, y) {
            walkable = false;
            texturePtr = &mirrorTex;
            sprite.setTexture(*texturePtr);
            sprite.setPosition(x, y);
        }

    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<Mirror4Tile>(posX, posY, *texturePtr); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    int code() override {
        return 7;
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
        return false;
    }
    bool isMirror2() override {
        return false;
    }
    bool isMirror3() override {
        return false;
    }
    bool isMirror4() override {
        return true;
    }
    bool isOverlappled() override {
        return false;
    }
    int getMirrorType() override {
        return 4;
    }
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    bool isWater() override {
        return false;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override{
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
};