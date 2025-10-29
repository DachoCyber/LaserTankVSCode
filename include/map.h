#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>
#include <list>

#include "tile.h"
#include "walkableGround.h"
#include "tileInWater.h"
#include "waterTile.h"

class Map : public sf::Drawable {
public:
    Map(int level);
    virtual ~Map() = default;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override ;
    bool isWalkable(int x, int y) const;
    sf::Vector2f getTilePosition(int x, int y) const;
    int getTileSize() const { return tileSize; }
    const std::vector<std::vector<std::unique_ptr<Tile>>>& getTileMap() const {return tiles;}
    const std::vector<std::vector<int>> getTileMapInt() const {return tileMap;}
    void destroyTile(int gridPosX, int gridPosY) {
        std::unique_ptr<Tile> tile = std::make_unique<WalkableGround>(gridPosX*tileSize, gridPosY*tileSize, walkableTexture);
        tiles[gridPosY][gridPosX] = std::move(tile);
    }

    void switchFramesWaterTiles(int i);


    void setTilesEl(size_t i, size_t j, std::unique_ptr<Tile> newElement);

    Tile* getTileFromUniquePtr(std::unique_ptr<Tile> tile) const;
    std::vector<std::vector<int>> getMapState() const;
    void updateWaterTiles();
    void destroyTank(int bulletGridPosX, int bulletGridPosY, int tankType);
    
    int getFlagCoordX() const {return flagCoordX;}
    int getFlagCoordY() const {return flagCoordY;}
    int getPlayerPositionX() const {return playerPosX;}
    int getPlayerPositionY() const {return playerPosY;}



    void undoMove(std::vector<std::vector<int>> *lastMapState);

    void updateTransportTracks();
    void moveTile(int newGridPosY, int newGridPosX, int oldGridPosY, int oldGridPosX);
    std::vector<std::tuple<int, int, Direction>> getTrackCoord() const {return trackTileCoords;}

    std::vector<std::pair<int, int>> getTilesInWaterCoords() const { return tilesInWaterCoords; }
    void setTileCoords(int i, int j, int code);

    void clearWaterTiles();

private:
    void loadTextures();
    void buildMap();

    const int tileSize = 32;
    const int mapWidth = 16;
    const int mapHeight = 16;

    int playerPosX;
    int playerPosY;
    
    std::list<std::pair<int, int>> waterTilesCoords;
    
    std::vector<std::vector<int>> tileMap;
    std::vector<std::vector<sf::Sprite>> sprites;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::pair<int, int>> tileInWater;
    std::vector<std::pair<int, int>> erasedWaterTiles;
    
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
    sf::Texture mirror1Texture;
    sf::Texture mirror2Texture;
    sf::Texture mirror3Texture;
    sf::Texture mirror4Texture;
    
    sf::Texture waterTileTexture;
	sf::Texture waterSecondFrameTexture;

    sf::Texture flagTexture;
    sf::Texture movableBlockTexture;
    sf::Texture undestructableBlockTex;

    sf::Texture EnemyTank1UpTexture;
    sf::Texture EnemyTank1DownTexture;
    sf::Texture EnemyTank1LeftTexture;
    sf::Texture EnemyTank1RightTexture;

    sf::Texture destroyedTankUpTexture;
    sf::Texture destroyedTankDownTexture;
    sf::Texture destroyedTankLeftTexture;
    sf::Texture destroyedTankRightTexture;

    sf::Texture transportTrackLeftTex;
    sf::Texture transportTrackUpTex;
    sf::Texture transportTrackRightTex;
    sf::Texture transportTrackDownTex;

    sf::Texture tileInWaterTex;



    std::vector<std::tuple<int, int, Direction>> trackTileCoords;

    std::vector<std::pair<int, int>> tilesInWaterCoords;

    int level;

    int flagCoordX, flagCoordY;
};