//
//  conveyor.cpp
//  SFMLPromisingTest
//
//  Created by Joseph Simeone on 4/24/23.
//

#include "conveyor.h"

Conveyor::Conveyor() : 
    animation_status(225) 
{
    if (!conveyor_texture.loadFromFile("assets/ConveyorSpriteSheet.png")) {


        cout << "Loading conveyor texture failed" << endl;
    }
    conveyor_sprite.setTexture(conveyor_texture);
    conveyor_sprite.setOrigin(-461, 0);
}

Sprite Conveyor::get_conveyor_sprite(int frames) {
    
    if (frames % 10 == 0) {
        conveyor_sprite.setTextureRect(IntRect(animation_status, 0, 865, 171));
        animation_status += 865;
        
        if (animation_status > 3459) {
            animation_status = 0;
        }
    }
    
    return conveyor_sprite;
}

Conveyor::~Conveyor() {
    return;
}
