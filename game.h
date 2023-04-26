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
#include "player.h"
#include "node.h"
#include "cargo_node.h"

using namespace sf;

class Game {
private: 
	RenderWindow* window;
	Event event;
	VideoMode videoMode;
	Player player;
	vector<Node*> nodes;
	//Node node_test;

	void init_variables();
	void init_window();
	void poll_events();
    
    float current_screen_shake = 0;
    float shake_direction = 1;
    void screen_shake(float intensity);
    
    void get_backdrop();
    Texture backdrop_texture;
    Sprite backdrop_sprite;
    
    View view;
public:
	Game();
	~Game();

	bool is_running();

	void spawn_cargo_node(int x_pos, int y_pos, int color_index);

	void update_player();
	void update_nodes();
	void update();
    
    void render_backdrop();
    void render_screen_shake();
	void render_player();
	void render_nodes();
	void render();
	
};

#endif // GAME_H
