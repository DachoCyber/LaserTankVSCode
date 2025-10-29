#include "include/game.h"
#include "include/playerInteraction.h"


MainGame::MainGame(int windowSizeX, int windowSizeY, int level) :
    window(std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowSizeX, windowSizeY),
        "Laser Tank",
        sf::Style::Close | sf::Style::Resize)),
    tileMap(level),
    player(tileMap.getPlayerPositionX(), tileMap.getPlayerPositionY(), windowSizeX, windowSizeY),
    windowSizeX(windowSizeX),
    windowSizeY(windowSizeY),
    bullets(0, nullptr)
{
    auto image = sf::Image{};
    std::string iconPath = "Images/tank.png";

    if (!image.loadFromFile(iconPath)) {
        throw std::runtime_error("Failed to load icon from: " + iconPath);
    }

    window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    int playerPosX = tileMap.getPlayerPositionX();
    int playerPosY = tileMap.getPlayerPositionY();
    sf::Vector2i playerPos = sf::Vector2i(playerPosX, playerPosY);
    player.setGridPosition(playerPos);
    window->setFramerateLimit(60);
    loadGoblet();
    loadGameOverFont();



    playerPositions.push_back(std::make_pair<int, int>(static_cast<unsigned>(playerPosX), static_cast<unsigned>(playerPosY)));


}


void MainGame::run() {

    bool waterToggle = false;
    while (window->isOpen()) {
        if (!gameEnd()) {

            if (windowEnableRepeatMovement.getElapsedTime() >= windowEnableRepMovTime) {
                isRepeatMovEnabled = true;
                windowEnableRepeatMovement.restart();
            }

            

            sf::Time time = waterFramesClock.getElapsedTime();
            if (time >= updateFramesWaterTile) {
                waterToggle = !waterToggle; // prebaci frame
                tileMap.switchFramesWaterTiles(waterToggle ? 1 : 0);
                waterFramesClock.restart();
            }

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {

                    window->close();
                    isWindowClosed = true;
                }
                if (event.type == sf::Event::KeyPressed && (!tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() || returnFromTrack) && (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() || !bulletFired)) {

                    handleInput();
                }
            }

            tileMap.updateTransportTracks();
            tileMap.updateWaterTiles();

            if (!tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]) {
                std::cout << "TILEMAP NULLPTR" << std::endl;
            }

            if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() && !returnFromTrack) {
                handlTransportableTrack(player.getGridPosition().y, player.getGridPosition().x);

            }
            if (!tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack()) {
                returnFromTrack = false;
            }

            update();
            render();
        }
        else {

            sf::Time gameEndShownTime = sf::seconds(3);
            sf::Clock clock;
            while (window->isOpen()) {
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                }

                window->clear(sf::Color::White);
                if (gameWon()) {
                    drawGoblet();
                }
                else if (gameLost()) {
                    window->draw(gameOverText);
                }
                if (clock.getElapsedTime() >= gameEndShownTime) {
                    window->close();
                }
                window->display();
            }
        }
    }
}
bool MainGame::playerKilledByEnemy() {
    for (const auto& bullet : bullets) {


        bool killed = (static_cast<int>(bullet->getPosition().x / tileSize == player.getGridPosition().x) && static_cast<int>(bullet->getPosition().y / tileSize == player.getGridPosition().y));
        if (killed) {
            return true;
        }
    }
    return false;
}

bool MainGame::shouldEnemyFireBullet() {
    for (int i = 0; i < tileMap.getTileMap().size(); i++) {
        for (int j = 0; j < tileMap.getTileMap()[i].size(); j++) {
            if (tileMap.getTileMap()[i][j]) {

                if (tileMap.getTileMap()[i][j]->killPlayer(
                    tileMap.getTileMap(),
                    player.getGridPosition().x * tileSize,
                    player.getGridPosition().y * tileSize)) {

                    std::cout << "now bullet should be fired" << std::endl;
                    tileMap.getTileMap()[i][j]->fireBullet();
                    bullets.push_back(tileMap.getTileMap()[i][j]->getBullet());
                    bulletFired = true;
                    coordXKillerTank = j;
                    coordYKillerTank = i;

                    isRepeatMovEnabled = false;
                    window->setKeyRepeatEnabled(false);
                    return true;
                }
            }
        }
    }
    return false;
}

