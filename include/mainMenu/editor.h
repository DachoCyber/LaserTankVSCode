#pragma once

#include "editorButton.h"

#include <sstream>
#include <ostream>

#include <filesystem>
#include <curl/curl.h>

#include "../walkableGround.h"
#include "../tile.h"
#include "../destructibleBlock.h"
#include "../mirror1Tile.h"
#include "../mirror2Tile.h"
#include "../mirror3Tile.h"
#include "../mirror4Tile.h"
#include "../waterTile.h"
#include "../movableBlock.h"
#include "../undestructableBlock.h"
#include "../tank1.h"
#include "../destroyedTank.h"
#include "../transportTrack.h"
#include "../tileInWater.h"


#include "../flag.h"

#include <fstream>

#include <vector>

class Editor : public sf :: Drawable {
public:

    bool editorWinClose = false;

    int tileSize = 32;

    EditorButton button;
    sf::Texture walkableTexture;
    sf::Texture destructibleTexture;
    sf::Texture mirror1Texture;
    sf::Texture mirror2Texture;
    sf::Texture mirror3Texture;
    sf::Texture mirror4Texture;
    sf::Texture waterTileTexture;
    sf::Texture flagTexture;
    sf::Texture movableBlockTexture;
    sf::Texture undestructableBlockTex;
    sf::Texture waterSecondFrameTexture;

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

    sf::Texture tankTex;

    sf::Texture tileInWaterTex;
    std::vector<std::vector<int>> tileMap;

	sf::Font tankInstructionTextFont;
	sf::Text tankInstructionText;

	sf::RectangleShape tankInstructionBackground;

	sf::RectangleShape tileInstructionBackground;

	sf::Font tileInstructionTextFont;
	sf::Text tileInstructionText;

public:
    Editor(int menuWinSizeX, int menuWinSizeY, bool editorWinClose) : button(menuWinSizeX, menuWinSizeY, editorWinClose) {}
    
