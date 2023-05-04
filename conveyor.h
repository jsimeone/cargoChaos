//
//  conveyor.h
//  SFMLPromisingTest
//
//  Created by Joseph Simeone on 4/24/23.
//

#ifndef conveyor_h
#define conveyor_h
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
};

#endif /* conveyor_h */
