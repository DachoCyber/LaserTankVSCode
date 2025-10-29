#pragma once

#include "map.h"
#include "player.h"


class BulletInteraction {
private:
    int windowSizeX, windowSizeY;
    Tank& player;
    Map& tileMap;
    const int tileSize = 32;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);
public:
    BulletInteraction(int windowSizeX, int windowSizeY, Tank& player, Map& map);
    
    ~BulletInteraction() = default;
    void interact();
    bool wasMirrorBefore = false;
};