    #pragma once

    #include "tile.h"
    #include "bullet.h"

    #include <memory>

    class EnemyTank1 : public Tile {
    public:
        const sf::Texture& texture;
        int dir;
        EnemyTank1(int x, int y, int dir, const sf::Texture& texture) : Tile(x, y), texture(texture) {
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
            auto clone = std::make_unique<EnemyTank1>(posX, posY, dir, texture); // Copy constructor
    return clone;
        }
        int code() override {
            return 12 + dir;
        }

        Bullet* enemysTankBullet;



        bool shouldKillPlayer = false;


        bool killPlayer(const std::vector<std::vector<std::unique_ptr<Tile>>>& tileMap, int playerPosX, int playerPosY) override {
            
            switch(dir) {
                case 0:
                    
                    if(playerPosY != posY) return false;
                    
                    if(posX < playerPosX) return false;
                    for(int j = posX/tileSize - 1; j > playerPosX/tileSize; j--) {
                        int gPosY = posY/tileSize;
    

                        if(!(tileMap[gPosY][j]->isWalkable() || tileMap[gPosY][j]->isWater())) {
                                return false;
                            }
                    }
                    
                    break;
                case 1:
                    if(playerPosY != posY) return false;
                    if(posX > playerPosX) {
                        
                        return false;
                    }
                    for(int j = posX/tileSize + 1; j < playerPosX/tileSize; j++) {
                        int gPosY = posY/tileSize;
                

                        if(!(tileMap[gPosY][j]->isWalkable() || tileMap[gPosY][j]->isWater())) {
                               
                                return false;
                            }
                    }
                    
                    break;
                case 2:
                    if(playerPosX != posX) return false;
                    if(posY < playerPosY) return false;
                    for(int j = posY/tileSize - 1; j > playerPosY/tileSize; j--) {
                        int gPosX = posX/tileSize;
                

                        if(!(tileMap[j][gPosX]->isWalkable() || tileMap[j][gPosX]->isWater())) {
                                return false;
                            }
                    }
                    break;
                default:
                    if(playerPosX != posX) return false;
                    if(posY > playerPosY) return false;
                    for(int j = posY/tileSize + 1; j < playerPosY/tileSize; j++) {
                        int gPosX = posX/tileSize;
                

                        if(!(tileMap[j][gPosX]->isWalkable() || tileMap[j][gPosX]->isWater())) {
                                return false;
                            }
                    }
                    break;
            }

            
            return true;
        }

        Bullet* bullet;
        bool fireBullet() override {
            if(dir == 0) {

                bullet = new Bullet(sf::Vector2f(posX, posY + tileSize/2), LEFT, true);
            } else if(dir == 1) {
                bullet = new Bullet(sf::Vector2f(posX, posY + tileSize/2), RIGHT, true);
            } else if(dir == 2) {
                bullet = new Bullet(sf::Vector2f(posX + tileSize/2, posY), UP, true);
            } else {
                bullet = new Bullet(sf::Vector2f(posX + tileSize/2, posY), DOWN, true);
            }
            return true;
        }
        int isTank() {
            return dir + 1;
        }
        bool isMovableBlock() {
            return true;
        }

        Bullet* getBullet() override {
            return bullet;
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
        virtual bool killPlayerTile(int playerPosX, int playerPosY) override {
            return false;
        }
        bool isWater() override {
            return false;
        }
    };