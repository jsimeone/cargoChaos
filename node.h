/**
 * Project 08: Cargo Chaos Node class declaration.
 * @file node.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

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
class Laser;

using namespace sf;
using namespace std;

class Node {
private:
protected:
	Texture texture;
	Sprite node_sprite;
    
public:
	Node(int x_pos, int y_pos);
	Sprite* get_node_sprite();
	void set_texture(string texture_file_name);
	void pick_up();
	virtual void put_down(Vector2f placement_position, float player_rotation);
	virtual string get_color() = 0;
	virtual void update(vector<Node*> nodes);
	virtual void render(RenderWindow* window);
	bool get_is_held();
    bool is_held;
    virtual void render_lasers(RenderWindow* window);
    virtual vector<Laser*> get_lasers();
};

#endif //NODE_H
