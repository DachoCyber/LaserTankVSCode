#pragma once
#include <SFML/Audio.hpp>
#include <string>

extern sf::SoundBuffer mirrorSoundBuffer;
extern sf::Sound mirrorSound;

extern sf::SoundBuffer hitWallSoundBuffer;
extern sf::Sound hitWallSound;

void loadMirrorBubbleSound(const std::string& path);
void loadHitWallSoundBuffer(const std::string& path);