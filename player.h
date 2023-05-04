#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "constants.h"
#include "globals.h"
#include "node.h"
#include "cargo_node.h"

using namespace sf;
using namespace std;

class Player {
private:
    
    void get_textures();
    Sprite player_sprite;
    Texture player_texture;
    
    Vector2<float> normalize_velocities(Vector2<float> &velocity);
    
    bool moving_left;
    bool moving_right;
    bool moving_up;
    bool moving_down;
    
   
    

    Vector2<float> velocity;
    Vector2<float> pos;
    bool moving;

    void update_player_velocity();
    void update_player_speed();
    void update_player_position(vector<Node*> nodes);
    void update_player_animations();

    void pick_up_node(vector<Node*> nodes);
    
    bool wall_offset_on_placement(Vector2f &new_pos, float angle, float offset);
    bool node_offset_on_placement(Vector2f &new_pos, float angle, float offset);
    float calculate_placement_node_offset(Node* node, Vector2f new_pos, float &angle);
    void calculate_placement_wall_offset(Vector2f &new_pos, float node_radius);
    
    void put_down_node(vector<Node*> nodes);
    
    float sprint_speed_factor;
    float encumbered_speed_factor;
    void put_down_animation();
    
public:
    Player();
    ~Player();

    Sprite get_player_sprite();
    int get_player_height();
    int get_player_width();
    float player_body_radius;

    void update(vector<Node*> nodes);
    
    void display();

    bool is_holding;
    bool is_sprinting;

    void set_moving_up(bool new_up);
    void set_moving_down(bool new_down);
    void set_moving_left(bool new_left);
    void set_moving_right(bool new_right);
    
    void pick_up_animation(string color);
    int pickup_animation_status;
    int put_down_animation_status;
    string pickup_color;

    void toggle_pick_up(vector<Node*> nodes);
    void check_play_bounds(float new_x, float new_y, bool &x_is_valid, bool &y_is_valid);
    void check_node_collisions(Node* node, float new_x, float new_y, bool &x_is_valid, bool &y_is_valid);
    void position_is_valid(float new_x, float new_y, vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid);
    void pick_up_from_conveyor(Node* node);
    Node* held_node;
    Vector2<float> put_down_fried_node(vector<Node*> nodes);
};



#endif // PLAYER_H
