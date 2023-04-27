#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/System.hpp>
#include <vector>
 
namespace constants {
    const float PI = 3.141526525;

    const int SCREEN_HEIGHT = 1200;
    const int SCREEN_WIDTH = 1600;

    const std::vector<float> PLAY_AREA_WIDTH_BOUNDS = {150, 1450};
    const std::vector<float> PLAY_AREA_HEIGHT_BOUNDS = {190, 1100};

    const float NODE_SCALE = 0.275;
    const sf::Vector2f off_screen(-100, -100);

    const float PLAYER_SCALE = 0.25;
    const int PLAYER_ANIMATION_FRAMES = 6;

    const float PLAYER_SPEED = 8;
    const float PLAYER_ACCELERATION = 0.1; //not in use
    const float PLAYER_DECELERATION = 0.1; //not in use

    const int PLACE_DISTANCE = 110; // should be a function of node_size + player_size
    const float PLACE_ANGLE_OFFSET = -90;
    const float MAX_PLACE_OFFSET = 50;

}

#endif // CONSTANTS_Hd
