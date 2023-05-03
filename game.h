#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "constants.h"
#include "globals.h"
#include "player.h"
#include "node.h"
#include "conveyor.h"
#include "cargo_node.h"
#include "fried_node.h"
#include "laser_node.h"


using namespace sf;

class Game {
private:
    RenderWindow* window;
    Event event;
    VideoMode videoMode;
    Player player;
    Conveyor conveyor;
    vector<Node*> nodes;
    //Node node_test;
    int frame_counter;

    void init_variables();
    void init_window();
    void key_press_checker();
    void key_release_checker();
    void poll_events();

    void conveyor_pick_up();

    float current_screen_shake = 0;
    float shake_direction = 1;
    void screen_shake(float intensity);

    void get_backdrop();

    Texture backdrop_texture;
    Sprite backdrop_sprite;
    
    RectangleShape exit_rectangle;
    
    Texture scorebox_texture;
    Sprite scorebox_sprite;
    Text scorebox_text;
    Font scorebox_font;
    int score;

    Texture backdrop_walls_texture;
    Sprite backdrop_walls_sprite;

    View view;
public:
    Game();
    ~Game();

    void get_scorebox();

    bool is_running();

    void spawn_cargo_node(int x_pos, int y_pos, int color_index);
    void spawn_fried_node(int x_pos, int y_pos);
    void spawn_laser_node(int x_pos, int y_pos);

    void increment_score(int value);

    void update_player();
    void update_nodes();
    void random_spawn();
    void update_screen_shake();
    void update();

    void render_backdrop();
    void render_backdrop_walls();
    void render_screen_shake();
    void render_player();
    void render_nodes();
    void render_conveyor(int frames);
    void render_scorebox();
	  void render();
    
	
};

#endif // GAME_H