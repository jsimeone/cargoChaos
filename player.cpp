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
    is_holding = false;
    held_node = nullptr;
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

void Player::get_textures() {
    if (!player_texture.loadFromFile("assets/player.png")) {
        std::cout<< "Load failed" << std::endl;
        system("pause");
    }
    player_sprite.setTexture(player_texture, true);
    player_sprite.setScale(constants::PLAYER_SCALE, constants::PLAYER_SCALE);
    player_sprite.setOrigin((sf::Vector2f)player_texture.getSize() / 2.f);
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


//makes the velocities vector at most length 1 (limits speed to a maximum value of constants::PLAYER_SPEED)
Vector2<float> Player::normalize_velocities(Vector2<float> &velocity){
    float magnitude = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (magnitude > 1) {
        return Vector2f(velocity.x / magnitude, velocity.y / magnitude);
    }
    return velocity;
}

void Player::update(vector<Node*> nodes) {
    //====UPDATE VELOCITIES====//
    if (moving_up && !moving_down) {
        velocity.y -= 0.5;
    } else if (moving_down && !moving_up) {
        velocity.y += 0.5;
    } else if ((!moving_up && !moving_down) || (moving_up && moving_down)) {
        velocity.y /=2;
    }
    if (moving_left && !moving_right) {
        velocity.x -= 0.5;
    } else if (moving_right && !moving_left) {
        velocity.x += 0.5;
    } else if ((!moving_left && !moving_right) || (moving_left && moving_right)) {
        velocity.x /=2;
    }
    velocity = normalize_velocities(velocity);
    
    //====UPDATE POSITION====//
    int new_x = pos.x + (velocity.x * constants::PLAYER_SPEED);
    int new_y = pos.y + (velocity.y * constants::PLAYER_SPEED);
    bool x_is_valid;
    bool y_is_valid;
    position_is_valid(new_x, new_y, nodes, x_is_valid, y_is_valid);
    if (x_is_valid) {
        pos.x = pos.x + velocity.x * constants::PLAYER_SPEED;
    }
    if (y_is_valid) {
        pos.y = pos.y + velocity.y * constants::PLAYER_SPEED;
    }
    float direction = atan2(velocity.y, velocity.x) * 180.0/constants::PI;
    player_sprite.setRotation(direction+90);
    player_sprite.setPosition(pos.x, pos.y);
        
}

void Player::display() {
    
}



void Player::toggle_pick_up(vector<Node*> nodes) {
    if (is_holding) {
        put_down_node(nodes);
    }
    else {
        pick_up_node(nodes);
    }
}

void Player::pick_up_node(vector<Node*> nodes) {
    if (!is_holding) {
        for (Node* node : nodes) {
            Vector2<float> node_pos = node->get_node_sprite().getPosition();
            float x_dis = node_pos.x - pos.x;
            float y_dis = node_pos.y - pos.y;
            float distance = (get_player_width()/2 + (node->get_node_sprite().getTexture()->getSize().x * node->get_node_sprite().getScale().x)/2)*1.2;
            float node_angle = atan2(y_dis, x_dis)* 180.0/constants::PI;; //angle between player and node
            float player_direction = player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET;
            float angle_difference =abs(player_direction - node_angle);
            if (angle_difference > 180) {
                angle_difference = abs(angle_difference - 360);
            }
            //std::cout << "Angle Difference=" <<angle_difference << std::endl;
//            std::cout << "Distance Difference=" <<abs(pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) - distance) << std::endl;
            
            if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance && angle_difference <= 60) {
                node->pick_up(player_sprite.getPosition(), player_sprite.getRotation());
                is_holding = true;
                held_node = node;
                return;
            }
        }
    }
}

void Player::put_down_node(vector<Node*> nodes) {
    if (is_holding) {
        Vector2f new_pos;
        new_pos.x = player_sprite.getPosition().x + constants::PLACE_DISTANCE * cos((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
        new_pos.y = player_sprite.getPosition().y + constants::PLACE_DISTANCE * sin((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
        
        for (Node* node : nodes) {
            float x_dist = node->get_node_sprite().getPosition().x - new_pos.x;
            float y_dist = node->get_node_sprite().getPosition().y - new_pos.y;
            float angle = atan2(y_dist, x_dist);
            float dist = sqrtf(pow(x_dist, 2) + pow(y_dist, 2));
            float offset = dist - node->get_node_sprite().getTexture()->getSize().x * constants::NODE_SCALE;

            if (offset < 0) {
                new_pos.x += cos(angle + constants::PI) * abs(offset);
                new_pos.y += sin(angle + constants::PI) * abs(offset);
            }

        }
        float x_dist = new_pos.x - pos.x;
        float y_dist = new_pos.y - pos.y;
        
        if (sqrt(pow(x_dist, 2) + pow(y_dist, 2)) <= held_node->get_node_sprite().getTexture()->getSize().x * constants::NODE_SCALE/2 + get_player_width()/2){
            //if player places a node on top of another and it shifts it back onto the player, don't let the player place the node
            return;
        }

        if (new_pos.x > constants::SCREEN_WIDTH - get_player_width() / 2) {
            return;
        }
        else if (new_pos.x < get_player_width() / 2) {
            return;
        }
        if (new_pos.y > constants::SCREEN_HEIGHT - get_player_height() / 2) {
            return;
        }
        else if (new_pos.y < get_player_height() / 2) {
            return;
        }
        
        held_node->put_down(new_pos, player_sprite.getRotation());
        is_holding = false;
        held_node = nullptr;
    }
}



void Player::position_is_valid(float new_x, float new_y, vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid) {
    x_is_valid = true;
    y_is_valid = true;
    for (Node* node : nodes){
        if (!x_is_valid && !y_is_valid) {
            return; //no need to continue checking
        }
        Sprite node_sprite = node->get_node_sprite();
        Vector2<float> node_pos = node_sprite.getPosition();
        float x_dis = node_pos.x - new_x;
        float y_dis = node_pos.y - new_y;
        float distance = get_player_width()/2 + (node_sprite.getTexture()->getSize().x * node_sprite.getScale().x)/2;
        if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance) {
            //the position of new_x, new_y is not valid
            if (pow(pow(node_pos.x - pos.x, 2) + pow(y_dis, 2), 0.5) > distance) {
                x_is_valid = false;
            } else if (pow(pow(x_dis, 2) + pow(node_pos.y - pos.y, 2), 0.5) > distance) {
                y_is_valid = false;
            } else {
                x_is_valid = false;
                y_is_valid = false;
                return;
            }

        }
    }
    if (!x_is_valid && !y_is_valid) {
        return; //no need to continue checking
    }
    //check walls:
    if (new_x > constants::SCREEN_WIDTH - get_player_width()/2) {
        x_is_valid = false;
    } else if (new_x < get_player_width()/2) {
        x_is_valid = false;
    }
    if (new_y> constants::SCREEN_HEIGHT - get_player_height()/2) {
        y_is_valid = false;
    } else if (new_y < get_player_height()/2 ) {
        y_is_valid = false;
    }
}




