/**
 * Project 08: Cargo Chaos Conveyor class declaration.
 * @file conveyor.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#ifndef CONVEYOR_H
#define CONVEYOR_H
#include <iostream>
#include <vector>
#include <random>
#include "node.h"
#include "cargo_node.h"
#include "laser_node.h"

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Conveyor {
private:
    Sprite conveyor_sprite;
    Texture conveyor_texture;
    int animation_status;
    vector<Node*> conveyor_nodes;
public:
    Conveyor();
    
    Sprite get_conveyor_sprite(int frames);

    void spawn_random_node();
    String pick_up_node();
    void update();
    void render(RenderWindow* window, int frames);
    bool is_losing();
};

#endif //CONVEYOR_H