void MainGame::handleInput() {
    sf::Keyboard::Key pressedKey = sf::Keyboard::Unknown;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movesPlayed++;
        pressedKey = sf::Keyboard::Up;


    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movesPlayed++;
        pressedKey = sf::Keyboard::Down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movesPlayed++;
        pressedKey = sf::Keyboard::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movesPlayed++;
        pressedKey = sf::Keyboard::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        movesPlayed++;
        pressedKey = sf::Keyboard::Space;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && moveCount > 0) {
        moveCount--;
        movesPlayed--;
        
        tileMap.undoMove(&mapStates.back());

        if(playerPositions.size() < 2) {
            return;
		}

        if(arrOfMoves.back() != sf::Keyboard::Space) {
            player.setGridPosition(sf::Vector2i(
                playerPositions[playerPositions.size() - 1].first,
                playerPositions[playerPositions.size() - 1].second));

            std::cout << "PLAYERPOSITIONS SIZE:" << playerPositions.size() << std::endl;

            if (playerPositions.size() > 0) {

                playerPositions.pop_back(); // Remove last move
            }

			//arrOfMoves.pop_back();
		}

		arrOfMoves.pop_back();
        mapStates.pop_back();

        return;
    }

    if (pressedKey != sf::Keyboard::Unknown) {

	    arrOfMoves.push_back(pressedKey);

        std::vector<std::pair<sf::Keyboard::Key, Direction>> keyDirPairs =
        { std::make_pair(sf::Keyboard::Up, UP),
          std::make_pair(sf::Keyboard::Down, DOWN),
          std::make_pair(sf::Keyboard::Left, LEFT),
          std::make_pair(sf::Keyboard::Right, RIGHT) };

        for (int i = 0; i < 4; i++) {

            if (pressedKey == keyDirPairs[i].first && player.getDir() == keyDirPairs[i].second) {
                
                playerPositions.push_back(std::make_pair<int, int>(
                    player.getGridPosition().x, player.getGridPosition().y));


                break;
            }
        }
        // Save state BEFORE movement
        std::cout << "Pushing player position: " << player.getGridPosition().x << " " << player.getGridPosition().y << std::endl;
        std::cout << "Map state:" << std::endl;


        std::cout << "Now pushing mapState(line 196):" << std::endl;
        mapStates.push_back(tileMap.getMapState());
        std::vector<std::vector<int>> currMapState2 = tileMap.getMapState();
        for (int i = 0; i < currMapState2.size(); i++) {
            for (int j = 0; j < currMapState2[i].size(); j++) {
                std::cout << currMapState2[i][j] << ", ";
            }
            std::cout << std::endl;
        }



        PlayerInteraction* playerInteraction = new PlayerInteraction(windowSizeX, windowSizeY, player, tileMap, pressedKey);
        playerInteraction->handleMovement();
        delete playerInteraction;
        
		
        
        playerMoved = true;
        moveCount++;
    }

    if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() && returnFromTrack && pressedKey != sf::Keyboard::Unknown) {
        returnFromTrack = false;
    }
}


void MainGame::update() {

    if (isRepeatMovEnabled) {
        window->setKeyRepeatEnabled(true);
    }

    if (bullets.size() == 0) {
        bulletFired = false;
    }

    if (player.getBullet() != nullptr) {

        BulletInteraction* bulletInteract = new BulletInteraction(windowSizeX, windowSizeY, player, tileMap);
        bulletInteract->interact();
        delete bulletInteract;
    }
    //std::cout << coordXKillerTank << " " << coordYKillerTank << std::endl;
    if (bullets.size() == 0 || (player.getGridPosition().x != coordXKillerTank && player.getGridPosition().y != coordYKillerTank)) {
        // std::cout << "should fire bullet " << std::endl;
        shouldEnemyFireBullet();
    }
    else {
        if (bullets.size() > 0) {
            std::cout << "bullet vector size is greater than 0" << std::endl;
        }
        if (player.getGridPosition().x != coordXKillerTank && player.getGridPosition().y != coordYKillerTank) {
            std::cout << "player grid position is not coord killer tank position" << std::endl;
        }
        std::cout << "bullet not  fired" << std::endl;
    }
    if (bullets.size() > 0) {
        const sf::Time updateInterval = sf::seconds(1.f / 60.f);
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i]->update(updateInterval);
        }
        if (killPlayer) {
            std::cout << "player should die" << std::endl;
        }
        //std::cout << static_cast<int>(bullet->getPosition().x)/tileSize << " " << static_cast<int>(bullet->getPosition().y)/tileSize << std::endl;
        //std::cout << player.getGridPosition().x << " " << player.getGridPosition().y << std::endl;
        for (int i = 0; i < bullets.size(); i++) {

            sf::Vector2f bulletPos = bullets[i]->getPosition();
            if (static_cast<int>(bulletPos.x) / tileSize == player.getGridPosition().x &&
                static_cast<int>(bulletPos.y) / tileSize == player.getGridPosition().y) {
                killPlayer = true;
                //std::fill(bullets.begin(), bullets.end(), nullptr);
            }
            if (bullets[i]->getPosition().x < 0 || bullets[i]->getPosition().x > windowSizeX ||
                bullets[i]->getPosition().y < 0 || bullets[i]->getPosition().y > windowSizeY) {
                bullets.erase(bullets.begin() + i);
            }
        }

    }
}


