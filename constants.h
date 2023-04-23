#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/System.hpp>

namespace constants {
    const int SCREEN_HEIGHT = 1200;
    const int SCREEN_WIDTH = 1600;
    const float PLAYER_SCALE = 0.1;
    const float NODE_SCALE = 0.1;
    const sf::Vector2f off_screen(-100, -100);
}

#endif // CONSTANTS_H