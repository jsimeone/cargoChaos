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
	void render(RenderWindow* window);
    vector<Laser*> get_lasers();
    
};

#endif // LASER_NODE_H
