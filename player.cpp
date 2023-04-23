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

void Player::update() {
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
    pos.x += velocity.x * constants::PLAYER_SPEED;
    pos.y += velocity.y * constants::PLAYER_SPEED;
    
    
    float direction = atan2(velocity.y, velocity.x) * 180.0/3.141592653589793238463;
    player_sprite.setRotation(direction+90);
    player_sprite.setPosition(pos.x - get_player_width(), pos.y-get_player_height());
        
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
    std::cout<< "Load Successful" << std::endl;
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








