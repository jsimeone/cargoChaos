#ifndef GAME_H
#define HAME_H
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
public:
	Game();
	~Game();

	bool is_running();

	void spawn_node(int x_pos, int y_pos, string texture);

	void update_player();
	void update_nodes();
	void update();

	void render_player();
	void render_nodes();
	void render();
	
};

#endif // GAME_H