void MainGame::render() {
    window->clear(sf::Color::White);
    window->draw(tileMap);
    window->draw(player);
    for (int i = 0; i < bullets.size(); i++) {
        window->draw(*bullets[i]);
    }
    if (gameLost()) {
        window->draw(gameOverText);
    }

    window->display();
}

bool  MainGame::gameLost() {
    return player.getShouldKillPlayer() == true || killPlayer;
}

bool MainGame::gameWon() {
    return tileMap.getTileMapInt()[player.getGridPosition().y][player.getGridPosition().x] == 10;
}

bool MainGame::gameEnd() {
    return gameLost() || gameWon();
}

void MainGame::drawGoblet() {

    window->draw(gobletSprite);
}

void MainGame::loadGoblet() {
    try {
        if (!gobletTexture.loadFromFile("Images/goblet.png")) {
            throw std::runtime_error("Cannot load goblet image");
        }

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    gobletSprite.setTexture(gobletTexture);
    gobletSprite.setOrigin(gobletSprite.getLocalBounds().width / 2, gobletSprite.getLocalBounds().height / 2);
    gobletSprite.setPosition(sf::Vector2f(static_cast<float>(windowSizeX) / 2, static_cast<float>(windowSizeY) / 2));
}
void MainGame::loadGameOverFont() {
    try {
        if (!weirdFont.loadFromFile("Fonts/Creepster-Regular.ttf")) {
            throw std::runtime_error("Cannot load weird font");
        }

        gameOverText.setFont(weirdFont);

        gameOverText.setString("GAME OVER");

        gameOverText.setCharacterSize(80);

        gameOverText.setFillColor(sf::Color::Red);

        gameOverText.setStyle(sf::Text::Bold | sf::Text::Italic);

        sf::FloatRect textBounds = gameOverText.getLocalBounds();

        gameOverText.setOrigin(textBounds.left + textBounds.width / 2.f,
            textBounds.top + textBounds.height / 2.f);

        gameOverText.setPosition(static_cast<float>(windowSizeX) / 2,
            static_cast<float>(windowSizeY) / 2);

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void MainGame::handlTransportableTrack(int y, int x) {
    if (returnFromTrack) return;

    int dx = 0, dy = 0;
    if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() == 1) {
        dx = -1;
    }
    else if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() == 2) {
        dx = 1;
    }
    else if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() == 3) {
        dy = -1;
    }
    else if (tileMap.getTileMap()[player.getGridPosition().y][player.getGridPosition().x]->isTransportTrack() == 4) {
        dy = 1;
    }
    if (player.validMove(x + dx, y + dy)) {

        if (tileMap.getTileMap()[y + dy][x + dx]->isTileMovableBlock() ||
            tileMap.getTileMap()[y + dy][x + dx]->isBulletDestroyable() ||
            tileMap.getTileMap()[y + dy][x + dx]->isMirror1() ||
            tileMap.getTileMap()[y + dy][x + dx]->isMirror2() ||
            tileMap.getTileMap()[y + dy][x + dx]->isMirror3() ||
            tileMap.getTileMap()[y + dy][x + dx]->isMirror4() ||
            tileMap.getTileMap()[y + dy][x + dx]->isTank()) {
            returnFromTrack = true;
            return;
        }
        int currGridCoordX = x;
        int currGridCoordY = y;

        returnFromTrack = false;

        player.setGridPosition(sf::Vector2i(x + dx, y + dy));

    }
}

bool MainGame::getWindowClosedState() const {
    return isWindowClosed;
}