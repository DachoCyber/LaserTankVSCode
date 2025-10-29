#include "include/player.h"


Tank::Tank(int gridPosX, int gridPosY, int windowSizeX, int windowSizeY) 
    :
    dir(RIGHT),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY)
{
    tankImg.loadFromFile("Images/tank.png");
    texture.loadFromImage(tankImg);
    sprite.setTexture(texture);
    //std::cout << gridPosX << " " << gridPosY << std::endl;
    sprite.setScale(sf::Vector2f(0.65, 0.65));  
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    setDir(dir);
    sprite.setPosition(sf::Vector2f(static_cast<float>(gridPosX * tileSize + tileSize/2), static_cast<float>(gridPosY*tileSize + tileSize/2)));
    updateSpritePosition();
    
}

bool Tank :: getShouldKillPlayer() {
    return shouldKillPlayer;
}

bool Tank::bulletInScreen() const {
    if (bullet && bullet->getPosition().x <= windowSizeX &&
        bullet->getPosition().x >= 0 &&
        bullet->getPosition().y <= windowSizeY &&
        bullet->getPosition().y >= 0) {
        return true;
    } else {
        return false;
    }
}


void Tank::setDir(Direction d) {
    dir = d;
    switch (dir) {
        case UP:    sprite.setRotation(0.f); break;
        case RIGHT: sprite.setRotation(90.f); break;
        case DOWN:  sprite.setRotation(180.f); break;
        case LEFT:  sprite.setRotation(270.f); break;
    }
}

Direction Tank::getDir() const {
    return dir;
}

sf::Vector2i Tank::getGridPosition() const {
    return gridPos;
}

void Tank :: setGridPosition(sf::Vector2i gridPos) {
    this -> gridPos = gridPos;
    updateSpritePosition();
}

void Tank::update(sf::Time accTime, sf::Time updateInterval) {

    sprite.setPosition(gridPos.x * tileSize + tileSize / 2, gridPos.y * tileSize + tileSize / 2);

    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
        moveQueued = false;
    }
    if(accTime >= updateInterval && bullet) {

        bullet->update(updateInterval);
        accTime -= updateInterval;
    }
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    if (bullet && bulletInScreen()) {
        target.draw(*bullet);
    }
}

void Tank::updateSpritePosition() {
    sprite.setPosition(sf::Vector2f(static_cast<float>(gridPos.x*tileSize + tileSize/2), static_cast<float>(gridPos.y*tileSize + tileSize/2)));
}

bool Tank :: validMove(int gridPosX, int gridPosy) const {
    return gridPosX >= 0 && gridPosX < 16 && gridPosy >= 0 && gridPosy < 16;
}
void Tank::fireBullet() {

    sf::Vector2f tankPos = sprite.getPosition();
    auto tankSize = tankImg.getSize();
    float bulletStartPosX, bulletStartPosY;
    switch (dir) {
        case UP: bulletStartPosX = tankPos.x; bulletStartPosY = tankPos.y ;  break;
        case DOWN: bulletStartPosX = tankPos.x ; bulletStartPosY = tankPos.y;  break;
        case RIGHT: bulletStartPosX = tankPos.x; bulletStartPosY = tankPos.y ;  break;
        case LEFT: bulletStartPosX = tankPos.x; bulletStartPosY = tankPos.y;  break;
    }   
    bullet   = new Bullet(sf::Vector2f(bulletStartPosX, bulletStartPosY), dir);

}   

void Tank::deleteBullet() {
    if(bullet) {

        bullet = nullptr;
    }
}

bool Tank :: deleteAdjBlockIfExists(Map& tileMap) {
    int x = getGridPosition().x;
    int y = getGridPosition().y;

    switch(dir) {
        case UP:
            if(y - 1 >= 0 && tileMap.getTileMap()[y-1][x]->isBulletDestroyable()) {
                tileMap.destroyTile(x, y - 1);
                std::cout << "bullet not fired!" << std::endl;
                return true;
            }
            break;
        case DOWN:
            if(y + 1 < tileMap.getTileMap().size() && tileMap.getTileMap()[y + 1][x]->isBulletDestroyable()) {
                tileMap.destroyTile(x, y + 1);
                std::cout << "bullet not fired" << std::endl;
                return true;
            }
            break;
        case LEFT:
            if(x - 1 >= 0 && tileMap.getTileMap()[y][x - 1]->isBulletDestroyable()) {
                tileMap.destroyTile(x - 1, y);
                std::cout << "bullet not fired" << std::endl;
                return true;
            }
            break;
        case RIGHT:
            if(x + 1 < tileMap.getTileMap()[y].size() && tileMap.getTileMap()[y][x + 1]->isBulletDestroyable()) {
                tileMap.destroyTile(x + 1, y);
                std::cout << "bullet not fired" << std::endl;
                return true;
            }
            break;
    }

    return false;
}