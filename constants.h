/**
 * Project 08: Cargo Chaos Constants namespace declaration.
 * @file constants.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

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
    const std::vector<float> CONVEYOR_PICK_UP_BOUNDS = { 450, 275 };
    const sf::Rect<float> EXIT_AREA_RECT(1242, 953, 214, 150); //Calculated using photoshop based on background

    const float NODE_SCALE = 0.275;
    const sf::Vector2f OFF_SCREEN(-100, -100);

    const float PLAYER_SCALE = 0.25;
    const int PLAYER_ANIMATION_FRAMES = 6;

    const float PLAYER_SPEED = 8;
    const float PLAYER_SPRINT_SPEED = 10;
    const float PLAYER_ENCUMBERED_SPEED = 5.5;
    const float PLAYER_ACCELERATION = 0.1; //not in use
    const float PLAYER_DECELERATION = 0.1; //not in use

    const int PLACE_DISTANCE = 110; // should be a function of node_size + player_size
    const float PLACE_ANGLE_OFFSET = -90;
    const float MAX_PLACE_OFFSET = 65;
    const float PLAYER_LASER_BUFFER = 5;

    const float INVALID_PLACEMENT_SHAKE= 0.8;
    const float HIT_SHAKE = 1.5;

    const int CONVEYOR_SPAWN_X = 1400;
    const int CONVEYOR_SPAWN_Y = 85;
    const int CONVEYOR_SPACING = 110;
    const int CONVEYOR_OFFSET = 400;
    const int MAX_CONVEYOR_CAPACITY = 6;

    const int SCORE_INCREMENT = 50;

    const float LASER_SPEED = 20;

    
}

#endif // CONSTANTS_H
