//
//  conveyor.cpp
//  SFMLPromisingTest
//
//  Created by Joseph Simeone on 4/24/23.
//

#include "conveyor.h"

Conveyor::Conveyor() {
    animation_status = 225;
}

Sprite Conveyor::get_conveyor_sprite(int frames) {
    if (!conveyor_texture.loadFromFile("assets/conveyorStates.png")) {
        cout << "Loading conveyor texture failed" << endl;
    }
    
    sf::IntRect rect_source_sprite(0, animation_status, 1354, 225);
    
    
    if (frames % 30 == 0) {
        if (animation_status == 0) {
            animation_status = 225;
            rect_source_sprite.top = animation_status;
        } else {
            animation_status = 0;
            rect_source_sprite.top = animation_status;
        }
    }
    
    conveyor_sprite = Sprite(conveyor_texture, rect_source_sprite);
    
    return conveyor_sprite;
}

Conveyor::~Conveyor() {
    
}
