#include "laser_node.h"

Laser_Node::Laser_Node(int x_pos, int y_pos) : 
	Node(x_pos, y_pos), 
	red_laser(node_sprite.getPosition(), 0),
	green_laser(node_sprite.getPosition(), 1),
	blue_laser(node_sprite.getPosition(), 2)
{
	set_texture("Laser");
    //get_node_sprite()->setScale(constants::LASER_NODE_SCALE, constants::LASER_NODE_SCALE);
}

string Laser_Node::get_color() {
	return "Laser";
}

bool Laser_Node::update_lasers_on(vector<Node*> nodes) {
	bool laser_on = false;
	for (Node* node : nodes) {
		if (node->get_is_held() && node->get_color() != "Laser") {
			string color = node->get_color();
			if (color == "Red") {
				red_laser.set_laser(true);
				green_laser.set_laser(false);
				blue_laser.set_laser(false);
				laser_on = true;
			}
			else if (color == "Green") {
				red_laser.set_laser(false);
				green_laser.set_laser(true);
				blue_laser.set_laser(false);
				laser_on = true;
			}
			else if (color == "Blue") {
				red_laser.set_laser(false);
				blue_laser.set_laser(true);
				green_laser.set_laser(false);
				laser_on = true;
			}
		}
	}
	return laser_on;
}

void Laser_Node::update(vector<Node*> nodes) {
	if (!update_lasers_on(nodes)) {
		red_laser.set_laser(false);
		blue_laser.set_laser(false);
		green_laser.set_laser(false);
		node_sprite.setRotation(node_sprite.getRotation() + .5);
	}
	red_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	green_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
	blue_laser.update_laser(node_sprite.getPosition(), node_sprite.getRotation(), nodes, node_sprite);
}

void Laser_Node::render(RenderWindow* window) {
//	red_laser.render(window);
//	green_laser.render(window);
//	blue_laser.render(window);
	Node::render(window);
}

void Laser_Node::render_lasers(RenderWindow* window) {
    red_laser.render(window);
    green_laser.render(window);
    blue_laser.render(window);
}

vector<Laser*> Laser_Node::get_lasers() {
    return {&red_laser, &green_laser, &blue_laser};
}
