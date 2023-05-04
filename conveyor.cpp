/**
 * Project 08: Cargo Chaos Conveyor class method definitions.
 * @file conveyor.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */
#include "conveyor.h"

/**
 @brief: Constructor for a Conveyor object
 */
Conveyor::Conveyor() : 
    animation_status(225) 
{
    if (!conveyor_texture.loadFromFile("assets/ConveyorSpriteSheet.png")) {


        cout << "Loading conveyor texture failed" << endl;
    }
    conveyor_sprite.setTexture(conveyor_texture);
    conveyor_sprite.setOrigin(-461, 0);
}

/**
 @brief: Gets the correct sprite for a conveyor object depending on frames
 @param frames The current frame the game is on. Used to calculate which frame of conveyor animation should be shown
 @return: A Sprite with the correct texture
 */
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

/**
 @brief: Spawns a random color node on the conveyor. Adds the node to the conveyor_nodes vector
 */
void Conveyor::spawn_random_node() {
    srand(time(0));
    int random = rand() % 100;
    if (random >= 60) {
        conveyor_nodes.push_back(new Laser_Node(constants::CONVEYOR_SPAWN_X, 
                                                constants::CONVEYOR_SPAWN_Y));
    }
    else if (random >= 40) {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, 
                                                constants::CONVEYOR_SPAWN_Y, 0));
    }
    else if (random >= 20) {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, 
                                                constants::CONVEYOR_SPAWN_Y, 1));
    }
    else {
        conveyor_nodes.push_back(new Cargo_Node(constants::CONVEYOR_SPAWN_X, 
                                                constants::CONVEYOR_SPAWN_Y, 2));
    }
}

/**
 @brief: Removes a node from the conveyor when the player picks it up
 @return: A string representing the color of the node that was picked up or "Empty" if there are no nodes on the conveyor
 */
String Conveyor::pick_up_node() {
    if (!conveyor_nodes.empty() && conveyor_nodes[0]->get_node_sprite()->getPosition().x < 
        1.01 * constants::CONVEYOR_SPACING + constants::CONVEYOR_OFFSET) 
    {
        String color = conveyor_nodes[0]->get_color();
        conveyor_nodes.erase(conveyor_nodes.begin());
        return color;
    }
    return "Empty";
    
}

/**
 @brief: Updates the state of all nodes on the conveyor belt and moves them to appropriate positions
 */
void Conveyor::update() {
    for (int i = 0; i < conveyor_nodes.size(); i++) {
        if (conveyor_nodes[i]->get_node_sprite()->getPosition().x > i * 
            constants::CONVEYOR_SPACING + constants::CONVEYOR_OFFSET) 
        {
            conveyor_nodes[i]->get_node_sprite()->move(-2.3, 0);
        }
    }
}

/**
 @brief: Renders the conveyor belt object as well as all of its nodes contained in conveyor_nodes
 @param window The window to render onto
 @param frames The current frame the game is on
 */
void Conveyor::render(RenderWindow* window, int frames) {
    window->draw(get_conveyor_sprite(frames));
    for (Node* node : conveyor_nodes) {
        window->draw(*(node->get_node_sprite()));
    }
}

/**
 @brief: Checks whether not the conveyor is full and the player is currently losing
 @return: Boolean whether or not player is losing
 */
bool Conveyor::is_losing() {
    return conveyor_nodes.size() > constants::MAX_CONVEYOR_CAPACITY;
}