    std::vector<std::vector<int>> getTileMap() { return tileMap; }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(button);
    }

    bool wasClicked() {
        return button.wasClicked();
    }

    void handleClick() {
        sf::Image destructibleBlock;        
        if(editorWinClose) return;

        if (!walkableTexture.loadFromFile("Images/walkableGround.png")) {
        throw std::runtime_error("Failed to load walkable texture");
    }
    if (!destructibleTexture.loadFromFile("Images/destructibleBlock.png")) {
        throw std::runtime_error("Failed to load destructible texture");
    }
    if(!mirror1Texture.loadFromFile("Images/Mirror1WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 1 texture");
    }
    if(!mirror2Texture.loadFromFile("Images/Mirror2WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 2 texture");
    }
    if(!mirror3Texture.loadFromFile("Images/Mirror3WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 3 texture");
    }
    if(!mirror4Texture.loadFromFile("Images/Mirror4WithBackground.png")) {
        throw std::runtime_error("Failed to load mirror 4 texture");
    }
    if(!waterTileTexture.loadFromFile("Images/waterTile.png")) {
        throw std::runtime_error("Failed to load water tile texture");
    }
    if (!waterSecondFrameTexture.loadFromFile("Images/waterTileSecondFrame.png")) {
        throw std::runtime_error("Failed to load water tile second frame texture");
    }
    if(!movableBlockTexture.loadFromFile("Images/MovableBlock.png")) {
        throw std::runtime_error("Failed to load water tile texture");
    }
    if(!flagTexture.loadFromFile("Images/flagWithBackground.png")) {
        throw std::runtime_error("Failed to load flag texture");
    }
    if(!undestructableBlockTex.loadFromFile("Images/undestructibleBlock.png")) {
        throw std::runtime_error("Failed to load undestructible block texture");
    }
    if(!EnemyTank1LeftTexture.loadFromFile("Images/tank1.png")) {
        throw std::runtime_error("Failed to load enemy tank left texture");
    }
    if(!EnemyTank1RightTexture.loadFromFile("Images/tank2.png")) {
        throw std::runtime_error("Failed to load enemy tank left texture");
    }
    if(!EnemyTank1UpTexture.loadFromFile("Images/tank3.png")) {
        throw std::runtime_error("Failed to load enemy tank up texture");
    }
    if(!EnemyTank1DownTexture.loadFromFile("Images/tank4.png")) {
        throw std::runtime_error("Failed to load enemy tank down texture");
    }
    if(!destroyedTankLeftTexture.loadFromFile("Images/destroyedTank1.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankUpTexture.loadFromFile("Images/destroyedTank2.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankDownTexture.loadFromFile("Images/destroyedTank3.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }
    if(!destroyedTankRightTexture.loadFromFile("Images/destroyedTank4.png")) {
        throw std::runtime_error("Failed to load destoryed tank left texutre");
    }

    if(!transportTrackDownTex.loadFromFile("Images/transportTrack4.png")) {
        throw std::runtime_error("Failed to load transport track texture");
    }
    if(!transportTrackUpTex.loadFromFile("Images/transportTrack3.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!transportTrackRightTex.loadFromFile("Images/transportTrack2.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!transportTrackLeftTex.loadFromFile("Images/transportTrack.png")) {
        throw std::runtime_error("Failed to load transport track 3 texture");
    }
    if(!tileInWaterTex.loadFromFile("Images/tileInWater.png")) {
        throw std::runtime_error("Failed to load tile in water texture");
    } 
    if(!tankTex.loadFromFile("Images/tank.png")) {
        throw std::runtime_error("Failed to load tank texture");
    }


        int mapSizeX = 512;
        int windowSizeY = 512;
        int mapElementsSizeX = 256;
        sf::Sprite tankInstructionSprite(tankTex);
        int windowSizeX = mapSizeX + mapElementsSizeX;
        sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Editor", sf::Style::Default);

        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        tiles.resize(16);

        if (!tileInstructionTextFont.loadFromFile("Fonts/arial.ttf"))
            throw new std::runtime_error("Failed to load instruction font!");
        tankInstructionTextFont = tileInstructionTextFont;
        sf::RectangleShape instructionPanel;
        instructionPanel.setFillColor(sf::Color::White);
        instructionPanel.setSize(sf::Vector2f(256, 200));  // širina i visina panela
        instructionPanel.setPosition(sf::Vector2f(512, 96)); // stavi ga desno od mape


        tankInstructionSprite.setScale(0.5f, 0.5f); // smanji da lepo stane, po potrebi
        tankInstructionSprite.setPosition(
            instructionPanel.getPosition().x + 16,
            instructionPanel.getPosition().y + 16
        );

        // Tekst "Press LB" pored tenka
        sf::Text pressLbText;
        pressLbText.setFont(tankInstructionTextFont);
        pressLbText.setString("Click mouse Right\n Button for tank");
        pressLbText.setCharacterSize(24);
        pressLbText.setFillColor(sf::Color::Black);
        pressLbText.setPosition(
            tankInstructionSprite.getPosition().x + tankInstructionSprite.getGlobalBounds().width + 12,
            tankInstructionSprite.getPosition().y
        );

        // Tekst "Press RB" ispod
        sf::Text pressRbText;
        pressRbText.setFont(tankInstructionTextFont);
        pressRbText.setString("Click mouse Left\n Button for tile ");
        pressRbText.setCharacterSize(24);
        pressRbText.setFillColor(sf::Color::Black);
        pressRbText.setPosition(
            pressLbText.getPosition().x,
            pressLbText.getPosition().y + pressLbText.getGlobalBounds().height + 50
        );


        bool tankPlaced = false;
        bool flagPlaced = false;

        
        sf::Sprite destructibleBlockSprite = createSprite(destructibleTexture, 16, 0, tileSize);
        sf::Sprite mirror1Sprite = createSprite(mirror1Texture, 17, 0, tileSize);   
        sf::Sprite mirror2Sprite = createSprite(mirror2Texture, 18, 0, tileSize);
        sf::Sprite mirror3Sprite = createSprite(mirror3Texture, 19, 0, tileSize);
        sf::Sprite mirror4Sprite = createSprite(mirror4Texture, 20, 0, tileSize);

        sf::Sprite waterSprite = createSprite(waterTileTexture, 21, 0, tileSize);
        sf::Sprite MovableBlockSprite = createSprite(movableBlockTexture, 22, 0, tileSize);
        sf::Sprite flagSprite = createSprite(flagTexture, 17,2, tileSize);
        sf::Sprite undestructableBlockSprite = createSprite(undestructableBlockTex, 23, 0, tileSize);

        sf::Sprite tank1LeftSprite = createSprite(EnemyTank1LeftTexture, 16, 1, tileSize);
        sf::Sprite tank1RightSprite = createSprite(EnemyTank1RightTexture, 17, 1, tileSize);
        sf::Sprite tank1UpSprite = createSprite(EnemyTank1UpTexture, 18, 1, tileSize);
        sf::Sprite tank1DownSprite = createSprite(EnemyTank1DownTexture, 19, 1, tileSize);

        sf::Sprite transportLeftSprite = createSprite(transportTrackLeftTex, 20, 1, tileSize);
        sf::Sprite transportDownSprite = createSprite(transportTrackDownTex, 21, 1, tileSize);
        sf::Sprite transportUpSprite = createSprite(transportTrackUpTex, 22, 1, tileSize);
        sf::Sprite transportRightSprite = createSprite(transportTrackRightTex, 23, 1, tileSize);

        sf::Sprite tankSprite(tankTex);
        
        tankSprite.setScale(sf::Vector2f(0.65, 0.65)); 
        tankInstructionSprite.setScale(sf::Vector2f(0.65, 0.65));

    tileMap.resize(16);
    for (int y = 0; y < 16; y++) {
        tiles[y].resize(16);
        tileMap[y].resize(16);
        for (int x = 0; x < 16; x++) {
            tiles[y][x] = std::make_unique<WalkableGround>(x * tileSize, y * tileSize, walkableTexture);
            
            tileMap[y][x] = 1;
        }
    }

    sf::Vector2i placedTile = {-1, -1};

    bool placingCode[20] = {false};

    int tankPosX;
	int tankPosY;

    tileInstructionBackground.setFillColor(sf::Color::White);

    tileInstructionBackground.setPosition(sf::Vector2f(512, 128));

    tileInstructionBackground.setSize(sf::Vector2f(256, 64));
    tankInstructionBackground.setFillColor(sf::Color::White);
    tankInstructionBackground.setSize(sf::Vector2f(256, 64));
    tankInstructionBackground.setPosition(sf::Vector2f(512, 96));




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {

                window.close();
                editorWinClose = true;
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i tileCoords = getTileCoords(window);
                int tileX = tileCoords.x;
                int tileY = tileCoords.y;
				tankPosX = tileX;
				tankPosY = tileY;
                tankSprite.setPosition({static_cast<float>(tileX*tileSize), static_cast<float>(tileY*tileSize)});
                tankPlaced = true;
            }

           if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2i tileCoords = getTileCoords(window);
                int tileX = tileCoords.x;
                int tileY = tileCoords.y;

                if (destructibleBlockSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[3] = true;
                    tileMap[tileY][tileX] = 3;
                } else if (placingCode[3] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    tileMap[tileY][tileX] = 1;
                    placeOrRemoveTile<DestructibleBlock>(tileX, tileY, 3, 1, tiles, tileMap, destructibleTexture);
                }

                if (mirror1Sprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[4] = true;
                } else if (placingCode[4] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror1Tile>(tileX, tileY, 4, 1, tiles, tileMap, mirror1Texture);
                }

                if (mirror2Sprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[5] = true;
                } else if (placingCode[5] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror2Tile>(tileX, tileY, 5, 1, tiles, tileMap, mirror2Texture);
                }

                if(mirror3Sprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[6] = true;
                } else if (placingCode[6] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror3Tile>(tileX, tileY, 6, 1, tiles, tileMap, mirror3Texture);
                }

                if(mirror4Sprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[7] = true;
                } else if (placingCode[7] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Mirror4Tile>(tileX, tileY, 7, 1, tiles, tileMap, mirror4Texture);
                }
                if(waterSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[8] = true;
                } else if (placingCode[8] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveWaterTile(tileX, tileY, tiles, tileMap);
                }
                if(MovableBlockSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[9] = true;
                } else if (placingCode[9] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<MovableBlock>(tileX, tileY, 9, 1, tiles, tileMap, movableBlockTexture);
                }
                if(flagSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[10] = true;
                    flagPlaced = true;
                } else if (placingCode[10] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<Flag>(tileX, tileY, 10, 1, tiles, tileMap, flagTexture);
                }

                if(undestructableBlockSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[11] = true;
                } else if (placingCode[11] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTile<UndestructableBlock>(tileX, tileY, 11, 1, tiles, tileMap, undestructableBlockTex);
                }
                if(tank1LeftSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[12] = true;
                } else if (placingCode[12] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTank(tileX, tileY, 12, 1, tiles, tileMap,LEFT, EnemyTank1LeftTexture);
                }

                if(tank1RightSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[13] = true;
                } else if (placingCode[13] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTank(tileX, tileY, 13, 1, tiles, tileMap,RIGHT, EnemyTank1RightTexture);
                }
                if(tank1UpSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[14] = true;
                } else if (placingCode[14] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTank(tileX, tileY, 14, 1, tiles, tileMap,UP, EnemyTank1UpTexture);
                }
                if(tank1DownSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[15] = true;
                } else if (placingCode[15] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTank(tileX, tileY, 15, 1, tiles, tileMap,DOWN, EnemyTank1DownTexture);
                }
                if(transportDownSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[16] = true;
                } else if (placingCode[16] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTrack(tileX, tileY, 23, 1, tiles, tileMap,DOWN, transportTrackDownTex);
                }
                if(transportUpSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[17] = true;
                } else if (placingCode[17] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTrack(tileX, tileY, 22, 1, tiles, tileMap,UP, transportTrackUpTex);
                }
                if(transportLeftSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[18] = true;
                } else if (placingCode[18] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTrack(tileX, tileY, 20, 1, tiles, tileMap,LEFT, transportTrackLeftTex);
                }
                if(transportRightSprite.getGlobalBounds().contains(worldPos)) {
                    for(int i = 0; i < 20; i++) {
                        placingCode[i] = false;
                    }
                    placingCode[19] = true;
                } else if (placingCode[19] && tileX >= 0 && tileX < 16 && tileY >= 0 && tileY < 16) {
                    placeOrRemoveTrack(tileX, tileY, 21, 1, tiles, tileMap,RIGHT, transportTrackRightTex);
                }
            }

        }

        window.clear();
        for (int y = 0; y < 16; ++y)
            for (int x = 0; x < 16; ++x)
                window.draw(*tiles[y][x]);

        window.draw(destructibleBlockSprite);
        window.draw(mirror1Sprite);
        window.draw(mirror2Sprite);
        window.draw(mirror3Sprite);
        window.draw(mirror4Sprite);
        window.draw(waterSprite);
        window.draw(MovableBlockSprite);
        window.draw(flagSprite);
        window.draw(undestructableBlockSprite);
        window.draw(tank1LeftSprite);
        window.draw(tank1DownSprite);
        window.draw(tank1UpSprite);
        window.draw(tank1RightSprite);
        window.draw(transportDownSprite);
        window.draw(transportLeftSprite);
        window.draw(transportRightSprite);
        window.draw(transportUpSprite);
        window.draw(instructionPanel);
        window.draw(tankInstructionSprite);
        window.draw(pressLbText);
        window.draw(pressRbText);




        if(tankPlaced) {
            window.draw(tankSprite);
        }

        window.display();
    }
        if (tankPlaced && flagPlaced) {
            int height = 16;
            int width = 16;
        

            std::string folder = "maps/";
            std::string levelName = generateNextMapFilename(folder); // already includes .tmx

            std::cout << levelName << std::endl;

            std::ofstream file(folder + levelName);
            if (!file.is_open()) {
                std::cerr << "Failed to open file for writing!\n";
                return;
            }

            int levelIndex = extractLevelIndex(levelName);
            std::cout << "Creating level " << levelIndex << " with filename: " << levelName << std::endl;

            // proceed to write to file...

            // Replace .tmx if not present
            if (levelName.find(".tmx") == std::string::npos)
                levelName += ".tmx";


            file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
            file << "<map version=\"1.0\" tiledversion=\"1.9.2\" orientation=\"orthogonal\" renderorder=\"right-down\" ";
            file << "width=\"" << width << "\" height=\"" << height << "\" tilewidth=\"32\" tileheight=\"32\" infinite=\"0\">\n";
            file << "  <tileset firstgid=\"1\" name=\"tileset\" tilewidth=\"32\" tileheight=\"32\" tilecount=\"10\" columns=\"10\">\n";
            file << "    <image source=\"tileset.png\" width=\"320\" height=\"32\"/>\n";
            file << "  </tileset>\n";
            file << "  <layer name=\"Tile Layer 1\" width=\"" << width << "\" height=\"" << height << "\">\n";
            file << "    <data encoding=\"csv\">\n";

            std::cout << "TankPosY: " << tankPosY << " TankPosX: " << tankPosX << std::endl;

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {

                    if (y == tankPosY && x == tankPosX) file << 0;
                    else {

                        file << tileMap[y][x];
                        
                    }
                    if (x < width - 1) file << ",";
                }
                if (y < height - 1) file << ",\n";
                else file << "\n";
            }

            file << "    </data>\n";
            file << "  </layer>\n";
            file << "</map>\n";


            file.close();


            const std::string& url = "https://alas.matf.bg.ac.rs/~mr22033/public_html/levels";
   



            pushTileMapToServer(levelIndex);

    
}

        

    }
    void pushTileMapToServer(int levelIndex) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Failed to init curl\n";
            return;
        }

        std::string fileName = "maps/map" + std::to_string(levelIndex) + ".tmx";

        if (!std::filesystem::exists(fileName)) {
            std::cerr << "File does not exist: " << fileName << "\n";
            curl_easy_cleanup(curl);
            return;
        }

        // Direktno ka upload.php na tvom serveru
        std::string url = "https://alas.matf.bg.ac.rs/~mr22033/levels/upload.php";

        // Form-data upload
        curl_mime* form = curl_mime_init(curl);
        curl_mimepart* field = curl_mime_addpart(form);
        curl_mime_name(field, "file");
        curl_mime_filedata(field, fileName.c_str());

        // Opcije
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // debug

        std::cout << "Uploading " << fileName << " to " << url << std::endl;

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cout << "HTTP Response Code: " << response_code << std::endl;
            std::cout << "Server Response: " << response << std::endl;
        }

        curl_mime_free(form);
        curl_easy_cleanup(curl);
    }



    sf::Vector2i getTileCoords(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        return { static_cast<int>(worldPos.x) / tileSize, static_cast<int>(worldPos.y) / tileSize };
    }

    void placeOrRemoveWaterTile(int tileX, int tileY, 
        std::vector<std::vector<std::unique_ptr<Tile>>>& tiles,
        std::vector<std::vector<int>>& tileMap) 
    {
        if (dynamic_cast<WaterTile*>(tiles[tileY][tileX].get())) {
            tileMap[tileY][tileX] = 1;
            tiles[tileY][tileX] = std::make_unique<WalkableGround>(tileX * tileSize, tileY * tileSize, walkableTexture);
        } else {
            tileMap[tileY][tileX] = 8;
        
            tiles[tileY][tileX] = std::make_unique<WaterTile>(
                tileX * tileSize,
                tileY * tileSize,
                waterTileTexture,
                waterSecondFrameTexture
            );
		}
    }

    void placeOrRemoveTank(
        int tileX, int tileY, 
        int placeID, int removeID,
        std::vector<std::vector<std::unique_ptr<Tile>>>& tiles,
        std::vector<std::vector<int>>& tileMap, Direction dir,
        sf::Texture& tileTexture
    ) 
    {

        if (dynamic_cast<EnemyTank1*>(tiles[tileY][tileX].get())) {
            tileMap[tileY][tileX] = removeID;
            tiles[tileY][tileX] = std::make_unique<WalkableGround>(tileX * tileSize, tileY * tileSize, walkableTexture);
        } else {
            tileMap[tileY][tileX] = placeID;
        

            tiles[tileY][tileX] = std::make_unique<EnemyTank1>(tileX * tileSize, tileY * tileSize, dir, tileTexture);
        }
    }

    void placeOrRemoveTrack(
        int tileX, int tileY, 
        int placeID, int removeID,
        std::vector<std::vector<std::unique_ptr<Tile>>>& tiles,
        std::vector<std::vector<int>>& tileMap, Direction dir,
        sf::Texture& tileTexture
    ) 
    {

        if (dynamic_cast<TransportTrack*>(tiles[tileY][tileX].get())) {
            tileMap[tileY][tileX] = removeID;
            tiles[tileY][tileX] = std::make_unique<WalkableGround>(tileX * tileSize, tileY * tileSize, walkableTexture);
        } else {
            tileMap[tileY][tileX] = placeID;
        

            tiles[tileY][tileX] = std::make_unique<TransportTrack>(tileX * tileSize, tileY * tileSize, dir, tileTexture);
        }
    }

    template<typename TileType>
    void placeOrRemoveTile(
        int tileX, int tileY, 
        int placeID, int removeID,
        std::vector<std::vector<std::unique_ptr<Tile>>>& tiles,
        std::vector<std::vector<int>>& tileMap,
        sf::Texture& tileTexture
    ) 
    {

        if (dynamic_cast<TileType*>(tiles[tileY][tileX].get())) {
            tileMap[tileY][tileX] = removeID;
            tiles[tileY][tileX] = std::make_unique<WalkableGround>(tileX * tileSize, tileY * tileSize, walkableTexture);
        } else {
            tileMap[tileY][tileX] = placeID;

            if (placeID == 8) {
                // water tile ? 3 argumenta
                tiles[tileY][tileX] = std::make_unique<WaterTile>(
                    tileX * tileSize,
                    tileY * tileSize,
                    tileInWaterTex,
                    waterSecondFrameTexture
                );
            }
            else {
                // svi ostali ? 2 argumenta
                tiles[tileY][tileX] = std::make_unique<TileType>(
                    tileX * tileSize,
                    tileY * tileSize,
                    tileTexture
                );
            }

        }
    }

    sf::Sprite createSprite(sf::Texture& texture, int gridX, int gridY, int tileSize) {
    sf::Sprite sprite(texture);
        sprite.setScale(sf::Vector2f(
            tileSize / sprite.getGlobalBounds().width,
            tileSize / sprite.getGlobalBounds().height
        ));
        sprite.setPosition(static_cast<float>(gridX * tileSize), static_cast<float>(gridY * tileSize));
        return sprite;
    }


    std::string generateNextMapFilename(const std::string& folderPath) {
        namespace fs = std::filesystem;

        int maxIndex = 0;

        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();

                // Check if the file starts with "map" and ends with ".tmx"
                if (filename.size() > 7 && filename.substr(0, 3) == "map" &&
                    filename.substr(filename.size() - 4) == ".tmx") {

                    // Extract the number part
                    std::string numberPart = filename.substr(3, filename.size() - 7);
                    try {
                        int index = std::stoi(numberPart);
                        if (index > maxIndex)
                            maxIndex = index;
                    } catch (...) {
                        // Not a valid number, ignore
                    }
                }
            }
        }

        return "map" + std::to_string(maxIndex + 1) + ".tmx";
    }
    int extractLevelIndex(const std::string& levelName) {
    // Assumes format is "map<number>.tmx"
        if (levelName.substr(0, 3) != "map" || levelName.size() <= 7 || 
            levelName.substr(levelName.size() - 4) != ".tmx") {
            throw std::invalid_argument("Invalid level name format");
        }

        std::string numberPart = levelName.substr(3, levelName.size() - 7); // removes "map" and ".tmx"
        return std::stoi(numberPart);
    }

};