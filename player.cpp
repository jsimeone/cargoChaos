/**
 * Project 08: Cargo Chaos Player class method definitions.
 * @file player.ccp
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#include "player.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace sf;

/**
 * @brief: Updates player velocity vector depending on user input.
 */
void Player::update_player_velocity() {
    //====UPDATE VELOCITIES====//
    if (moving_up && !moving_down) {
        velocity.y -= 0.5;
    }
    else if (moving_down && !moving_up) {
        velocity.y += 0.5;
    }
    else if ((!moving_up && !moving_down) || (moving_up && moving_down)) {
        velocity.y /= 3;
    }
    if (moving_left && !moving_right) {
        velocity.x -= 0.5;
    }
    else if (moving_right && !moving_left) {
        velocity.x += 0.5;
    }
    else if ((!moving_left && !moving_right) || (moving_left && moving_right)) {
        velocity.x /= 3;
    }
    velocity = normalize_velocities(velocity);
}

/**
 * @brief: Updates player speed depending on whether or not
 *         the player is holding the sprint key and if the player is holding a node.
 */
void Player::update_player_speed() {
    if (is_sprinting) {
        sprint_speed_factor = constants::PLAYER_SPRINT_SPEED / constants::PLAYER_SPEED;
    }
    else {
        sprint_speed_factor = 1;
    }

    if (is_holding) {
        encumbered_speed_factor = constants::PLAYER_ENCUMBERED_SPEED / 
                                  constants::PLAYER_SPEED;
    }
    else {
        encumbered_speed_factor = 1;
    }
}

/**
 * @brief: Updates player position using the velocities and sprint/encumbered
 *         speed factors if the position is valid.
 * @param nodes Pointers to each node to check player-node collisions.
 */
void Player::update_player_position(vector<Node*> nodes) {
    int new_x = pos.x + velocity.x * constants::PLAYER_SPEED * 
                sprint_speed_factor * encumbered_speed_factor;
    int new_y = pos.y + velocity.y * constants::PLAYER_SPEED * 
                sprint_speed_factor * encumbered_speed_factor;

    bool x_is_valid;
    bool y_is_valid;
    position_is_valid(new_x, new_y, nodes, x_is_valid, y_is_valid);
    if (x_is_valid) {
        pos.x = new_x;
    }
    if (y_is_valid) {
        pos.y = new_y;
    }

    if (moving_left || moving_right || moving_down || moving_up) {
        float direction = atan2(velocity.y, velocity.x) * 180.0 / constants::PI;
        player_sprite.setRotation(direction + 90);
    }
    player_sprite.setPosition(pos.x, pos.y);
}

/**
 * @brief: Checks if animations are in progress and if so, animations
 *         are continued with pick_up_animation() and put_down_animation().
 */
void Player::update_player_animations() {
    if (pickup_animation_status != 0) {
        pick_up_animation(pickup_color);
    }
    else if (put_down_animation_status != 0) {
        put_down_animation();
    }
}

/**
 * @brief: Finds the first node in the player's field of vision and within reach distance and
 *         picks it up.
 * @param nodes A vector for nodes that could be picked up.
 */
void Player::pick_up_node(vector<Node*> nodes) {
    if (!is_holding) {
        for (Node* node : nodes) {
            Vector2<float> node_pos = node->get_node_sprite()->getPosition();
            float x_dis = node_pos.x - pos.x;
            float y_dis = node_pos.y - pos.y;
            float distance = (player_body_radius + 
                             (node->get_node_sprite()->getTexture()->getSize().x * 
                              node->get_node_sprite()->getScale().x) / 2) * 1.3;
            float node_angle = atan2(y_dis, x_dis) * 180.0 / constants::PI;
            float player_direction = player_sprite.getRotation() + 
                                     constants::PLACE_ANGLE_OFFSET;
            float angle_difference = abs(player_direction - node_angle);
            if (angle_difference > 180) {
                angle_difference = abs(angle_difference - 360);
            }

            if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance && 
                angle_difference <= 60) 
            {
                string color = node->get_color();
                if (color != "Fried") {
                    node->pick_up();
                    pick_up_animation(color);
                    pickup_color = color;
                    is_holding = true;
                    held_node = node;
                    return;
                }
                else {
                    new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
                }
            }
        }
    }
}

/**
 * @brief: Used when node is placed on top of another. Calculates the distance and direction
 *         the node needs to be to be in a valid position.
 * @param node The node in the way of the node being placed.
 * @param new_pos A vector representing the desired placement position of the node.
 * @param angle The direction that the node should be moved in to be in a valid place.
 * @return: The distance that the node should be moved to be in a valid place.
 */
