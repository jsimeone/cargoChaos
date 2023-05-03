/**
 * Project 08: Cargo Chaos AudioConstants declaration.
 * @file AudioConstants.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#ifndef AUDIO_CONSTANTS_H
#define AUDIO_CONSTANTS_H

#include <SFML/Audio.hpp>

class AudioConstants {
public:
    static sf::SoundBuffer selectSoundBuffer;
    static sf::SoundBuffer clickSoundBuffer;
    static sf::Music gameplayMusic;
    static sf::Music backgroundMusic;

    static sf::Sound selectSound;
    static sf::Sound clickSound;

    static void loadSounds();
};

#endif // AUDIO_CONSTANTS_H
