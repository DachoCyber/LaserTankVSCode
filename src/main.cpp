#include "../include/game.h"
#include "../include/mainMenu/mainMenu.h"

#include "../include/mainMenu/resources.h"

#include "../include/movesProcessor.h"

#include <filesystem>
#include <curl/curl.h>

namespace fs = std::filesystem;

int countMapFiles(const std::string& folderPath) {
    int count = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".tmx")
                count++;
        }
    }

    return count;
}

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// Preuzmi jedan level
bool downloadLevel(int levelIndex, const std::string& baseUrl) {
    if (!fs::exists("maps")) {
        fs::create_directory("maps");
    }

    std::cout << levelIndex << std::endl;

    std::string localFile = "maps/map" + std::to_string(levelIndex) + ".tmx";

    std::cout << baseUrl << std::endl;

    // Preskoči ako već postoji
    if (fs::exists(localFile)) {
        std::cout << localFile << " already exists, skipping.\n";
        return true;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to init curl\n";
        return false;
    }

    std::string remoteFile = "https://alas.matf.bg.ac.rs/~mr22033/levels/uploads/map" + std::to_string(levelIndex) + ".tmx";

    std::cout << remoteFile << std::endl;

    FILE* fp = nullptr;
    if (fopen_s(&fp, localFile.c_str(), "wb") != 0 || !fp) {
        std::cerr << "Cannot open local file for writing: " << localFile << "\n";
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, remoteFile.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    fclose(fp);

    long response_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK || response_code != 200) {
        std::cerr << "Failed to download map" << levelIndex
            << " (HTTP code: " << response_code << ")\n";
        fs::remove(localFile); // briši nepotpuni fajl
        return false;
    }

    std::cout << "Downloaded map" << levelIndex << " successfully.\n";
    return true;
}

// Preuzmi sve levele dok ne naiđeš na prvi nepostojeći
void downloadAllLevels(const std::string& baseUrl) {
    int level = 1;
    for(; ; level++) {
        if (!downloadLevel(level, baseUrl)) {
            break; // prekini ako preuzimanje nije uspelo
        }
	}
}


int main() {

	std::string url = "https://alas.matf.bg.ac.rs/~mr22033/~public_html/levels/";

    downloadAllLevels(url);

    try {
        loadGlobalFont();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::string folder = "maps/";
    int levelCount = countMapFiles(folder);


    bool getIsClosed = false;
    MainMenu menu(levelCount);
    menu.run();

    bool enterAnotherLevel = false;
    int chosenLevel;
    do {
        //std::cout << chosenLevel << std::endl;
        if (!enterAnotherLevel) {
            chosenLevel = menu.getChosenLevel();
        }
        //std::cout << chosenLevel << std::endl;
        if (chosenLevel != -1) {
            MainGame game(512, 512, chosenLevel);
            game.run();
            getIsClosed = !game.getWindowClosedState();
            if (game.gameWon()) {
                
               // std::cout << "game won" << std::endl;
                enterAnotherLevel = true;
                
               // std::cout << game.getMovesCount() << std::endl;
               // std::cout << "Enter initials: ";
                
                std::string initials;
                std::cin >> initials;
                curl_global_init(CURL_GLOBAL_ALL);
                sendScore(initials, game.getMovesCount(), chosenLevel);
                curl_global_cleanup();


                chosenLevel = (chosenLevel + 1) % levelCount;
            }
        }
        //std::cout << getIsClosed << std::endl;
    } while (getIsClosed);
    return 0;
}
