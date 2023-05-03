/**
 * Project 08: Cargo Chaos Laser_Node class declaration.
 * @file laser_node.h
 * @authors Jack Kertscher, Hank Elsesser, Joe Simeone, Javi Garcia
 * @date May 4, 2023
 */

#ifndef LASER_NODE_H
#define LASER_NODE_H
#include "node.h"
#include "laser.h"
class Laser_Node : public Node {
private:
	Laser red_laser;
	Laser blue_laser;
	Laser green_laser;

	Laser_Node() = delete;
public:
	Laser_Node(int x_pos, int y_pos);
	string get_color();
	bool update_lasers_on(vector<Node*> nodes);
	void update(vector<Node*> nodes);
    void render_lasers(RenderWindow* window);
    vector<Laser*> get_lasers();
};

#endif // LASER_NODE_H
