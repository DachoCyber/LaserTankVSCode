#define SFML_STATIC
#include "../include/loadSound.h"
#include <iostream>

sf::SoundBuffer mirrorSoundBuffer;
sf::Sound mirrorSound;

sf::SoundBuffer hitWallSoundBuffer;
sf::Sound hitWallSound;

void loadMirrorBubbleSound(const std::string& path) {
    if (!mirrorSoundBuffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        return;
    }
    mirrorSound.setBuffer(mirrorSoundBuffer);
}

void loadHitWallSoundBuffer(const std::string& path) {
    if (!hitWallSoundBuffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        return;
    }
    hitWallSound.setBuffer(hitWallSoundBuffer);
}
