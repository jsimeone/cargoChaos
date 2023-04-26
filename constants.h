#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/System.hpp>
 
namespace constants {
    const float PI = 3.141526525;

    const int SCREEN_HEIGHT = 1200;
    const int SCREEN_WIDTH = 1600;
    const float NODE_SCALE = 0.05;
    const sf::Vector2f off_screen(-100, -100);

    const float PLAYER_SCALE = 0.1;

    const float PLAYER_SPEED = 10;
    const float PLAYER_ACCELERATION = 0.1; //not in use
    const float PLAYER_DECELERATION = 0.1; //not in use

    const int PLACE_DISTANCE = 85;
    const float PLACE_ANGLE_OFFSET = -90;
    const float MAX_PLACE_OFFSET = 30;

}

#endif // CONSTANTS_Hd
