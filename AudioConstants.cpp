#include "AudioConstants.h"
#include <iostream>

sf::SoundBuffer AudioConstants::selectSoundBuffer;
sf::SoundBuffer AudioConstants::clickSoundBuffer;
sf::Music AudioConstants::gameplayMusic;

sf::Sound AudioConstants::selectSound;
sf::Sound AudioConstants::clickSound;

void AudioConstants::loadSounds() {
    if (!selectSoundBuffer.loadFromFile("assets/select.wav")) {
        std::cout << "Error loading select sound!" << std::endl;
    }
    if (!clickSoundBuffer.loadFromFile("assets/enter.wav")) {
        std::cout << "Error loading click sound!" << std::endl;
    }


    selectSound.setBuffer(selectSoundBuffer);
    clickSound.setBuffer(clickSoundBuffer);

}
