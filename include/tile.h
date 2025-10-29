#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include <vector>

#include "bullet.h"

#include "direction.h"

class Tile : public sf::Drawable {

protected:
    const int tileSize = 32;
    int posX, posY;

    sf::Texture tex;
    sf::Sprite sprite;

    bool walkable;
public:
 
    Tile(int x, int y) {
        posX = x;
        posY = y;
    }
    virtual int code() = 0;
    virtual std::unique_ptr<Tile> clone() const = 0;
    virtual ~Tile() = default;
    virtual bool isTileMovableBlock() {
        return false;
    }
    virtual int isTransportTrack() {
        return 0;
    }
    virtual bool isTileInWater() {return false;}
    virtual bool isMovableTypeOfBlock() {return false;}
    virtual Bullet* getBullet() { return nullptr; }
    virtual int isTank() {return 0;}
    virtual bool isWalkableGround() {return false;}
    virtual bool isMovableBlock() {return false;}
    virtual bool fireBullet() = 0;
    virtual bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) = 0;
    virtual bool isUndestructibleBlock() = 0;
    virtual void setAlpha(int alpha) = 0;
    virtual bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) = 0;
    virtual bool isWalkable() = 0;
    virtual bool isBulletDestroyable() = 0;
    virtual void interactWithBullet(Direction dir) = 0;
    virtual bool isBulletMovable() = 0;
    virtual bool isMirror1() = 0;
    virtual bool isMirror2() = 0;
    virtual bool isMirror3() = 0;
    virtual bool isMirror4() = 0;
    virtual bool isOverlappled() = 0;
    virtual int getMirrorType() = 0;
    virtual void setPosition(int x, int y) {
        sprite.setPosition(x, y);
        posX = x;
        posY = y;
    }
    virtual bool isWater() = 0;
    virtual bool killPlayerTile(int playerPosX, int playerPosY) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override {
        target.draw(sprite);
    }
    Tile() : walkable(false), posX(0), posY(0) {}
};