#pragma once

#define SFML_STATIC

#include "bulletInteraction.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Audio.hpp>



class MainGame {
public:
    MainGame(int windowSizeX, int windowSizeY, int level);
    ~MainGame() = default;
    void run();
    
    bool getWindowClosedState() const;

    bool gameEnd();
    bool gameLost();
    bool gameWon();
    
    int getMovesCount() { return movesPlayed; }
private:
    void loadGoblet();
    void drawGoblet();



    void loadGameOverFont();

    bool shouldEnemyFireBullet();
    bool playerKilledByEnemy();



    void setTrack();
    void handlTransportableTrack(int x, int y);

    void handleInput();
    void render();
    void update();

    std::unique_ptr<sf::RenderWindow> window;
    Tank player;
    Map tileMap;
    
    bool isWindowClosed;

    int startTankX;
    int startTankY;

    int countSpacePressed;


    int currBulletGridPosX, currBulletGridPosY;
    int nextBulletGridPosX, nextBulletGridPosY;
    bool shouldBeDeleted = false;

    const int tileSize = 32;
    bool moveQueued = false;
    int windowSizeX, windowSizeY;

    bool killPlayer = false;
    bool bulletFired = false;
	bool playerFiredBullet = false;

    bool playerMovedFromLastPosition = false;
    bool updated = false;

    bool returnFromTrack = false;

    std::vector<Bullet*> bullets;
    sf::Clock gameClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time timePerFrame = sf::seconds(1.f/60.f);

    sf::Time updateFramesWaterTile = sf::seconds(0.5);

    sf::Clock waterFramesClock;

    sf::Font weirdFont;
    sf::Text gameOverText;


    sf::Texture gobletTexture;
    sf::Sprite gobletSprite;

    std::vector<std::vector<std::vector<int>>> mapStates;

    std::vector<sf::Keyboard::Key> arrOfMoves;


    bool playerMoved = false;
    int moveCount = 0;
    std::vector<std::pair<int, int>> playerPositions;
    int coordXKillerTank, coordYKillerTank;

    sf::Clock windowEnableRepeatMovement;
    const sf::Time windowEnableRepMovTime = sf::seconds(0.5f);
    bool isRepeatMovEnabled = false;
    int movesPlayed = 0;
};

