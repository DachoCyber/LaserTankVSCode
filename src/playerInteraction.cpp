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

    
    bool staySame = false;
    Direction dir = player.getDir();

    // UP
    if(pressedKey == sf::Keyboard::Key::Up) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != UP) {
                player.setDir(UP);
                staySame = true;
                dir = UP;
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
        sf::Vector2i position = player.getGridPosition();
        player.getPlayerStates().push_back({dir, position});
    }

    // DOWN
    if(pressedKey == sf::Keyboard::Key::Down) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != DOWN) {
                player.setDir(DOWN);
                staySame = true;
                dir = DOWN;
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
        sf::Vector2i position = player.getGridPosition();
        player.getPlayerStates().push_back({dir, position});
    }

    

    // LEFT
    if(pressedKey == sf::Keyboard::Key::Left && player.getBullet() == nullptr) {
        if(player.getDir() != LEFT) {
            player.setDir(LEFT);
            staySame = true;
            dir = LEFT;
        } else {
            if(validMove(newGridPos.x - 1, newGridPos.y)) {
                
                bool notLeftTrack = tileMap.getTileMap()[newGridPos.y][newGridPos.x - 1] -> isTransportTrack() != 2;
                if(notLeftTrack) {
                    
                    if(tileMap.getTileMap()[newGridPos.y][newGridPos.x - 1] -> isWalkable()) {

                        newGridPos.x -= 1;
                        moved = true;
                    }
                }
            }
        }
        sf::Vector2i position = player.getGridPosition();
        player.getPlayerStates().push_back({dir, position});
    }
    

    // RIGHT
    if(pressedKey == sf::Keyboard::Key::Right) {
        if(player.getBullet() == nullptr) {
            if(player.getDir() != RIGHT) {
                player.setDir(RIGHT);
                staySame = true;
                dir = RIGHT;
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
        sf::Vector2i position = player.getGridPosition();
        player.getPlayerStates().push_back({dir, position});
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
