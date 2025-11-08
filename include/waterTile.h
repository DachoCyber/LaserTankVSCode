#pragma once

#include "tile.h"
#include <iostream>


class WaterTile : public Tile {

    private:
        const sf::Texture* texturePtr;
		const sf::Texture* secondFrameTexturePtr;
        
    public:
        WaterTile(int x, int y, const sf::Texture& WaterTileTexture, const sf::Texture& SFWaterTileTexture) : Tile(x, y) {
            walkable = false;
            texturePtr = &WaterTileTexture;
			secondFrameTexturePtr = &SFWaterTileTexture;
            sprite.setTexture(*texturePtr);
            sprite.setPosition(x, y);
            sf::Color waterColor = sprite.getColor();
            waterColor.a = 180;
            sprite.setColor(sf::Color(waterColor));
        }
        void switchFrame(int frameIndex) {
            
            
            if (frameIndex % 2 == 0) {

                sprite.setTexture(*secondFrameTexturePtr);
            } else {
				sprite.setTexture(*texturePtr);
			}
          
            
        }

    bool isUndestructibleBlock() override {
        return false;
    }
    int code() override {
        return 8;
    }
    std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<WaterTile>(posX, posY, *texturePtr, *secondFrameTexturePtr); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
    bool fireBullet() override {
        return false;
    }
    bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
        return false;
    }
    void setAlpha(int alpha) override {
        sf::Color waterColor = sprite.getColor();
        waterColor.a = alpha;
        sprite.setColor(sf::Color(waterColor));
    }
    bool killPlayerTile(int playerPosX, int playerPosY) override {
        if(posX == playerPosX && posY == playerPosY) {
            return true;
        }
        return false;
    }
    bool isWater() override {
        return true;
    }

    bool isWalkable() override {
        return true;
    }
    bool isBulletDestroyable() override {
        return false;
    }
    bool isBulletMovable() override {
        return false;
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
        return false;
    }
    bool isOverlappled() override {
        return true;
    }
    int getMirrorType() override {
        return -1;
    }
    bool isUnderWater(const std::vector<std::pair<int, int>>& waterTileCoords) override {
        return false;
    }
};