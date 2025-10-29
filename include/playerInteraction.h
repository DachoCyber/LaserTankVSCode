#pragma once

#include "map.h"
#include "player.h"

class PlayerInteraction {
private:
    int windowSizeX, windowSizeY;
    Tank& player;
    Map& tileMap;
    sf::Keyboard :: Key pressedKey;
    const int tileSize = 32;
public:
    PlayerInteraction(int windowSizeX, int windowSizeY, Tank& player, Map& map, sf::Keyboard::Key key);
    ~PlayerInteraction() = default;
    void handlTransportableTrack(int x, int y);
    void handleMovement();
};