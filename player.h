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
    
    
    bool is_holding;
    Node* held_node;
    
    int pickup_animation_status;
    int put_down_animation_status;
    string pickup_color;

    void pick_up_node(vector<Node*> nodes);
    void put_down_node(vector<Node*> nodes);
    
    float sprint_speed_factor;
    void pick_up_animation(string color);
    void put_down_animation();
    
public:
    Player();
    ~Player();

    Sprite get_player_sprite();
    int get_player_height();
    int get_player_width();
    float player_body_radius;
    
    void update(vector<Node*> nodes);
    void update_player_velocity();
    void update_player_speed();
    void update_player_position(vector<Node*> nodes);
    void update_player_animations();
    void display();
    Vector2<float> velocity;
    Vector2<float> pos;
    bool moving;
    bool is_sprinting;
     

    void set_moving_up(bool new_up);
    void set_moving_down(bool new_down);
    void set_moving_left(bool new_left);
    void set_moving_right(bool new_right);

    void toggle_pick_up(vector<Node*> nodes);
    void position_is_valid(float new_x, float new_y, vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid);
    
    
};



#endif // PLAYER_H
