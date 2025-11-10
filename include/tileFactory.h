#pragma once

#include "walkableGround.h"
#include "destructibleBlock.h"
#include "waterTile.h"
#include "mirror1Tile.h"
#include "mirror2Tile.h"
#include "mirror3Tile.h"
#include "mirror4Tile.h"
#include "tank1.h"
#include "destroyedTank.h"
#include "flag.h"
#include "transportTrack.h"
#include "movableBlock.h"
#include "tileInWater.h"
#include "undestructableBlock.h"

#include <iostream>

class TileFactory {
public:
    static std::unique_ptr<Tile> constructTile(int code, int x, int y, int tileSize);
};