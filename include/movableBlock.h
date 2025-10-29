#pragma once

#include "tile.h"


class MovableBlock : public Tile {
public:
    const sf::Texture& texture;
    MovableBlock(int x, int y, const sf::Texture& texture) : Tile(x, y), texture(texture) {
        try {
            walkable = false;
            isMovable = true;
            overlappled = false;
            sprite.setTexture(texture);
            sprite.setPosition(x, y);
            posX = x;
            posY = y;
        }
        catch(const std::string& what) {
            std::cerr << what << std::endl;
        }
    }
    int code() override {
        return 9;
    }
    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<MovableBlock>(*this); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
    bool overlappled;
    bool isMovable;
    virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
        return false;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
        if (waterTileCoords.empty()) return false; // Early exit if no water tile
        for (const auto& coord : waterTileCoords) {
            if (coord.first == posY/tileSize && coord.second == posX/tileSize) {
                walkable = true;
                isMovable = false;
                overlappled = true;
                return true;
            }
        }
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color color = sprite.getColor();
        color.a = alpha;
        sprite.setColor(color);
    }
    bool isWalkable() override {

        return walkable;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    void interactWithBullet(Direction dir) override {
        return;
    }
    bool isBulletMovable() override {
        return true;
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
        return overlappled;
    }
    bool isWater() override {
        return false;
    }
    bool isTileMovableBlock() {
        return isMovable;
    }
    bool isUndestructibleBlock() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    bool fireBullet() override {
        return false;
    }
    bool isMovableTypeOfBlock() {
        return true;
    }
};