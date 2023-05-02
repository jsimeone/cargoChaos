#ifndef NODE_H
#define NODE_H
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

class Node {
private:
protected:
	Texture texture;
	Sprite node_sprite;
	bool is_held;
public:
	Node(int x_pos, int y_pos);
	Sprite* get_node_sprite();
	void set_texture(string texture_file_name);
	virtual void pick_up(Vector2f player_position, float player_rotation);
	virtual void put_down(Vector2f player_position, float player_rotation);
	virtual string get_color() = 0;
	virtual void update(vector<Node*> nodes);
	virtual void render(RenderWindow* window);
	bool get_is_held();

};

#endif //NODE_H
