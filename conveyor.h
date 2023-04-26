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
#include "node.h"
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
    ~Conveyor();
    
    Sprite get_conveyor_sprite(int frames);
};

#endif /* conveyor_h */
