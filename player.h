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
#include "node.h"


using namespace sf;
using namespace std;

class Player {
private:
//    vector<Texture> idle_textures;
//    vector<Texture> walking_textures;
    
    void get_textures();
    Sprite player_sprite;
    Texture player_texture;
    
    Vector2<float> normalize_velocities(Vector2<float> &velocity);
    
    bool moving_left;
    bool moving_right;
    bool moving_up;
    bool moving_down;
    
public:
    Player();
    ~Player();

    Sprite get_player_sprite();
    int get_player_height();
    int get_player_width();
    
    void update(vector<Node*> nodes);
    void display();
    Vector2<float> velocity;
    Vector2<float> pos;
    bool moving = false;
     

    void set_moving_up(bool new_up);
    void set_moving_down(bool new_down);
    void set_moving_left(bool new_left);
    void set_moving_right(bool new_right);
    
    void position_is_valid(float new_x, float new_y, vector<Node*> nodes, bool &x_is_valid, bool &y_is_valid);
};


#endif // PLAYER_H
