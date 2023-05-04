/**
 * Project 08: Cargo Chaos Conveyor class method definitions.
 * @file conveyor.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */
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

void Conveyor::spawn_random_node() {
    srand(time(0));
    int random = rand() % 100;
    if (random >= 60) {
        conveyor_nodes.push_back(new Laser_Node(constants::CONVEYOR_SPAWN_X, constants::CONVEYOR_SPAWN_Y));
    }
    else if (random >= 40) {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, constants::CONVEYOR_SPAWN_Y, 0));
    }
    else if (random >= 20) {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, constants::CONVEYOR_SPAWN_Y, 1));
    }
    else {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, constants::CONVEYOR_SPAWN_Y, 2));
    }
}

String Conveyor::pick_up_node() {
    if (!conveyor_nodes.empty() && conveyor_nodes[0]->get_node_sprite()->getPosition().x < 1.01 * constants::CONVEYOR_SPACING + constants::CONVEYOR_OFFSET) {
        String color = conveyor_nodes[0]->get_color();
        conveyor_nodes.erase(conveyor_nodes.begin());
        return color;
    }
    return "Empty";
    
}

void Conveyor::update() {
    for (int i = 0; i < conveyor_nodes.size(); i++) {
        if (conveyor_nodes[i]->get_node_sprite()->getPosition().x > i * constants::CONVEYOR_SPACING + constants::CONVEYOR_OFFSET) {
            conveyor_nodes[i]->get_node_sprite()->move(-2.3, 0);
        }
    }
}

void Conveyor::render(RenderWindow* window, int frames) {
    window->draw(get_conveyor_sprite(frames));
    for (Node* node : conveyor_nodes) {
        window->draw(*(node->get_node_sprite()));
    }
}

bool Conveyor::is_losing() {
    return conveyor_nodes.size() > constants::MAX_CONVEYOR_CAPACITY;
}

Conveyor::~Conveyor() {
    return;
}
