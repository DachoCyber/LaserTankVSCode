#include "../include/playerInteraction.h"

bool validMove(int x, int y) {
    return x >= 0 && x < 16  && 
           y >= 0 && y < 16;
}

PlayerInteraction :: PlayerInteraction(int windowSizeX, int windowSizeY, Tank& player, Map& map, sf::Keyboard::Key key) :
        windowSizeX(windowSizeX),
        windowSizeY(windowSizeY),
        player(player),
        tileMap(map),
        pressedKey(key) 
{
    
}



void PlayerInteraction :: handleMovement() {
    sf::Vector2i newGridPos = player.getGridPosition();
    bool moved = false;

    

    // UP
    if(pressedKey == sf::Keyboard::Key::Up) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != UP) {
                player.setDir(UP);
            } else {
                if(validMove(newGridPos.x, newGridPos.y - 1)) {
                    bool notUpTrack = tileMap.getTileMap()[newGridPos.y - 1][newGridPos.x] -> isTransportTrack() != 4;
                    if(notUpTrack) {

                        if(tileMap.getTileMap()[newGridPos.y - 1][newGridPos.x] -> isWalkable()) {

                            newGridPos.y -= 1;
                            moved = true;
                        }
                    }
                }
            }
        }
    }

    // DOWN
    if(pressedKey == sf::Keyboard::Key::Down) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != DOWN) {
                player.setDir(DOWN);
            } else {
                if(validMove(newGridPos.x, newGridPos.y + 1)) {
                    bool notDownTrack = tileMap.getTileMap()[newGridPos.y + 1][newGridPos.x] -> isTransportTrack() != 3;
                    if(notDownTrack) {
                        
                        if(tileMap.getTileMap()[newGridPos.y + 1][newGridPos.x] -> isWalkable()) {

                            newGridPos.y += 1;
                            moved = true;
                        }
                    }
                }
            }
        }
    }

    

    // LEFT
    if(pressedKey == sf::Keyboard::Key::Left && player.getBullet() == nullptr) {
        if(player.getDir() != LEFT) {
            player.setDir(LEFT);
        } else {
            if(validMove(newGridPos.x - 1, newGridPos.y)) {
                //std::cout << "this is good!" << std::endl;
                bool notLeftTrack = tileMap.getTileMap()[newGridPos.y][newGridPos.x - 1] -> isTransportTrack() != 2;
                if(notLeftTrack) {
                    //std::cout << "this is also good!" << std::endl;
                    if(tileMap.getTileMap()[newGridPos.y][newGridPos.x - 1] -> isWalkable()) {

                        newGridPos.x -= 1;
                        moved = true;
                    }
                }
            }
        }
    }
    

    // RIGHT
    if(pressedKey == sf::Keyboard::Key::Right) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != RIGHT) {
                player.setDir(RIGHT);
            } else {
                if(validMove(newGridPos.y, newGridPos.x + 1)) {
                    bool notRightTrack = tileMap.getTileMap()[newGridPos.y][newGridPos.x + 1] -> isTransportTrack() != 1;
                    if(notRightTrack) {
                        if(tileMap.getTileMap()[newGridPos.y][newGridPos.x + 1] -> isWalkable()) {
                            newGridPos.x += 1;
                            moved = true;
                        }

                    }

                }
                
            }
        }
    }

    // SPACE
    if(pressedKey == sf::Keyboard::Key::Space && player.getBullet() == nullptr) {
        
        if(!player.deleteAdjBlockIfExists(tileMap)) {
            player.fireBullet();
        }
    }

    if(moved && validMove(newGridPos.x, newGridPos.y)) {
        player.setGridPosition(newGridPos);
        if(tileMap.getTileMap()[newGridPos.y][newGridPos.x] -> isWater()) {
            player.setShouldKillPlayer();
        }
    }
}
/*
void PlayerInteraction :: handlTransportableTrack(int y, int x) {
    player.setDir(LEFT);
    if(validMove(x - 1, y)) {

            if(tileMap.getTileMap()[y][x-1] -> isTileMovableBlock() || 
                tileMap.getTileMap()[y][x-1] -> isBulletDestroyable() ||
                tileMap.getTileMap()[y][x-1] -> isMirror1() ||
                tileMap.getTileMap()[y][x-1] -> isMirror2() ||
                tileMap.getTileMap()[y][x-1] -> isMirror3() ||
                tileMap.getTileMap()[y][x-1] -> isMirror4() ||
                tileMap.getTileMap()[y][x-1] -> isTank()) {
                    //std::cout << "here" << std::endl;
                    return;
            }
            int currGridCoordX = x;
            int currGridCoordY = y;

            //std::cout << player.getGridPosition().x << std::endl;
            player.setGridPosition(sf::Vector2i(x - 1, y));
            //std::cout << player.getGridPosition().x << std::endl;
        }
}*/