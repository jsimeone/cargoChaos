#include "player.h"
#include "constants.h"
#include <iostream>
#include <cmath>
using namespace sf;

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

void Player::update_player_speed() {
    if (is_sprinting) {
        sprint_speed_factor = constants::PLAYER_SPRINT_SPEED / constants::PLAYER_SPEED;
    }
    else {
        sprint_speed_factor = 1;
    }

    if (is_holding) {
        encumbered_speed_factor = constants::PLAYER_ENCUMBERED_SPEED / constants::PLAYER_SPEED;
    }
    else {
        encumbered_speed_factor = 1;
    }
}

void Player::update_player_position(vector<Node*> nodes) {
    int new_x = pos.x + velocity.x * constants::PLAYER_SPEED * sprint_speed_factor * encumbered_speed_factor;
    int new_y = pos.y + velocity.y * constants::PLAYER_SPEED * sprint_speed_factor * encumbered_speed_factor;

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

void Player::update_player_animations() {
    if (pickup_animation_status != 0) {
        pick_up_animation(pickup_color);
    }
    else if (put_down_animation_status != 0) {
        put_down_animation();
    }
}

void Player::pick_up_node(vector<Node*> nodes) {
    if (!is_holding) {
        for (Node* node : nodes) {
            Vector2<float> node_pos = node->get_node_sprite()->getPosition();
            float x_dis = node_pos.x - pos.x;
            float y_dis = node_pos.y - pos.y;
            float distance = (player_body_radius + (node->get_node_sprite()->getTexture()->getSize().x * node->get_node_sprite()->getScale().x) / 2) * 1.3;
            float node_angle = atan2(y_dis, x_dis) * 180.0 / constants::PI;; //angle between player and node
            float player_direction = player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET;
            float angle_difference = abs(player_direction - node_angle);
            if (angle_difference > 180) {
                angle_difference = abs(angle_difference - 360);
            }

            if (pow(pow(x_dis, 2) + pow(y_dis, 2), 0.5) <= distance && angle_difference <= 60) {
                string color = node->get_color();
                if (color != "Fried") {
                    node->pick_up(player_sprite.getPosition(), player_sprite.getRotation());
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

float Player::calculate_placement_offset(Node* node, Vector2f new_pos, float &angle) {
    float x_dist = node->get_node_sprite()->getPosition().x - new_pos.x;
    float y_dist = node->get_node_sprite()->getPosition().y - new_pos.y;
    angle = atan2(y_dist, x_dist);
    float dist = sqrtf(pow(x_dist, 2) + pow(y_dist, 2));
    return dist - node->get_node_sprite()->getTexture()->getSize().x * constants::NODE_SCALE;
}

bool Player::offset_on_placement(Vector2f &new_pos, float angle, float offset) {
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
    if (sqrt(pow(x_dist, 2) + pow(y_dist, 2)) <= held_node->get_node_sprite()->getTexture()->getSize().x * constants::NODE_SCALE / 2 + player_body_radius) {
        new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
        return false;
    }
    if (new_pos.x > constants::PLAY_AREA_WIDTH_BOUNDS[1] - get_player_width() / 2 || new_pos.x < constants::PLAY_AREA_WIDTH_BOUNDS[0] + get_player_width() / 2) {
        new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
         return false;
    }
    if (new_pos.y > constants::PLAY_AREA_HEIGHT_BOUNDS[1] - get_player_height() / 2 || new_pos.y < constants::PLAY_AREA_HEIGHT_BOUNDS[0] + get_player_height() / 2) {
        new_shake_intensity = constants::INVALID_PLACEMENT_SHAKE;
        return false;
    }
    return true;
}

void Player::put_down_node(vector<Node*> nodes) {
    if (is_holding) {
        Vector2f new_pos;
        new_pos.x = player_sprite.getPosition().x + constants::PLACE_DISTANCE * cos((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
        new_pos.y = player_sprite.getPosition().y + constants::PLACE_DISTANCE * sin((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
        for (Node* node : nodes) {
            float angle = 0;
            float offset = calculate_placement_offset(node, new_pos, angle);
            if (!offset_on_placement(new_pos, angle, offset)) {
                return;
            }
        }
        held_node->put_down(new_pos, player_sprite.getRotation());
        is_holding = false;
        held_node = nullptr;
        put_down_animation();
    }
}

Player::Player() : 
    pos({ (constants::PLAY_AREA_WIDTH_BOUNDS[1] - constants::PLAY_AREA_WIDTH_BOUNDS[0]) / 2 + constants::PLAY_AREA_WIDTH_BOUNDS[0], (constants::PLAY_AREA_HEIGHT_BOUNDS[1] - constants::PLAY_AREA_HEIGHT_BOUNDS[0]) / 2 + constants::PLAY_AREA_HEIGHT_BOUNDS[0] } ),
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
    player_body_radius = player_sprite.getTexture()->getSize().x / constants::PLAYER_ANIMATION_FRAMES * constants::PLAYER_SCALE*(.25);
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
    return player_sprite.getTexture()->getSize().x / constants::PLAYER_ANIMATION_FRAMES * constants::PLAYER_SCALE;
}

void Player::get_textures() {
    if (!player_texture.loadFromFile("assets/yellowSpriteSheet.png")) {
        cout<< "Loading player texture failed" << endl;
        system("pause");
    }
    player_sprite.setTexture(player_texture, true);
    player_sprite.setTextureRect(IntRect(0, 0, 512, 512));
    player_sprite.setScale(constants::PLAYER_SCALE, constants::PLAYER_SCALE);
    player_sprite.setOrigin(player_sprite.getTextureRect().width / 2, player_sprite.getTextureRect().height / 2);
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
    update_player_velocity();
    update_player_speed();
    update_player_position(nodes);
    update_player_animations();
}

void Player::display() {
    return;
}

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

void Player::check_play_bounds(float new_x, float new_y, bool &x_is_valid, bool &y_is_valid) {
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

void Player::check_node_collisions(Node* node, float new_x, float new_y, bool &x_is_valid, bool &y_is_valid) {
    Sprite node_sprite = *(node->get_node_sprite());
    Vector2<float> node_pos = node_sprite.getPosition();
    float x_dis = node_pos.x - new_x;
    float y_dis = node_pos.y - new_y;
    float distance = player_body_radius + (node_sprite.getTexture()->getSize().x * node_sprite.getScale().x) / 2;
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

void Player::position_is_valid(float new_x, float new_y, vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid) {
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

void Player::pick_up_from_conveyor(Node* node) {
    if (!is_holding) {
        node->pick_up(player_sprite.getPosition(), player_sprite.getRotation());
        pick_up_animation(node->get_color());
        pickup_color = node->get_color();
        is_holding = true;
        held_node = node;
    }
}

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

void Player::put_down_animation() {
    put_down_animation_status++;
    
    if (put_down_animation_status >= constants::PLAYER_ANIMATION_FRAMES) {
        put_down_animation_status = 0;
        if (!player_texture.loadFromFile("assets/YellowSpriteSheet.png")) {
            cout<< "Put down animation: Loading player texture failed" << endl;
        }
        return;
    }
    
    player_sprite.setTextureRect(IntRect(512 * (6 - put_down_animation_status), 0, 512, 512));
}

Vector2<float> Player::put_down_fried_node(vector<Node*> nodes) {
//    if (!is_holding) {
//        cout << "ERROR" << endl;
//        return {0, 0};
//    }
    Vector2f new_pos;
    new_pos.x = player_sprite.getPosition().x + constants::PLACE_DISTANCE * cos((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
    new_pos.y = player_sprite.getPosition().y + constants::PLACE_DISTANCE * sin((player_sprite.getRotation() + constants::PLACE_ANGLE_OFFSET) * constants::PI / 180);
    for (Node* node : nodes) {
        float angle = 0;
        float offset = calculate_placement_offset(node, new_pos, angle);
        offset_on_placement(new_pos, angle, offset);
        //            if (!offset_on_placement(new_pos, angle, offset)) {
        //                return;
        //            }
    }
    //held_node->put_down(new_pos, player_sprite.getRotation());
    held_node->is_held = false;
    is_holding = false;
    held_node = nullptr;
    put_down_animation();
    
    return new_pos;
}

