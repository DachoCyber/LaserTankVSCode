#include "include/game.h"
#include "include/mainMenu/mainMenu.h"

#include "include/mainMenu/resources.h"

#include <filesystem>
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


int main() {

    try {
        loadGlobalFont();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::string folder = "maps/";
    int levelCount = countMapFiles(folder);  // dynamically count levels

    MainMenu menu(levelCount);
    menu.run();

    int chosenLevel = menu.getChosenLevel();
    if (chosenLevel != -1) {
        MainGame game(512, 512, chosenLevel);
        game.run();
    }

    return 0;
}