float Player::calculate_placement_node_offset(Node* node, Vector2f new_pos, float &angle) {
    float x_dist = node->get_node_sprite()->getPosition().x - new_pos.x;
    float y_dist = node->get_node_sprite()->getPosition().y - new_pos.y;
    angle = atan2(y_dist, x_dist);
    float dist = sqrtf(pow(x_dist, 2) + pow(y_dist, 2));
    return dist - node->get_node_sprite()->getTexture()->getSize().x * 
           constants::NODE_SCALE;
}

/**
 * @brief: Checks if the player has placed a node out of the play area
 *         and adjusts the placement position.
 * @param new_pos The vector representing the nodes position.
 * @param node_radius The radius of the node being placed.
 */
void Player::calculate_place_wall_offset(Vector2f &new_pos, float node_radius) {
    if (new_pos.x > constants::PLAY_AREA_WIDTH_BOUNDS[1] - node_radius) {
        new_pos.x = constants::PLAY_AREA_WIDTH_BOUNDS[1] - node_radius/2.15;
    } else if (new_pos.x < constants::PLAY_AREA_WIDTH_BOUNDS[0] + node_radius) {
        new_pos.x = constants::PLAY_AREA_WIDTH_BOUNDS[0] + node_radius/2.15;
    }
    if (new_pos.y > constants::PLAY_AREA_HEIGHT_BOUNDS[1] - node_radius) {
        new_pos.y = constants::PLAY_AREA_HEIGHT_BOUNDS[1] - node_radius/1.5;
    } else if (new_pos.y < constants::PLAY_AREA_HEIGHT_BOUNDS[0] + node_radius) {
        new_pos.y = constants::PLAY_AREA_HEIGHT_BOUNDS[0] + node_radius/2.25;
    }
}

/**
 * @brief: Checks if the node offset is valid and sets the position according if it is.
 * @param new_pos A vector representing the node's position.
 * @param angle The direction that the node is being offset in.
 * @param offset The distance of the node's offset.
 * @return: If the offset is not too far away from the original position.
 */
bool Player::node_offset_on_placement(Vector2f &new_pos, float angle, float offset) {
    if (offset < -constants::MAX_PLACE_OFFSET) {
        new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
        return false;
    }
    if (offset < 0) {
        new_pos.x += cos(angle + constants::PI) * abs(offset);
        new_pos.y += sin(angle + constants::PI) * abs(offset);
    }
    float x_dist = new_pos.x - pos.x;
    float y_dist = new_pos.y - pos.y;
    if (sqrt(pow(x_dist, 2) + pow(y_dist, 2)) <= 
        held_node->get_node_sprite()->getTexture()->getSize().x * 
        constants::NODE_SCALE / 2 + player_body_radius) 
    {
        new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
        return false;
    }
    return true;
}

/**
 * @brief: Player puts down the held node if the held node can be placed in a valid position.
 * @param nodes A vector of node pointers to the nodes on the play area.
 */
