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

#include "constants.h"

using namespace sf;
using namespace std;

class Player {
private:
	Texture texture;
	Sprite player_sprite;

	bool moving_left;
	bool moving_right;
	bool moving_up;
	bool moving_down;
	vector<float> velocity;
	Vector2i target_position;
public:
	Player();
	~Player();

	Sprite get_player_sprite();
	int get_player_height();
	int get_player_width();
	void update_player_velocity();
	void update_player_position();
	void set_moving_up(bool new_up);
	void set_moving_down(bool new_down);
	void set_moving_left(bool new_left);
	void set_moving_right(bool new_right);
	void set_target_position(Vector2i new_target);

};


#endif // PLAYER_H