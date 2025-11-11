#include "../include/tileFactory.h"
#include "../include/textures.h"

std::unique_ptr<Tile> TileFactory :: constructTile(int code, int x, int y, int tileSize) {
    std::unique_ptr<Tile> tile;
    switch (code) {
                case 0:
                    tile = std::make_unique<WalkableGround>(x * tileSize, y * tileSize, walkableTexture);
                    break;
                case 1:
                    tile = std::make_unique<WalkableGround>(x * tileSize, y * tileSize, walkableTexture);
                    break;
                case 3:
                    tile = std::make_unique<DestructibleBlock>(x * tileSize, y * tileSize, destructibleTexture);
                    break;
                case 4:
                    tile = std::make_unique<Mirror1Tile>(x * tileSize, y * tileSize, mirror1Texture);
                    break;
                case 5:
                    tile = std::make_unique<Mirror2Tile>(x * tileSize, y * tileSize, mirror2Texture);
                    break;
                case 6:
                    tile = std::make_unique<Mirror3Tile>(x * tileSize, y * tileSize, mirror3Texture);
                    break;
                case 7:
                    tile = std::make_unique<Mirror4Tile>(x * tileSize, y * tileSize, mirror4Texture);
                    break;
                case 8:
                    tile = std::make_unique<WaterTile>(x * tileSize, y * tileSize, waterTileTexture, waterSecondFrameTexture);
                    break;
                case 9:
                    tile = std::make_unique<MovableBlock>(x * tileSize, y * tileSize, movableBlockTexture);
                    break;
                case 10:
                    tile = std::make_unique<Flag>(x * tileSize, y * tileSize, flagTexture);
                    break;
                case 11:
                    tile = std::make_unique<UndestructableBlock>(x * tileSize, y * tileSize, undestructableBlockTex);
                    break;
                case 12:
                    tile = std::make_unique<EnemyTank1>(x * tileSize, y * tileSize, 0, EnemyTank1LeftTexture);
                    break;
                case 13:
                    tile = std::make_unique<EnemyTank1>(x * tileSize, y * tileSize, 1, EnemyTank1RightTexture);
                    break;
                case 14:
                    tile = std::make_unique<EnemyTank1>(x * tileSize, y * tileSize, 2, EnemyTank1UpTexture);
                    break;
                case 15:
                    tile = std::make_unique<EnemyTank1>(x * tileSize, y * tileSize, 3, EnemyTank1DownTexture);
                    break;
                case 16:
                    tile = std::make_unique<DestroyedTank>(x * tileSize, y * tileSize, 0, destroyedTankLeftTexture);
                    break;
                case 17:
                    tile = std::make_unique<DestroyedTank>(x * tileSize, y * tileSize, 1, destroyedTankUpTexture);
                    break;
                case 18:
                    tile = std::make_unique<DestroyedTank>(x * tileSize, y * tileSize, 2, destroyedTankDownTexture);
                    break;
                case 19:
                    tile = std::make_unique<DestroyedTank>(x * tileSize, y * tileSize, 3, destroyedTankRightTexture);
                    break;
                case 20:
                    tile = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, LEFT, transportTrackLeftTex);
                    break;
                case 21:
                    tile = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, RIGHT, transportTrackRightTex);
                    break;
                case 22:
                    tile = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, UP, transportTrackUpTex);
                    break;
                case 23:
                    tile = std::make_unique<TransportTrack>(x * tileSize, y * tileSize, DOWN, transportTrackDownTex);
                    break;
                case 50:
                    tile = std::make_unique<TileInWater>(x * tileSize, y * tileSize, tileInWaterTex);
                    break;
                default:
                    tile = nullptr;
                    break;
                }

    return tile;
}