void Player::put_down_node(vector<Node*> nodes) {
    if (is_holding) {
        Vector2f new_pos;
        new_pos.x = player_sprite.getPosition().x + constants::PLACE_DISTANCE * 
                    cos((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * 
                    constants::PI / 180);
        new_pos.y = player_sprite.getPosition().y + constants::PLACE_DISTANCE * 
                    sin((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * 
                    constants::PI / 180);
        
        calculate_place_wall_offset(new_pos, 
                                held_node->get_node_sprite()->getGlobalBounds().width/2);
        
        for (Node* node : nodes) {
            float angle = 0;
            float offset = calculate_placement_node_offset(node, new_pos, angle);
            if (!node_offset_on_placement(new_pos, angle, offset)) {
                return;
            }
        }
        held_node->put_down(new_pos, player_sprite.getRotation());
        is_holding = false;
        held_node = nullptr;
        put_down_animation();
    }
}

/**
 * @brief: Default constructor for the player class.
 */
Player::Player() : 
    pos({ (constants::PLAY_AREA_WIDTH_BOUNDS[1] - 
           constants::PLAY_AREA_WIDTH_BOUNDS[0]) / 2 + 
           constants::PLAY_AREA_WIDTH_BOUNDS[0], 
          (constants::PLAY_AREA_HEIGHT_BOUNDS[1] - 
           constants::PLAY_AREA_HEIGHT_BOUNDS[0]) / 2 + 
           constants::PLAY_AREA_HEIGHT_BOUNDS[0] } ),
    moving(false),
    moving_left(false),
    moving_right(false),
    moving_up(false),
    moving_down(false),
    is_sprinting(false),
    is_holding(false),
    held_node(nullptr),
    sprint_speed_factor(1),
    pickup_animation_status(0),
    put_down_animation_status(0),
    pickup_color("")
{
    get_textures();
    player_body_radius = player_sprite.getTexture()->getSize().x / 
                      constants::PLAYER_ANIMATION_FRAMES * constants::PLAYER_SCALE*(.25);
}

/**
 * @brief: Deconstructor for the player class. Useful in further development.
 */
Player::~Player() {
    return;
}

/**
 * @brief: Gets the sprite used by the player.
 * @return: returns the player's sprite object.
 */
Sprite Player::get_player_sprite() {
    return player_sprite;
}
 
/**
 * @brief: Gets the player's height using the texture size and the scale.
 * @return: returns an int representing the player's height.
 */
int Player::get_player_height() {
    return player_sprite.getTexture()->getSize().y * constants::PLAYER_SCALE;
}

/**
 * @brief: Gets the player's width using the texture size and the scale.
 * @return: Returns an int representing the player's width.
 */
int Player::get_player_width() {
    return player_sprite.getTexture()->getSize().x / constants::PLAYER_ANIMATION_FRAMES *
           constants::PLAYER_SCALE;
}
/**
 * @brief: Gets texture from assets, sets and scales texture according to settings, and 
           sets to sprite.
 */
void Player::get_textures() {
    if (!player_texture.loadFromFile("assets/yellowSpriteSheet.png")) {
        cout<< "Loading player texture failed" << endl;
        system("pause");
    }
    player_sprite.setTexture(player_texture, true);
    player_sprite.setTextureRect(IntRect(0, 0, 512, 512));
    player_sprite.setScale(constants::PLAYER_SCALE, constants::PLAYER_SCALE);
    player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, 
                            player_sprite.getTextureRect().height / 2);
}

/**
 * @brief: Indicates that player is being moved up by user input.
 * @param new_up true if player is moving up.
 */
void Player::set_moving_up(bool new_up) {
    moving_up = new_up;
}

/**
 * @brief: Indicates that player is being moved down by user input.
 * @param new_down True if player is moving down.
 */
void Player::set_moving_down(bool new_down) {
    moving_down = new_down;
}

/**
 * @brief: Indicates that player is being moved right by user input.
 * @param new_right true if player is moving right.
 */
void Player::set_moving_right(bool new_right) {
    moving_right = new_right;
}

/**
 * @brief: Indicates that player is being moved left by user input.
 * @param new_left true if player is moving left.
 */
void Player::set_moving_left(bool new_left) {
    moving_left = new_left;
}

/**
 * @brief: Normalizes velocities if the magnitude of velocities is greater than zero.
 *         Makes it so the sum of velocites can not surpass one.
 * @param velocity A vector with the x velocity and y velocity
 * @return: The velocity vector with magnitude less than or equal to one.
 */
Vector2<float> Player::normalize_velocities(Vector2<float> &velocity){
    float magnitude = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (magnitude > 1) {
        return Vector2f(velocity.x / magnitude, velocity.y / magnitude);
    }
    return velocity;
}

/**
 * @brief: Updates player position. Controls sequence of helper position functions.
 * @param nodes The nodes active in the play area for collisions.
 */
void Player::update(vector<Node*> nodes) {
    update_player_velocity();
    update_player_speed();
    update_player_position(nodes);
    update_player_animations();
}

/**
 * @brief: Display function for the player. To be used in later development.
 */
void Player::display() {
    return;
}

/**
 * @brief: Initiates a node pick up or put down based on whether the player is holding a
 *         node or not and if a pick up or put down is
 * already in progress.
 * @param nodes A vector of pointers to all nodes active on the playing field.
 */
void Player::toggle_pick_up(vector<Node*> nodes) {
    if (pickup_animation_status == 0 && put_down_animation_status == 0) {
        if (is_holding) {
            put_down_node(nodes);
        }
        else {
            pick_up_node(nodes);
        }
    }
}

/**
 * @brief: Checks if a the position of the player is within the play area.
 * @param new_x The x value of the position being checked.
 * @param new_y The y value of the position being checked.
 * @param x_is_valid Will be true if the x value of the position is valid.
 * @param y_is_valid Will be true if the y value of the position is valid.
 */
void Player::check_play_bounds(float new_x, float new_y, 
                               bool &x_is_valid, bool &y_is_valid) 
{
    if (new_x > constants::PLAY_AREA_WIDTH_BOUNDS[1] - player_body_radius) {
        x_is_valid = false;
    }
    else if (new_x < constants::PLAY_AREA_WIDTH_BOUNDS[0] + player_body_radius) {
        x_is_valid = false;
    }
    if (new_y > constants::PLAY_AREA_HEIGHT_BOUNDS[1] - player_body_radius) {
        y_is_valid = false;
    }
    else if (new_y < constants::PLAY_AREA_HEIGHT_BOUNDS[0] + player_body_radius) {
        y_is_valid = false;
    }
}

/**
 * @brief: Checks if the player will collide with a node.
 * @param node Node to be checked for collisions with player.
 * @param new_x The x value of the position being checked.
 * @param new_y The y value of the position being checked.
 * @param x_is_valid Will be true if the x value of the position is valid.
 * @param y_is_valid Will be true if the y value of the position is valid.
 */
void Player::check_node_collisions(Node* node, float new_x, float new_y, 
                                   bool &x_is_valid, bool &y_is_valid) 
{
    Sprite node_sprite = *(node->get_node_sprite());
    Vector2<float> node_pos = node_sprite.getPosition();
    float x_dis = node_pos.x - new_x;
    float y_dis = node_pos.y - new_y;
    float distance = player_body_radius + (node_sprite.getTexture()->getSize().x * 
                     node_sprite.getScale().x) / 2;
    if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance) {
        if (pow(pow(node_pos.x - pos.x, 2) + pow(y_dis, 2), 0.5) > distance) {
            x_is_valid = false;
        }
        else if (pow(pow(x_dis, 2) + pow(node_pos.y - pos.y, 2), 0.5) > distance) {
            y_is_valid = false;
        }
        else {
            x_is_valid = false;
            y_is_valid = false;
        }
    }
}

