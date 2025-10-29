    #pragma once

    #include "tile.h"
    #include "bullet.h"

    #include <memory>

    class DestroyedTank: public Tile {
    public:
        const sf::Texture& texture;
        int dir;
        DestroyedTank(int x, int y, int dir, const sf::Texture& texture) : Tile(x, y), texture(texture) {
            try {
                this-> dir = dir;
                walkable = false;
                sprite.setTexture(texture);
                sprite.setPosition(x, y);
            }
            catch(const std::string& what) {
                std::cerr << what << std::endl;
            }
        }
        std::unique_ptr<Tile> clone() const override {
        auto clone = std::make_unique<DestroyedTank>(posX, posY, dir, texture); // Copy constructor
    clone->sprite = this->sprite; // Copy the sprite
    return clone;
    }
        int code() override {
            return 16 + dir;
        }

        Bullet* enemysTankBullet;



        bool shouldKillPlayer = false;


        bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
            
            return false;
        }
        int isTank() {
            return 0;
        }

        Bullet* getBullet() override {
            return nullptr;
        }

        bool fireBullet() override {
            return false;
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
        int getMirrorType() override {
            return -1;
        }
        bool isMovableBlock() override {
            return true;
        }
        virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
            return false;
        }
        bool isWater() override {
            return false;
        }
    };