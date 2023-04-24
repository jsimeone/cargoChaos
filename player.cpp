#include "player.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace sf;

Player::Player() {
    pos = {400, 400};
    get_textures();
    moving_left = false;
    moving_right = false;
    moving_up = false;
    moving_down = false;
    
    
}

Player::~Player() {
    return;
}

Sprite Player::get_player_sprite() {
    return player_sprite;
}
 
int Player::get_player_height() {
    return player_sprite.getTexture()->getSize().y * constants::PLAYER_SCALE;
}

int Player::get_player_width() {
    return player_sprite.getTexture()->getSize().x * constants::PLAYER_SCALE;
}

void Player::update(vector<Node*> nodes) {
    if (moving_up && !moving_down) {
        velocity.y -= 0.5;
    }
    if (moving_down && !moving_up) {
        velocity.y += 0.5;
    }
    if ((!moving_up && !moving_down) || (moving_up && moving_down)) {
        velocity.y /=2;
    }
    
    if (moving_left && !moving_right) {
        velocity.x -= 0.5;
    }
    if (moving_right && !moving_left) {
        velocity.x += 0.5;
    }
    if ((!moving_left && !moving_right) || (moving_left && moving_right)) {
        velocity.x /=2;
    }

    
    velocity = normalize_velocities(velocity);
    
    int new_x = pos.x + (velocity.x * constants::PLAYER_SPEED)*1.2;
    int new_y = pos.y + (velocity.y * constants::PLAYER_SPEED)*1.2;
    
    if (position_is_valid(new_x, new_y, nodes)) {
        pos.x = pos.x + velocity.x * constants::PLAYER_SPEED;
        pos.y = pos.y + velocity.y * constants::PLAYER_SPEED;
    } else {
        //this is lazy: the four lines below allow the player to slide if colliding with something
        if (position_is_valid(pos.x, new_y, nodes)) {
            pos.y = pos.y + velocity.y * constants::PLAYER_SPEED;
        } else if (position_is_valid(new_x, pos.y, nodes)){
            pos.x = pos.x + velocity.x * constants::PLAYER_SPEED;
        }
    }
    
    float direction = atan2(velocity.y, velocity.x) * 180.0/3.141592653589793238463;
    player_sprite.setRotation(direction+90);
    player_sprite.setPosition(pos.x, pos.y);
        
}

Vector2<float> Player::normalize_velocities(Vector2<float> &velocity){
    float magnitude = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (magnitude > 1) {
        return Vector2f(velocity.x / magnitude, velocity.y / magnitude);
    }
    return velocity;
}

void Player::display() {
    
}

void Player::get_textures() {
    if (!player_texture.loadFromFile("assets/player.png")) {
        std::cout<< "Load failed" << std::endl;
        system("pause");
    }
    player_sprite.setTexture(player_texture, true);
    player_sprite.setScale(constants::PLAYER_SCALE, constants::PLAYER_SCALE);
    player_sprite.setOrigin((sf::Vector2f)player_texture.getSize() / 2.f);
   

    
//    player_sprite.setTexture(texture, true);
    
}

void Player::set_moving_up(bool new_up) {
    moving_up = new_up;
}

void Player::set_moving_down(bool new_down) {
    moving_down = new_down;
}

void Player::set_moving_right(bool new_right) {
    moving_right = new_right;
}

void Player::set_moving_left(bool new_left) {
    moving_left = new_left;
}



bool Player::position_is_valid(float new_x, float new_y, vector<Node*> nodes) {
    for (Node* node : nodes){
        Sprite node_sprite = node->get_node_sprite();
        Vector2<float> node_pos = node_sprite.getPosition();
        float x_dis = node_pos.x - new_x;
        float y_dis = node_pos.y - new_y;
        float distance = get_player_width()/2 + (node_sprite.getTexture()->getSize().x * node_sprite.getScale().x)/2;
        if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance) {
            return false;
        }
    }
    //check walls:
    
    if (new_x > constants::SCREEN_WIDTH - get_player_width()/2) {
        return false;
    } else if (new_x < get_player_width()/2) {
        return false;
    } else if (new_y> constants::SCREEN_HEIGHT - get_player_height()/2) {
        return false;
    } else if (new_y < get_player_height()/2 ) {
        return false;
    }
    
    return true;
}