/**
 * @brief: Checks if a player position is valid.
 * @param new_x The x value of the position being checked
 * @param new_y The y value of the position being checked.
 * @param nodes A vector of node pointers pointing to the active nodes in the game area.
 * @param x_is_valid Will be true if the x value of the position is valid.
 * @param y_is_valid Will be true if the y value of the position is valid.
 */
void Player::position_is_valid(float new_x, float new_y, vector<Node*> nodes, 
                               bool &x_is_valid, bool &y_is_valid) 
{
    x_is_valid = true;
    y_is_valid = true;
    for (Node* node : nodes){
        if (!x_is_valid && !y_is_valid) {
            return; 
        }
        check_node_collisions(node, new_x, new_y, x_is_valid, y_is_valid);
    }
    if (!x_is_valid && !y_is_valid) {
        return; 
    }
    check_play_bounds(new_x, new_y, x_is_valid, y_is_valid);
}

/**
 * @brief: Makes player pick up a node from the conveyor.
 * @param node Pointer pointing to the node to be picked up.
 */
void Player::pick_up_from_conveyor(Node* node) {
    if (!is_holding) {
        node->pick_up();
        pick_up_animation(node->get_color());
        pickup_color = node->get_color();
        is_holding = true;
        held_node = node;
    }
}

/**
 * @brief: Continues and advances an active pick-up animation.
 * @param color The color of the node being picked up.
 */
void Player::pick_up_animation(string color) {
    pickup_animation_status++;
    
    if (pickup_animation_status >= constants::PLAYER_ANIMATION_FRAMES) {
        pickup_animation_status = 0;
        if (!player_texture.loadFromFile("assets/" + color + "SpriteSheet.png")) {
            cout<< "Pick up animation: Loading player texture failed" << endl;
        }
        return;
    }
    
    player_sprite.setTextureRect(IntRect(512 * pickup_animation_status, 0, 512, 512));
}

/**
 * @brief: Continues and advances an active put-down animation.
 */
void Player::put_down_animation() {
    put_down_animation_status++;
    
    if (put_down_animation_status >= constants::PLAYER_ANIMATION_FRAMES) {
        put_down_animation_status = 0;
        if (!player_texture.loadFromFile("assets/YellowSpriteSheet.png")) {
            cout<< "Put down animation: Loading player texture failed" << endl;
        }
        return;
    }
    
    player_sprite.setTextureRect(IntRect(512 * (6 - put_down_animation_status), 
                                         0, 512, 512));
}

/**
 * @brief: Player puts down a fried node after being hit by a laser.
 * @param nodes Vector of pointers pointing to the active nodes to check for collisions with fried node.
 * @return: The position of the fried node to be spawned by game.
 */
Vector2<float> Player::put_down_fried_node(vector<Node*> nodes) {
    Vector2f new_pos;
    new_pos.x = player_sprite.getPosition().x + constants::PLACE_DISTANCE * 
                cos((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * 
                constants::PI / 180);
    new_pos.y = player_sprite.getPosition().y + constants::PLACE_DISTANCE * 
                sin((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * 
                constants::PI / 180);
    calculate_place_wall_offset(new_pos, 
                                held_node->get_node_sprite()->getGlobalBounds().width/2);
    for (Node* node : nodes) {
        float angle = 0;
        float offset = calculate_placement_node_offset(node, new_pos, angle);
        node_offset_on_placement(new_pos, angle, offset);
    }
    held_node->is_held = false;
    is_holding = false;
    held_node = nullptr;
    put_down_animation();
    
    return new_pos;
}

