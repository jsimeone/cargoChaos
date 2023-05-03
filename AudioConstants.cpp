/**
 * Project 08: Cargo Chaos AudioConstants class method definitions.
 * @file AudioConstants.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#include "AudioConstants.h"
#include <iostream>

sf::SoundBuffer AudioConstants::selectSoundBuffer;
sf::SoundBuffer AudioConstants::clickSoundBuffer;
sf::Music AudioConstants::gameplayMusic;
sf::Music AudioConstants::backgroundMusic;

sf::Sound AudioConstants::selectSound;
sf::Sound AudioConstants::clickSound;

void AudioConstants::loadSounds() {
    if (!selectSoundBuffer.loadFromFile("assets/select.wav")) {
        std::cout << "Error loading select sound!" << std::endl;
    }
    if (!clickSoundBuffer.loadFromFile("assets/enter.wav")) {
        std::cout << "Error loading click sound!" << std::endl;
    }
    if (!backgroundMusic.openFromFile("assets/soundtrack.wav")) {
        std::cout << "Error loading sountrack!" << std::endl;
    }
    if (!gameplayMusic.openFromFile("assets/Gameplay.wav")) {
        std::cout << "Error loading gameplay music!" << std::endl;
    }

    selectSound.setBuffer(selectSoundBuffer);
    clickSound.setBuffer(clickSoundBuffer);
}
